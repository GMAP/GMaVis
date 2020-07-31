/* ***************************************************************************
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  As a special exception, you may use this file as part of a free software
 *  library without restriction.  Specifically, if other files instantiate
 *  templates or use macros or inline functions from this file, or you compile
 *  this file and link it with other files to produce an executable, this
 *  file does not by itself cause the resulting executable to be covered by
 *  the GNU General Public License.  This exception does not however
 *  invalidate any other reasons why the executable file might be covered by
 *  the GNU General Public License.
 *
 ****************************************************************************
 *  Authors: Cleverson Ledur <cleversonledur@gmail.com>
 *  Copyright: GNU General Public License
 *  Description: This is part of the GMaVis Compiler
 *  File Name: preprocessor.cpp
 *  Version: 1.0 (20/10/2015)
 ****************************************************************************
*/
int REQUIRED1 = 3-1;
int REQUIRED2 = 4-1;
#include "sys/sysinfo.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
 #include <fstream>
 #include <vector>

typedef struct {
	char ***buffer;
	unsigned long long **counter;
}data_to_parse;

typedef struct {
	unsigned long long *result = NULL;
	unsigned long long count;
}filter_data;



using namespace std;


bool header_in_file=false;


filter_data filter(unsigned long long **counter,char ***data, unsigned long long number_of_fields);

std::string print_output(unsigned long long filter_finds,unsigned long long **counter,char ***data, unsigned long long *filter, char delimiter, char endRegistry);



std::string return_string(char *buffer, unsigned long long count){

	std::string string_to_return="";
	if(buffer){
		
		for(unsigned long long i=0;i<count;i++){
			if(buffer[i]){
				string_to_return += buffer[i];
			}
		}	
	}	
	return string_to_return;
}

unsigned long long return_registry_number(char *buffer, char endregistry, char delimiter,unsigned long long start, unsigned long long end){
	unsigned long long registry_n=0;
	for(unsigned long long i=start;i<=end;i++){
		if(buffer[i]==endregistry){
			registry_n++;
		}
	}
	return registry_n;
	
}

unsigned long long return_fields_number(char delimiter, char endRegistry, char *buffer,unsigned long long start, unsigned long long end){
	unsigned long long fields = 0;
	unsigned long long i;
	for(i=start;i<=end;i++){
		if(buffer[i]==delimiter)
			fields++;
		else if(buffer[i]==endRegistry){
			fields++;
			break;
		}
	}
	if(fields < REQUIRED1)
		{
			
			
			return -1;
		}
	if(fields < REQUIRED2)
		{
			
				
			return -1;
		}
	
	return fields;
}



bool string_contains(unsigned long long **counter,char ***data, unsigned long long i, int field, std::string value){
		
		std::string field_data = return_string(data[i][field],counter[i][field]);
		
		std::size_t found = field_data.find(value);
		
		return found!=std::string::npos ? true : false;
		
}
bool string_is_equal(unsigned long long **counter,char ***data, unsigned long long i, int field, std::string value){
		
		std::string field_data = return_string(data[i][field],counter[i][field]);

		return field_data == value ? true : false;
		
}
bool string_is_different(unsigned long long **counter,char ***data, unsigned long long i, int field, std::string value){
		
		std::string field_data = return_string(data[i][field],counter[i][field]);
		
		std::size_t found = field_data.find(value);
		
		return found!=std::string::npos ? false : true;
}


bool int_is_equal(unsigned long long **counter,char ***data, unsigned long long i, int field, long long int value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value == atoll(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool int_is_different(unsigned long long **counter,char ***data, unsigned long long i, int field, long long int value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value != atoll(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool int_is_greater(unsigned long long **counter,char ***data, unsigned long long i, int field, long long int value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value < atoll(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool int_is_less(unsigned long long **counter,char ***data, unsigned long long i, int field, long long int value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value > atoll(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool int_is_between(unsigned long long **counter,char ***data, unsigned long long i, int field, long long int value1, long long int value2 ){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if((value1 < atoll(field_data.c_str()))&&(value2 > atoll(field_data.c_str()))){
			return true;
		}else{
			return false;
		}
}


bool float_is_equal(unsigned long long **counter,char ***data, unsigned long long i, int field, double value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value == atof(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool float_is_different(unsigned long long **counter,char ***data, unsigned long long i, int field, double value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value != atof(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool float_is_greater(unsigned long long **counter,char ***data, unsigned long long i, int field, double value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value < atof(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool float_is_less(unsigned long long **counter,char ***data, unsigned long long i, int field, double value){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if(value > atof(field_data.c_str())){
			return true;
		}else{
			return false;
		}
}

bool float_is_between(unsigned long long **counter,char ***data, unsigned long long i, int field, double value1, double value2 ){

		std::string field_data = return_string(data[i][field],counter[i][field]);

		if((value1 < atof(field_data.c_str()))&&(value2 > atof(field_data.c_str()))){
			return true;
		}else{
			return false;
		}
}

/******************************************************************************
-> FILE OPERATIONS
******************************************************************************/

data_to_parse file_parser(char *buffer, char endRegistry, char delimiter, unsigned long long start, unsigned long long end){
	unsigned long long **counter;
	char *** array_data;
	

	unsigned long long n=0,l=0; 
						
						

	
	
	
	for(unsigned long long i=start;i<=end;i++){
		if(buffer[i]==endRegistry){
			n++;
		}
	}
	
	
	
	l = return_fields_number(delimiter, endRegistry,buffer,start,end);
	
	
	array_data = new char**[n];
	counter = new unsigned long long* [n];

	unsigned long long row=0; unsigned long long column=0;
	unsigned long long field_size = 0;
	for(unsigned long long i=0;i<n;i++){
		counter[i] = new unsigned long long[l];
		array_data[i] = new char*[l];
		for(unsigned long long j=0;j<l;j++){
			counter[i][j] = 0;
			array_data[i][j] = NULL;
		}
		if(!array_data[i])
			exit(-1);
	}
	for(unsigned long long i=start;i<=end;i++){		
		if(buffer[i]==delimiter){
			array_data[row][column] = &buffer[i-field_size];
			counter[row][column] = field_size;
			field_size = 0;
			column++;
		}
		else if (buffer[i]==endRegistry){
			array_data[row][column] = &buffer[i-field_size];
			counter[row][column] = field_size;
			row++;
			field_size = 0;
			column=0;
		}else{
			field_size += 1;
		}
	}
	
	data_to_parse data_to_return;
	data_to_return.buffer = array_data;
	data_to_return.counter = counter;
	
return (data_to_return);

}

void desalocate_3D(char ***data, unsigned long long **counter, unsigned long long n){

	
	
	for(unsigned long long i=0;i<n;i++)
    {
    	if(data[i] !=NULL)
    		delete [] data[i];
		delete [] counter[i];
    }
    delete [] counter;
 delete [] data;

}

std::string process_chunk(char *file, unsigned long long start, unsigned long long end, char delimiter, char endRegistry){
	
	unsigned long long **counter;
	
	
	
	unsigned long long n=0;
	for(unsigned long long i=start;i<=end;i++){
		if(file[i]==endRegistry){
			n++;
		}
	}
	
	
	char ***data;
	unsigned long long del =  return_fields_number(delimiter,endRegistry, file,start,end);
	if(del==-1)
		return "";
	unsigned long long del_aux = 0;
	unsigned long long line=0;
	/*for(unsigned long long i=start;i<=end;i++){
		if(file[i]=='''){
			file[i]=' ';
		}
		if(file[i]==delimiter){
			del_aux ++;
		}
		if(file[i]==endRegistry){
			del_aux ++;
			line++;
			if(del_aux!=del){
				std::cout << "ERROR: Data with problem in line " << line << ": " << del_aux << " != " << del << std::endl;
				exit(-1);				
			}			
			del_aux = 0;
		}
	}*/
	
	data_to_parse parsed_data;
	
	
	parsed_data = file_parser(file,endRegistry,delimiter,start,end);
	data = parsed_data.buffer;
	counter = parsed_data.counter;
	
	
	
	
	filter_data filtered_data = filter(counter,data,n);
	unsigned long long *x = filtered_data.result;
	unsigned long long filtered_data_n = filtered_data.count;
	
	
	
	
	std::string output = print_output(filtered_data_n,counter,data, x,delimiter,endRegistry);
	
	
	free(x);
	desalocate_3D(data,counter, n);
	return (char*)output.c_str();
}

unsigned long long recalculate_start(char* buffer,unsigned long long start, unsigned long long lSize ,char endRegistry,char delimiter){
	
	if(buffer[start]==endRegistry){
		start++;
	}
	unsigned long long n=start;
	int lines=0,col1=0,col2=0;
	while(lines==0){
		if(buffer[n]==delimiter){
			col1++;
		}
		if(buffer[n]==endRegistry){
			col1++;
			lines++;
		}
		n++;
		
	}
	while(lines==1){
		if(buffer[n]==delimiter){
			col2++;
		}
		if(buffer[n]==endRegistry)
		{
			col2++;
			lines++;
		}
		n++;

	}
	if(col1!=col2){	
		for(unsigned long long i = start;i<lSize;i++){
			if(buffer[i]==endRegistry){

				start=i+1;
				
				break;
			}

		}
	}
	return start;
}

unsigned long long recalculate_end(char* buffer, unsigned long long  lSize,char endRegistry,char delimiter){

	/*int start=0;
	if(buffer[start]==endRegistry){
		start++;
	}*/
	/*unsigned long long n=start;
	int lines=0,col1=0,col2=0;
	while(lines==0){
		
		if(buffer[n]==delimiter){
			col1++;
		}
		if(buffer[n]==endRegistry){
			col1++;
			lines++;
		}
		
		n++;
		
	}
	while(lines==1){
		
		if(buffer[n]==delimiter){
			col2++;
		}
		if(buffer[n]==endRegistry)
		{
			col2++;
			lines++;
		}

		n++;
		
	}
	*/
	for(unsigned long long i=lSize;i>0;i--){
		if(buffer[i]==endRegistry){
			
			
			lSize=i;
			break;
		}
	}
	return lSize;
}

static inline ssize_t getNumProcessors() {
	ssize_t n = 1; 
	FILE * f; 
	f = popen("cat /proc/cpuinfo |grep processor | wc -l","r"); 
	if(fscanf(f,"%ld",& n) == EOF)
	{
		pclose (f); 
		return n;
	} 
	pclose (f); 
	return n;
}
static inline ssize_t getfile_lines(std::string file_name) {
	ssize_t n = 1; 
	FILE * f; 
	std::string command = "wc -l " + file_name + " | awk '{print $1}' ";
	f = popen(command.c_str(),"r"); 
	if(fscanf(f,"%ld",& n) == EOF)
	{
		pclose (f); 
		return n;
	} 
	pclose (f); 
	return n;
}


bool date_is_between(unsigned long long **counter,char ***data,unsigned long long i, int field, std::string date2, std::string date3){
	std::string date1 = return_string(data[i][field],counter[i][field]);
	int day1=0, month1=0, year1=0;
	int day2=0, month2=0, year2=0;
	int day3=0, month3=0, year3=0;
	int ok;
	if(year1 > year2){
		ok = 0;
	//printf("%d is greater than %d\n", year1,year2);
	}else if((year1 == year2) && (month1 > month2)){
		ok = 0;
	}else if((year1 == year2) && (month1 == month2) && (day1 > day2)){
		ok = 0;
	}else{
		return false;
	}
	if(year1 < year3){
		ok = 0;
	}else if((year1 == year3) && (month1 < month3)){
		ok = 0;
	}else if((year1 == year3) && (month1 == month3) && (day1 < day3)){
		ok = 0;
	}else{
		return false;
	}
//printf("%d %d %d is between %d %d %d and %d %d %d\n", day1,month1,year1,day2,month2,year2,day3,month3,year3);
	if(ok==0)
		return true;
	return true;
}
bool date_is_less(unsigned long long **counter,char ***data, unsigned long long i, int field, std::string date2){
	std::string date1 = return_string(data[i][field],counter[i][field]);
	int day1=0, month1=0, year1=0;
	int day2=0, month2=0, year2=0;
if(year1 < year2){
	return true;
}else if((year1==year2)&&(month1<month2)){
	return true;
}else if((year1==year2)&&(month1 == month2)&&(day1<day2)){
	return true;
}else{
	return false;
}
}
bool date_is_greater(unsigned long long **counter,char ***data,unsigned long long i, int field, std::string date2){
	std::string date1 = return_string(data[i][field],counter[i][field]);
	int day1=0, month1=0, year1=0;
	int day2=0, month2=0, year2=0;
if(year1 > year2){
	return true;
}else if((year1==year2)&&(month1>month2)){
	return true;
}else if((year1==year2)&&(month1 == month2)&&(day1>day2)){
	return true;
}else{
	return false;
}
}
bool date_is_equal(unsigned long long **counter,char ***data, unsigned long long i, int field, std::string date2){
	std::string date1 = return_string(data[i][field],counter[i][field]);
	int day1=0, month1=0, year1=0;
	int day2=0, month2=0, year2=0;
if((year1==year2)&&(month1 == month2)&&(day1==day2)){
	return true;
}else{
	return false;
}
}
bool date_is_different(unsigned long long **counter,char ***data, unsigned long long i, int field, std::string date2){
	std::string date1 = return_string(data[i][field],counter[i][field]);
	int day1=0, month1=0, year1=0;
	int day2=0, month2=0, year2=0;
if((year1!=year2)&&(month1 != month2)&&(day1!=day2)){
	return true;
}else{
	return false;
}
}


filter_data filter(unsigned long long **counter,char ***data, unsigned long long number_of_fields){

filter_data filtered_data;
unsigned long long *result;
unsigned long long count = 0;
result = (unsigned long long*)malloc(sizeof(unsigned long long)*number_of_fields);	
for(unsigned long long i=0;i<number_of_fields;i++){
		if((i==0)&&(header_in_file==true)) continue;

		std::string required_field1 = return_string(data[i][REQUIRED1],counter[i][REQUIRED1]);
		std::string required_field2 = return_string(data[i][REQUIRED2],counter[i][REQUIRED2]);
		if( ((strcmp(required_field1.c_str(),(char*)"")!=0) && (strcmp(required_field2.c_str(),(char*)"")!=0)) && (string_is_equal(counter,data,i,13-1,"2016")) )
		{

			result[count]=i;
			count++;
		}
	}
	filtered_data.result = result;
	filtered_data.count = count;
	return filtered_data;
}


int classification(unsigned long long **counter, char ***data, unsigned long long j,unsigned long long *filter){

	unsigned long long i = filter[j];
	if(string_is_equal(counter,data,i,11-1,"RS"))
		return 1;
	if(string_is_equal(counter,data,i,11-1,"SP"))
		return 2;
	if(string_is_equal(counter,data,i,11-1,"RJ"))
		return 3;
	if(string_is_equal(counter,data,i,11-1,"MG"))
		return 4;
	return 0;
}
std::string print_output(unsigned long long filter_finds,unsigned long long **counter,char ***data, unsigned long long *filter, char delimiter, char endRegistry){
std::string output_aux;
std::string output;
for(unsigned long long i=0;i<filter_finds;i++){
		int classification_class = classification(counter,data,i,filter);
		if(classification_class!=0){
			output_aux =  return_string(data[filter[i]][REQUIRED1],counter[filter[i]][REQUIRED1]) + delimiter + return_string(data[filter[i]][REQUIRED2],counter[filter[i]][REQUIRED2])+delimiter+ std::to_string(classification_class) + endRegistry;
output+=output_aux;
}
}
return output;
}
		int threads = 3;
int main(){
	std::vector < std::string > files;
	std::vector <bool> files_header_info;
files.push_back("examples/datasets/saude_brasil.csv");	files_header_info.push_back(true);
	[[spar::ToStream(),spar::Input(files,files_header_info)]]while(!files.empty()){
			std::cout << "Starting processing of file " << files.back() << "\n";
			header_in_file = files_header_info.back();
		std::string filename = files.back();
		char delimiter = ';';
		char endRegistry = '\n';

		long long start = 0,end=0;
	unsigned long long total_processed = 0;
		unsigned long freeMem = 0;
	unsigned long long chunk_size = 104857600;
	//printf("Free Memory: %f\n", ((float)freeMem/1024)/1024);
	//printf("Chunk size: %f\n", ((float)chunk_size/1024)/1024);
	unsigned long long last_read = 0;
	unsigned long long file_size = 0;
	int num_processors = getNumProcessors();
//Open File
FILE *pFile;
	pFile = fopen((const char*)filename.c_str(),"r");
	if(pFile==NULL){
		printf("\n\nERROR: Hey! I can not open this file! Verify this file specificaion in your code...\n");
		exit(-1);
	}
	//printf("Loading file %s to buffer.\n",filename);
	fseek (pFile , 0 , SEEK_END);
	file_size = ftell (pFile);
	

	auto t_start = std::chrono::high_resolution_clock::now();
	

while(last_read < file_size){
		
		//std::cout << "Begining new processing...\n";
		int chunk_count = 0;
		rewind (pFile);
		unsigned long long read_size = 0;
		if(file_size - last_read < chunk_size){
			read_size = file_size - last_read;
			//std::cout << "Last reading...\n";
			if(read_size<100){ //Junk data like \n in the end of file\n				break;
			}
		}else{
			//std::cout << "Middle reading...\n";
			read_size = chunk_size;
		}
		//std::cout << "\nread_size:		" << read_size << std::endl;
		char * buffer=NULL;
		buffer = new char[read_size];
		if(buffer!=NULL){
			fseek(pFile, last_read, SEEK_SET);
			//std::cout << "\nread_size2:		" << read_size << std::endl;
			if(fread (buffer,1,read_size,pFile) != read_size){
				std::cerr << "ERROR: Error when reading file.\n";
				exit(-1);
			}
		}else{
			std::cerr << "ERROR: Error in malloc of buffer when reading file.\n";
		}
		//std::cout << "\nread_size3:\t\t" << read_size << std::endl;
 start =1;
		//start = recalculate_start(buffer,end,read_size,endRegistry,delimiter);	
		end = read_size; 
		end = recalculate_end(buffer,end,endRegistry,delimiter); 
last_read += end;
		total_processed=end;
		chunk_count +=1;
		
		std::cout << "chunk_size:		" << chunk_size << std::endl;
		std::cout << "file_size:		" << file_size << std::endl;
		std::cout << "last_read:		" << last_read << std::endl;
		std::cout << "total_processed:	" << total_processed << std::endl;
		std::cout << "chunk_count:		" << chunk_count << std::endl;
		std::cout << "end: 			" << end << std::endl;
		std::cout << "start: 			" << start << std::endl;	
		std::string output_chunk;
		[[spar::Stage(),spar::Input(buffer,output_chunk,start,end,delimiter,endRegistry),spar::Output(output_chunk),spar::Replicate(threads)]]{
			output_chunk = process_chunk(buffer,start,end,delimiter,endRegistry);
			delete [] buffer;
		}
		[[spar::Stage(),spar::Input(output_chunk)]]{
						
			std::ofstream out_file;
			out_file.open ("/home/cleversonledur/SVN_REPOS/GMaVis/compiler/build/bin/.log/output",std::ios::app);
			if(out_file.fail()){
				std::cout << "ERROR to open file\n";
				exit(-1);
		}
		out_file << output_chunk;
		out_file.close();	
		}	
	}
	auto t_end = std::chrono::high_resolution_clock::now();
	std::cout << "	"  <<  std::chrono::duration<double>(t_end-t_start).count() << "	";
	
	fclose(pFile);

			files.pop_back();
	}
	return 0;
}
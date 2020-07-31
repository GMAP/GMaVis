# Author: Cleverson Ledur <cleversonledur@gmail.com>
# Date:   April 2015

all: pwd spar gmavis

pwd:
	pwd > bin/.gmavis

spar:
	mkdir -p spar
	svn checkout svn://svn.code.sf.net/p/spar-dsl-compiler/svn spar --depth empty
	svn checkout svn://svn.code.sf.net/p/spar-dsl-compiler/svn/bin spar/bin
	svn checkout svn://svn.code.sf.net/p/spar-dsl-compiler/svn/libraries spar/libraries
	svn up spar/Makefile
	cd spar/; make

gmavis:
	mkdir -p generated_visualizations

clean:
	rm bin/.gmavis
	rm spar -rf
	rm generated_visualizations -rf

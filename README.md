# GMaVis: A Domain-Specific Language for Geo-Visualization

GMaVis is a domain-specific language (DSL) that simplifies the creation of visualization from geospatial information, which is designed to use multi-core architecture parallelism to process data in parallel. Its compiler abstracts complexities from the whole visualization creation process, even in the data pre-processing phase. Also, it allows domain users with
low-level knowledge in computer programming to create these visualizations through a high-level description language. These users can easily do it with a few lines of code, using simple declarations and blocks to express visualization details. Currently, GMaVis supports the creation of three types of geospatial visualization: markedmap, clusteredmap and heatmap. GMaVis has a short and simple grammar.

![img](https://github.com/GMAP/GMaVis/blob/master/images/video-gmavis.gif)

## Authors

**Cleverson Ledur** (Creator) <cleversonledur@gmail.com>

**Dalvan Griebler** (Contributor and Mentoring) <dalvangriebler@gmail.com>

**Isabel Mansur** (Mentoring)

**Luiz G. Fernandes** (Mentoring)




## Reference Papers for citation

[[DOI]](https://doi.org/10.1109/COMPSAC.2017.18) Ledur, C.; Griebler, D.; Manssour, I.; Fernandes, L. G. **A High-Level DSL for Geospatial Visualizations with Multi-core Parallelism Support**. *41st IEEE Computer Society Signature Conference on Computers, Software and Applications (COMPSAC)*, 2017.

[[DOI]](http://dx.doi.org/10.1109/AICCSA.2015.7507178) Ledur, C.; Griebler, D.; Manssour, I.; Fernandes, L. G.. **Towards a Domain-Specific Language for Geospatial Data Visualization Maps with Big Data Sets**. *ACS/IEEE International Conference on Computer Systems and Applications (AICCSA)*, 2015.

## Other publications about GMaVis

[[DOI]](https://doi.org/10.1007/978-3-030-41050-6_7) Vogel A.; Rista, C.; Justo, G.; Ewald, E.; Griebler, D.; Mencagli, G.; Fernandes, L. G. **Parallel Stream Processing with MPI for Video Analytics and Data Visualization**. *Communications in Computer and Information Science (CCIS)*, 2020.

[[DOI]](http://tede2.pucrs.br/tede2/handle/tede/6837) Ledur, C. **GMaVis: A Domain-Specific Language for Large-Scale Geospatial Data Visualization Supporting Multi-core Parallelism**. *Master Thesis*, PPGCC - PUCRS, 2016.


# Using GMaVis

GMaVis' compiler is used to recognize GMaVis' code and transform it in a geospatial data visualizations.

In order to use this compiler, you must inform the file with GMaVis'code.

## Command Line

Usage:
``
bin/gmavis [-i/--input] <arg> [-o/--output] <arg> [-p/--parallel] <arg>
``

Example: 
``
bin/gmavis -i examples/heatmap_accidents_poa.vis -o out.html -p 2
``

To see all GMaVis options:
``
bin/gmavis -h
``

## Visualizations

![img](https://github.com/GMAP/GMaVis/blob/master/images/heatmap.png)
![img](https://github.com/GMAP/GMaVis/blob/master/images/marketmap.png)


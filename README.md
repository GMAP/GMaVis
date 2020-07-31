# GMaVis: A Domain-Specific Language for Geo-Visualization

GMaVis is a domain-specific language (DSL) that simplifies the creation of visualization from geospatial information, which is designed to use multi-core architecture parallelism to process data in parallel. Its compiler abstracts complexities from the whole visualization creation process, even in the data pre-processing phase. Also, it allows domain users with
low-level knowledge in computer programming to create these visualizations through a high-level description language. These users can easily do it with a few lines of code, using simple declarations and blocks to express visualization details. Currently, GMaVis supports the creation of three types of geospatial visualization: markedmap, clusteredmap and heatmap. GMaVis has a short and simple grammar.

Authors:
**Cleverson Ledur** (Creator) 

**Dalvan Griebler** (Contributor and Mentoring)

**Isabel Mansur** (Mentoring)

**Luiz G. Fernandes** (Mentoring)

Reference Paper:



Other scientific contributions:



GMaVis' compiler is used to recognize GMaVis' code and transform it in a geospatial data visualizations.

In order to use this compiler, you must inform the file with GMaVis'code.

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

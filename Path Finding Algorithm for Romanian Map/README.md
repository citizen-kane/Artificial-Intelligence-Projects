Find and Compare results of DFS, BFS and A* pathfinding algorithms on the map of Romania.

-----------------------------------------------------------------------------------------

Using files neighbours.txt and locations.txt for node connection and node coordinates respectively to create a Graph of the Romania road network and analyse how different Path-Finding algorithms work on them. 

1. neighbours.txt

	This file will only have the detail about the connection between the cities to help draw a graph of the map.
	
	This file will have the NUMBER OF CITIES in the first row
	
	Then it will have: -source city- -destination city- -distance-

2. locations.txt

	This file will have the latitude longitude of each city in the following format:
	
	-city- -latitude- -longitude-
	
	This file will NOT have the number of cities.

-----------------------------------------------------------------------------------------

Compile and Execution:
Please compile the code using the following command:

g++ untitled.cpp -o a

Please execute the code using:
\./a \<type> \<sourceCity> \<destinationCity>

\<type>	:		BFS, DFS, A*, BFSvsDFS, DFSvsA*

example:
./a DFS urziceni mehadia

-----------------------------------------------------------------------------------------

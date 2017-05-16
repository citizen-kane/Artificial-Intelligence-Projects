======================================================================================================================================================================================================
Prepare FILES for reading
======================================================================================================================================================================================================
No Use of roads.pl file for this code. Need to prepare the following two files for node connection and node coordinates respectively.

1. neighbours.txt

This file will only have the detail about the connection between the cities to help draw a graph of the map.
This file will have the NUMBER OF CITIES in the first row
Then it will have the <source city> <destination city> <distance>

The file will look like below for the given example:
20
oradea zerind 71
zerind arad 75
arad timisoara 118
timisoara lugoj 111
lugoj mehadia 70
dobreta mehadia 75
oradea sibiu 151
arad sibiu 140
dobreta craiova 120
sibiu rimnicu_vilcea 80
sibiu fagaras 99
rimnicu_vilcea craiova 146
pitesti craiova 138
rimnicu_vilcea pitesti 97
bucharest pitesti 101
bucharest fagaras 211
bucharest giurgiu 90
bucharest urziceni 85
vaslui urziceni 142
hirsova urziceni 98
hirsova eforie 86
vaslui iasi 92
neamt iasi 87


2. locations.txt

This file will have the latitude longitude of each city in the following format:
<city> <latitude> <longitude>
This file will NOT have the number of cities.

The filw will look like below for the following example:
arad 46.16667 21.3
bucharest 44.41667 26.1
craiova 44.33333 23.81667
dobreta 44.5 23.95
eforie 44.06667 28.63333
fagaras 45.84472 24.97417
giurgiu 43.90083 25.97389
hirsova 46.68333 27.53333
iasi 47.16222 27.58889
lugoj 45.68611 21.90056
mehadia 44.90083 22.35028
neamt 46.9275  26.37083
oradea 47.07222 21.92111
pitesti 44.86056 24.86778
rimnicu_vilcea 45.10472 24.37556
sibiu 45.79583 24.15222
timisoara 45.75972 21.23
urziceni 44.71806 26.64528
vaslui 46.63833 27.72917
zerind 46.63333 21.66667


please note: PLEASE DO NOT HAVE AN EXTRA LINE IN THE END OF ANY OF THE FILES. PLEASE LOOK AT BOTH THE FILES IN THE FOLDER FOR ANY CLARIFICATIONS.

======================================================================================================================================================================================================
Compile and Execution:
======================================================================================================================================================================================================
Please compile the code using the following command:

g++ untitled.cpp -o a

Please execute the code using:
./a <type> <sourceCity> <destinationCity>

<type>	:	BFS
			DFS
			A*
			BFSvsDFS
			DFSvsA*

example:
./a DFS urziceni mehadia

======================================================================================================================================================================================================
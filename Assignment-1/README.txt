You can import the project into any IDE of your preference, since the code is platform-independent. 
Alternatively you can use the provided makefile as "make && /.main" using gcc version > 5 (c++17).

DO NOT INCLUDE ANY OTHER LIBRARIES. ONLY C++ STL IS PERMITTED.
C++17 is OK (i.e. gcc version > 5). C++11 will crash the std::chrono imports.


Brief Intro:

The main.cpp file controls the grading functions and calls the Geographical Data Manager (GPOs) to instatiate a grid index.

The GPOs class is an interface to the spatial "Grid" index. In the future we may also have an "Rtree" spatial index that stores checkins in place of the grid index.

The Grid Index is in GPOs/grid folder. It contains classes for storing the entire grid structure (Grid.h), the individual cells (Cell.h) and individual checkins in each cell (called "Point.h").

You will be primarily working in Grid.cpp. Refer to functions getkNN and getRange for hints on the implementation.

/Utilities/utilities.h defines equirectangular distance approximation function. It is also available in Point.cpp and Cell.cpp.
Pay keen attention to whether you are computing distances in km or geo-coordinate distance on the lat,lng.

headers.h defines some global constants (BOUNDARY_ERROR,etc) and includes all necessary standard libraries I could think of.

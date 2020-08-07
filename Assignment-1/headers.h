#ifndef HEADER_H
#define HEADER_H


// Standard includes
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <map>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <stdint.h>
#include <stdarg.h>
#include <errno.h>
#include <bitset>

/// @brief The usual PI/180 constant
#define DEG_TO_RAD 0.017453292519943295769236907684886

/// @brief Earth's quatratic mean radius for WGS-84
#define EARTH_RADIUS_IN_KILOMETERS 6371
#define EARTH_CIRCUMFERENCE 40075.017

/// @brief special constants
#define EULERS_NUMBER 2.718281828459045
#define BOUNDARY_ERROR 0.000001

// These are global variables that control the grid spatial extent, its granularity and the cell dimensions.
extern double DATASET_SIZE;
extern double MIN_LAT ;
extern double MAX_LAT ;
extern double MIN_LON ;
extern double MAX_LON ;
extern double DELTA_LON ;
extern double DELTA_LAT ;

// Grid size (or granularity)
#define X_granularity 2000
#define Y_granularity 1000

// Cell type
// it is used to store the following types of objects in the same heap
#define CELL 0
#define RECTANGLE 1
#define POINT 2

// Directions in clockwise
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

//basic includes for the makefile.
#include "GPOs/grid/Point.h"
#include "utilities/utilities.h"
#include "GPOs/grid/Cell.h"
#include "GPOs/grid/Grid.h"
#include "GPOs/GPOs.h"

#endif

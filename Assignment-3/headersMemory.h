
#ifndef HEADERSMEMORY_H
#define HEADERSMEMORY_H

#include "headers.h"

extern double DATASET_SIZE;
#define X_granularity 400 // table[X][Y]   
#define Y_granularity 400
extern double MIN_LON;
extern double MIN_LAT;
extern double MAX_LON;
extern double MAX_LAT;


//#define DATASET_SIZE 10000

/// @brief The usual PI/180 constant
#define DEG_TO_RAD 0.017453292519943295769236907684886

/// @brief Earth's quatratic mean radius for WGS-84
#define EARTH_RADIUS_IN_KILOMETERS 6371
#define EARTH_CIRCUMFERENCE 40075.017

extern double DELTA_LON ;
extern double DELTA_LAT ;

// Cell type, it is used for the heaps
#define CELL 0
#define RECTANGLE 1
#define POINT 2

// CPM directions
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#include "GPOs/MemoryGrid/grid/Point.h"
#include "GPOs/MemoryGrid/grid/Cell.h"
#include "GPOs/MemoryGrid/grid/IncrVisitor.h"
#include "GPOs/MemoryGrid/grid/Visitor.h"
#include "GPOs/MemoryGrid/grid/Grid.h"

//#include "SPOs/MemoryMap/pch.h"
//#include "GPOs/MemoryGrid/headers.h"

#include "GPOs/MemoryGrid/GPOs.h"
#include "SPOs/MemoryMap/Value.h"
#include "SPOs/MemoryMap/SPOs.h"

#endif
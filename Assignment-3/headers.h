#ifndef HEADER_H
#define HEADER_H


#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <math.h>
#include <map>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <cmath>
#include <fstream>
#include <unistd.h>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>

// --------------------- Server

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <winsock2.h>
//#include <netinet/in.h>

// --------------------- Server
#define EARTH_CIRCUMFERENCE 40075.017

using namespace std;


//VLDB dataset
//#define MAXGROUPSIZE 12652
//#define MAXSC 420                  // maximum number of friends plus one
//#define MAXDIST 52.1636             // maximum distance between to points
//#define MAXDIST 0.021636

//austin dataset from Nick
#define MAXGROUPSIZE 5868
extern int MAXSC;                // maximum number of friends plus one
extern double MAXDIST;          // maximum distance between to points
extern int MAXT;

#define EULERS_NUMBER 2.718281828459045
#define BOUNDARY_ERROR 0.00000000000001


#include "utilities/res_point.h"
#include "utilities/utilities.h"
#include "utilities/Group.h"

#include "GPOs/IGPOs.h"
#include "SPOs/ISPOs.h"

#include "basicGSQueries/BasicGSQueries.h"
#include "complexQueries/topkUsers.h"

#endif
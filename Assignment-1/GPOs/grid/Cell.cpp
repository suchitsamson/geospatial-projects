#include "../../headers.h"

Cell::Cell(){
    x1 = new double;
    x2 = new double;                  //  |-----X2
    y1 = new double;                  //  |     |
    y2 = new double;                  //  X1----|

	// We assume that all cells have order_id less than 0 (Can you explain why?)
	// Can be modified to your own preference
    c_order_id = std::numeric_limits<int>::min();
}

Cell::~Cell(){

    delete x1;
    delete x2;
    delete y1;
    delete y2;

    if(checkIns != NULL){
        while(!checkIns->empty()) {
            delete checkIns->back();
            checkIns->pop_back();
        }
    }
    delete checkIns;
}


void Cell::setIndex(int c_i, int c_j){
    i = c_i;
    j = c_j;
}

int Cell::getIndexI(){
    return i;
}

int Cell::getIndexJ(){
    return j;
}

int Cell::getCheckinCount(){
    if(checkIns == NULL)
        return 0;

    return checkIns->size();
}

void Cell::setDimensions(double x_1, double y_1, double x_2, double y_2){
    *x1 = x_1;
    *x2 = x_2;
    *y1 = y_1;
    *y2 = y_2;
}


void Cell::newCheckIn(Point* user){
    if(checkIns == NULL){
        checkIns = new std::list<Point*>();
    }
    checkIns->push_back(user);
}


std::list<Point*>* Cell::getCheckIns(){
    return checkIns;
}

void Cell::setType(int type){
    cell_type = type;
}

int Cell::getType(){
    return cell_type;
}


//----------------------------------
double Cell::getX1(){ return *x1;}

double Cell::getY1(){ return *y1;}

double Cell::getX2(){ return *x2;}

double Cell::getY2(){ return *y2;}

void Cell::setOrderID(int id){
    c_order_id = id;
}

int Cell::getOrderID(){
    return c_order_id;
}

//----------------------------------

// Compute the minimum distance, in other words, the distance between the nearest corner of the Cell to (x, y) and (x, y). Then update c_minDist
// Editing this function may cause float accuracy issues. If you must do it, please edit with caution.
double Cell::computeMinDist(double x, double y){

    c_minDist = 0.0;
    double x_var = x, y_var = y, u, v, lat1r, lat2r, lon1r, lon2r;

	lat1r = DEG_TO_RAD * y;
	lon1r = DEG_TO_RAD * x;

    if (x < *x1){
        x_var = *x1;
    }
    else if (x > *x2){
        x_var = *x2;
    }

	if (y < *y1) {
		y_var = *y1;
	}
	else if (y > * y2) {
		y_var = *y2;
	}

	lat2r = DEG_TO_RAD * y_var;
	lon2r = DEG_TO_RAD * x_var;

    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);

	c_minDist = 2.0 * EARTH_RADIUS_IN_KILOMETERS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

    return c_minDist;
}

// Returns true if the cell has parts inside the circle centered at (x, y) and radius
// DO NOT CHANGE THIS FUNCTION
bool Cell::intersectsWithCircle(double x, double y, double radius){

    double dist = computeMinDist(x, y);

    if (dist - radius > BOUNDARY_ERROR)
        return false;

    return true;
}


//----------------------------------------------

// Check if all cells corners lay into the circle
// DO NOT CHANGE THIS FUNCTION
bool Cell::fullyCoveredByCircle(double x, double y, double radius){

    if(utilities::distanceBetween(y, x, *y1, *x1) <= radius){
        if(utilities::distanceBetween(y, x, *y2, *x1) <= radius){
            if(utilities::distanceBetween(y, x, *y1, *x2) <= radius){
                if(utilities::distanceBetween(y, x, *y2, *x2) <= radius){
                    return true;
                }else
                    return false;
            }else
                return false;
        }else
            return false;
    }else
        return false;

}


void Cell::setDirection(int direction){
    c_direction = direction;
}

int Cell::getDirection(){
    return c_direction;
}

double Cell::getMinDist(){
    return c_minDist;
}

void Cell::setMinDist(double dist){
    c_minDist = dist;
}

//test
void Cell::setPoint(Point* p){
    point = p;
}

Point* Cell::getPoint(){
    return point;
}

void Cell::setIndex1(int c_i, int c_j){
    i1 = c_i;
    j1 = c_j;
}

int Cell::getIndexI1(){
    return i1;
}

int Cell::getIndexJ1(){
    return j1;
}

int Cell::getLevel(){
    return level;
}

void Cell::setLevel(int l){
     level = l;
}
//test

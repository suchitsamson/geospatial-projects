#include "../../../headersMemory.h"

Cell::Cell(){
    cell_type = CELL;
    checkIns = new list<Point*>();

    // ---------------------------------
    x1 = new double;
    x2 = new double;                  //  |-----X2
    y1 = new double;                  //  |     |
    y2 = new double;                  //  X1----|

    numOfPoints = 0;
}

Cell::~Cell(){

    delete x1;
    delete x2;
    delete y1;
    delete y2;


    while(!checkIns->empty()) {
        delete checkIns->back();
        checkIns->pop_back();
    }
    delete checkIns;
};


void Cell::deleteCheckIn(Point* p){
    //cout << "Delete checkin" << endl;
    for(list<Point*>::iterator it = checkIns->begin(); it != checkIns->end(); ++it){
        if((*it)->getID() == p->getID()){
            //cout << "To vrika!" << endl;
            checkIns->erase(it);
            break;
        }
    }

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

void Cell::setDimensions(double x_1, double y_1, double x_2, double y_2){
    *x1 = x_1;
    *x2 = x_2;
    *y1 = y_1;
    *y2 = y_2;

    /*	x1 = x_1;
        x2 = x_2;
        y1 = y_1;
        y2 = y_2;
*/
}


void Cell::newCheckIn(Point* user){
    checkIns->push_back(user);
}    


list<Point*>* Cell::getCheckIns(){
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

void Cell::setID(int id){
    c_id = id;
}

int Cell::getID(){
    return c_id;
}


//---------------------------------

double Cell::computeMinDist(double x, double y){

	c_minDist = 0.0;
	double x_var = x, y_var = y, u, v, lat1r, lat2r, lon1r, lon2r;

	lat1r = DEG_TO_RAD * y;
	lon1r = DEG_TO_RAD * x;

	if (x < *x1) {
		x_var = *x1;
	}
	else if (x > * x2) {
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

	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);

	c_minDist = 2.0 * EARTH_RADIUS_IN_KILOMETERS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

	return c_minDist;
}

bool Cell::intersectsWithCircle(double x, double y, double radius){

    double dist = computeMinDist(x, y);

    if (dist - radius > 0)
        return false;

    return true;
}


double Cell::intersectedVolumeWithRectangle(double x_1, double y_1, double x_2, double y_2){

    if(x_1 < MIN_LON)
        x_1 = MIN_LON;
    else if(x_1 > MAX_LON)
        x_1 = MAX_LON;

    if(x_2 < MIN_LON)
        x_2 = MIN_LON;
    else if(x_2 > MAX_LON)
        x_2 = MAX_LON;

    if(y_1 < MIN_LAT)
        y_1 = MIN_LAT;
    else if(y_1 > MAX_LAT)
        y_1 = MAX_LAT;

    if(y_2 < MIN_LAT)
        y_2 = MIN_LAT;
    else if(y_2 > MAX_LAT)
        y_2 = MAX_LAT;


    double x_overlap = max(0.0, abs(min(*x2, x_2) - max(*x1, x_1)));
    double y_overlap = max(0.0, abs(min(*y2, y_2) - max(*y1, y_1)));

    /*
    if(x_overlap - DELTA_LON > 0)
        cout << " ---------------------------Error x_overlap = " << x_overlap << "\t DELTA_LON = " << DELTA_LON << endl;
    if(y_overlap - DELTA_LAT > 0)
        cout << " ---------------------------Error y_overlap = " << y_overlap << "\t DELTA_LAT = " << DELTA_LAT << endl;

    */
    return x_overlap*y_overlap;
}

//----------------------------------------------

// Check if all cells corners lay into the circle
bool Cell::fullyCoveredByCircle(double x, double y, double radius){

    if(sqrt(pow(x-*x1, 2.0) + pow(y-*y1, 2.0)) <= radius){
        if(sqrt(pow(x-*x1, 2.0) + pow(y-*y2, 2.0)) <= radius){
            if(sqrt(pow(x-*x2, 2.0) + pow(y-*y1, 2.0)) <= radius){
                if(sqrt(pow(x-*x2, 2.0) + pow(y-*y2, 2.0)) <= radius){
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

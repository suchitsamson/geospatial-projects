#include "../../../headersMemory.h"           

Point::Point (){} 

Point::Point (double x, double y, int id){


    p_x = x;
    p_y = y;
    p_id = id;

}

Point::~Point (){
    /*
    delete p_x;
    delete p_y;
    delete p_id;
*/
}


double Point::getX(){return p_x;} 

double Point::getY(){return p_y;}

int Point::getID(){return p_id;}          
			            
double Point::computeMinDist(double x, double y){
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = DEG_TO_RAD * y;
	lon1r = DEG_TO_RAD * x;
	lat2r = DEG_TO_RAD * p_y;
	lon2r = DEG_TO_RAD * p_x;
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return p_minDist = 2.0 * EARTH_RADIUS_IN_KILOMETERS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
} 

void Point::printDetails(){
    cout << "ID = " << p_id << "\t (" << p_x << ", " << p_y << ")" << " dist = " << p_minDist << endl;
}           

double Point::getMinDist(){
    return p_minDist;
}

//Overload the < operator.
bool Point::operator< (const Point& p) const
{
    return p_minDist > p.p_minDist;
}

//Overload the > operator.
bool Point::operator> (const Point& p) const
{
    return p_minDist < p.p_minDist;
}

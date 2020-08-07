#include "../../headers.h"

Point::Point (){}

Point::Point (double lon, double lat, int order_id){
    p_x = lon;
    p_y = lat;
    p_order_id = order_id;
}

int Point::getOrderID() {
	return p_order_id;
}

double Point::getX() {
	return p_x;
}

double Point::getY() {
	return p_y;
}

double Point::getMinDist() {
	return p_minDist;
}

// Distance in Kilometers from the Point to a given (x, y). Update p_minDist with such value
// Editing this function may cause float accuracy issues. If you must do it, please edit with caution.
double Point::computeMinDist(double x, double y){
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = DEG_TO_RAD * y;
    lon1r = DEG_TO_RAD * x;
    lat2r = DEG_TO_RAD * p_y;
    lon2r = DEG_TO_RAD * p_x;
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return p_minDist = 2.0 * EARTH_RADIUS_IN_KILOMETERS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//usefull for debugging.
void Point::print(){
    std::cout << "Order:" << p_order_id << " (" << p_x << ", " << p_y << ") dist: " << p_minDist << " km \n";
}

//Overload the < operator.
bool Point::operator< (const Point& p) const
{
	if (p_minDist > p.p_minDist) return true;
	if (p_minDist == p.p_minDist) {
		if (p_order_id > p.p_order_id)
			return true;
	}
	return false;
}

//Overload the > operator.
bool Point::operator> (const Point& p) const
{
	if (p_minDist < p.p_minDist) return true;
	if (p_minDist == p.p_minDist) {
		if (p_order_id < p.p_order_id)
			return true;
	}
	return false;
}

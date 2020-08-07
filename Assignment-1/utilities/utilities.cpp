#include "../headers.h"

// Compute distance between (lon1, lat1) and (lon2, lat2)
// Editing this function may cause float accuracy issues. If you must do it, please edit with caution.
double utilities::distanceBetween(double lat1, double lon1, double lat2, double lon2) {
		double lat1r, lon1r, lat2r, lon2r, u, v;
		lat1r = DEG_TO_RAD * lat1;
		lon1r = DEG_TO_RAD * lon1;
		lat2r = DEG_TO_RAD * lat2;
		lon2r = DEG_TO_RAD * lon2;
		u = sin((lat2r - lat1r) / 2);
		v = sin((lon2r - lon1r) / 2);
		return (2.0 * EARTH_RADIUS_IN_KILOMETERS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)));
}

// Compute the intersection of two sets. 
// DO NOT CHANGE THIS FUNCTION
size_t utilities::computeSetIntersection(std::unordered_set<size_t>& _f1, std::unordered_set<size_t>& _f2) {
		size_t intersections = 0;
		
		if (_f1.size() == 0 || _f2.size() == 0)
			return 0;
		if (_f1.size() > _f2.size()) {
			for (auto it = _f2.begin(); it != _f2.end(); it++) {
				size_t id = *it;
				if (_f1.find(id) != _f1.end()) {
					intersections++;
				}
			}
		}
		else {
			for (auto it = _f1.begin(); it != _f1.end(); it++) {
				size_t id = *it;
				if (_f2.find(id) != _f2.end()) {
					intersections++;
				}
			}
		}
		return intersections;
}
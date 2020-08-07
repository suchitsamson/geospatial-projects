class Point {

public:
    Point ();
    Point (double x, double y, int order_id);

	int getOrderID();
	double getX();
	double getY();
	double getMinDist();

	double computeMinDist(double x, double y);
    void print();

    //Overload the < operator.
    bool operator< (const Point& p) const;
    //Overload the > operator.
    bool operator> (const Point& p) const;

	// Comparator function. Compare by Distance first, if tied Order_id second.
    struct ascending : public std::binary_function<Point*, Point*, bool>
    {
		bool operator()(const Point* __x, const Point* __y) const {

			// Handle corner cases that p_minDist doesn't have a value
			if (std::isnan(__x->p_minDist)) return true;
			if (std::isnan(__y->p_minDist)) return false;

			if (__x->p_minDist - __y->p_minDist > BOUNDARY_ERROR)
				return true;
			else
				if (fabs(__x->p_minDist - __y->p_minDist) < BOUNDARY_ERROR)
					return (__x->p_order_id > __y->p_order_id);

            return false ;
        }
    };


public:
    int p_order_id;
    double p_minDist;
    double p_x, p_y;
};


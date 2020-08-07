class Cell {

public:
	// Comparator function. Distance first, Order_id second.
    struct ascending : public std::binary_function<Cell*, Cell*, bool>
    {
        bool operator()(const Cell* __x, const Cell* __y) const {

			// Handle corner cases that c_minDist doesn't have a value
			if (std::isnan(__x->c_minDist)) return true;
			if (std::isnan(__y->c_minDist)) return false;
		
			if (__x->c_minDist - __y->c_minDist > BOUNDARY_ERROR)
				return true;
			else
				if (fabs(__x->c_minDist - __y->c_minDist) < BOUNDARY_ERROR)
					return (__x->c_order_id > __y->c_order_id);
            return false;
        }
    };

public:
    Cell ();
    virtual ~Cell();

    virtual void newCheckIn(Point* user);
    virtual double computeMinDist(double x, double y);
    virtual bool intersectsWithCircle(double x, double y, double radius);
    virtual bool fullyCoveredByCircle(double x, double y, double radius);

    virtual void setDimensions(double x_1, double y_1, double x_2, double y_2);
    virtual void setOrderID(int id);
    virtual void setType(int type);
    virtual void setDirection(int direction);
    virtual void setMinDist(double dist);

    virtual std::list<Point*>* getCheckIns();
    virtual double getX1();
    virtual double getY1();
    virtual double getX2();
    virtual double getY2();
    virtual int getOrderID();
    virtual int getType();
    virtual int getDirection();
    virtual double getMinDist();
    void setIndex(int c_i, int c_j);
    int getIndexI();
    int getIndexJ();
    int getCheckinCount();
    //test
    virtual void setPoint(Point* p);
    virtual Point* getPoint();
    virtual void setIndex1(int a, int b);
    virtual int getIndexI1();
    virtual int getIndexJ1();
    virtual void setLevel(int a);
    virtual int getLevel();
    //test


private:
    double *x1, *x2, *y1, *y2;
    std::list<Point*>* checkIns = NULL;
    int cell_type;
    int c_order_id;
    int c_direction;
    double c_minDist;
    // int numOfPoints;
    int i, j;
    //test
    Point* point;
    int i1,j1,level;
    //test

};


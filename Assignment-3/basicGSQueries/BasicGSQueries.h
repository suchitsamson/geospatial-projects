class SimpleQueries{

private:
    IGPOs *gpos;
    ISPOs *spos;
    Utilities util;
    char f[3];
public:
    SimpleQueries(IGPOs *spatialIndex, ISPOs *socialGraph);
    ~SimpleQueries();

    Group* getClosestFriends(double x, double y, res_point* user, unsigned int m);    
    Group* getMyFriendsInRange(double x, double y, double radius, res_point* user);

};


class topkUsers{

private:
    IGPOs *gpos;
    ISPOs *spos;
    SimpleQueries *sq;
    Utilities util;

public:

    topkUsers(IGPOs *spatialIndex, ISPOs *socialGraph, SimpleQueries *simpleQueries);
    ~topkUsers();

	Group* NSG(double x, double y, int m);


	// Group* NSG_lazy(double x, double y, int m);
	// Group* NSG_bruteforce(double x, double y, int m);
	// Group* NSG_eagerstar(double x, double y, int m);
};


#include "../headers.h"

class GPOs
{

private:
    Grid *grid;
	bool loadLocations(const char* filename);

public:
    GPOs(const char* checkins_file);
	~GPOs();
	void getkNN(double x, double y, int k, std::vector<Point*>& results);
	void getRange(double x, double y, double radius, std::vector<Point*>& results);
};



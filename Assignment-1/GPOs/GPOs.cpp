#include "../headers.h"

GPOs::GPOs (const char* checkins_file){
  grid = new Grid;
  loadLocations(checkins_file);
}

GPOs::~GPOs(){
  delete grid;
}

// Load locations from file. DO NOT CHANGE THIS FUNCTION except for std::cout or std::cerr
bool GPOs::loadLocations(const char* fileName){
  std::cout << "Loading checkins from " << fileName << std::endl;
  std::ifstream fin(fileName);

  if (!fin) {
    std::cerr << "Cannot open checkins file " << fileName << std::endl;
    return false;
  }

  int user_id, order_id = 0;
  std::string location_id;
  double lat, lon, hours_since_epoch ;

  while (fin){
	if (!fin.good()) {
		  std::string blank;
		  std::getline(fin, blank);
		  continue;
	}
    fin >> user_id >> location_id >> hours_since_epoch >> lat >> lon;
	assert(lat < MAX_LAT && lat > MIN_LAT && lon < MAX_LON && lon > MIN_LON);

	//ignore location_id, user_id and hours_since_epoch for Assignment 1

    //Create a new point with (LON, LAT), and give the point an order id, based on order of reading from file. 
    Point* l;
    l = new Point(lon, lat, order_id);
    grid->addCheckIn(l);
    order_id++;
  }

  fin.close();

  std::cout << "------- LOADED GPOS from FILE --------- " << std::endl;
  std::cout << "Done! Number of lines parsed: " <<  order_id << std::endl;
  std::cout << " -------------------------------------- " << std::endl;

  return true;
}

void GPOs::getkNN(double x, double y, int k, std::vector<Point*>& results){
  grid->getkNN(x, y, k, results);
}

void GPOs::getRange(double x, double y, double radius, std::vector<Point*>& results){
  grid->getRange(x, y, radius, results);
}



#include "../../headers.h"

Grid::Grid (){
    locations = new std::map<int , Point*>();
    std::cout << "MIN_LON = " << MIN_LON << " MAX_LON = " << MAX_LON << " DELTA_LON = " << DELTA_LON << std::endl;
    std::cout << "MIN_LAT = " << MIN_LAT << " MAX_LAT = " << MAX_LAT << " DELTA_LAT = " << DELTA_LAT << std::endl;
    std::cout << "GRID SETUP COMPLETE" << std::endl;
}

Grid::~Grid (){
    for (int i=0; i<X_granularity; i++){
        for (int j=0; j<Y_granularity; j++){
            delete table[i][j];
        }
    }
    delete locations;
}

// Get the Cell* that contains coordinaates (lon, lat)
Cell* Grid::getCell(double x, double y){
	// get corresponding coordinate for given lon, lat
    int q_x = (int)((x - MIN_LON)/DELTA_LON);
    int q_y = (int)((y - MIN_LAT)/DELTA_LAT);

    if(q_x >=0 && q_x < X_granularity && q_y >=0 && q_y < Y_granularity)
        return table[q_x][q_y];
    else
        return NULL;
}

// Get the Cell with index (i, j) of Grid
Cell* Grid::getCell(int i, int j){
    if(i >= 0 && j >= 0 && i < X_granularity && j < Y_granularity)
        return table[i][j];
    else
        return NULL;

}

// Create the Cell object inside the Grid
Cell* Grid::makeCell(double x, double y){
    int q_x = (int)((x - MIN_LON)/DELTA_LON);
    int q_y = (int)((y - MIN_LAT)/DELTA_LAT);

    if(q_x <0) q_x = 0; 
    if(q_y <0) q_y = 0; 
    if(q_x >X_granularity) q_x = X_granularity; 
    if(q_y >Y_granularity) q_y = Y_granularity; 

    if (table[q_x][q_y] != NULL){
        return table[q_x][q_y];
    }

    Cell* c = new Cell;
    c->setDimensions(MIN_LON+(q_x*DELTA_LON), MIN_LAT+(q_y*DELTA_LAT), MIN_LON+((q_x+1)*DELTA_LON), MIN_LAT+((q_y+1)*DELTA_LAT));
    c->setType(CELL);
    c->setIndex(q_x, q_y);
    table[q_x][q_y] = c;

    return c;
}

// Record a new checkin, and mark it in Grid
bool Grid::addCheckIn(Point* checkin){
    Cell * c = makeCell(checkin->getX(),checkin->getY());
	
    if(c != NULL){
        c->newCheckIn(checkin);
		// checkin->print();
        int id = checkin->getOrderID();
        locations->insert(std::pair<int, Point*>(id, checkin));
        return true;
    }
    else{
        std::cerr<<"Something is terribly wrong."<<std::endl;
        exit(-1);
    }
	return false;
}


// TODO::
// Update your answers in the vector "results", which should contains Point* of k nearest neighbors of (x, y) in format of (lon, lat)
// The order of k nearest neighbors inside "results" is not important. However, if two points are the same distance away return the one with the smaller order_id.
// Recommended implementation is a Best-First Search algorithm which utilizes a priority_queue with a custom comparator function.
// You can use/emulate the one I have in Cell.h file.
// You may need to implement helper functions and also 
void Grid::getkNN(double lon, double lat, int k, std::vector<Point*>& results){

    double x = lon; double y = lat;
    if(k > DATASET_SIZE) k = DATASET_SIZE;

    //-----------YOUR CODE HERE----

    std::priority_queue <Cell*, std::vector<Cell*>, Cell::ascending> pq;
    int ctr=0,orig_i=getIntI(lon),orig_j=getIntJ(lat),row,col;

    if(table[orig_i][orig_j] != NULL){
        pq.push(table[orig_i][orig_j]);
        pq.top()->setMinDist(0);
    }

    pushRectangle(orig_i,orig_j,1,UP,lon,lat,pq);
    pushRectangle(orig_i,orig_j,1,RIGHT,lon,lat,pq);
    pushRectangle(orig_i,orig_j,1,DOWN,lon,lat,pq);
    pushRectangle(orig_i,orig_j,1,LEFT,lon,lat,pq);

    while(ctr<k){
        Cell* top = pq.top();
        pq.pop();
        //there is a cell with min Distance to query point
        if(top->getType() == CELL){
            for (auto it = top->getCheckIns()->begin(); it != top->getCheckIns()->end(); ++it) {
                (*it)->computeMinDist(lon, lat);
                Cell* c = new Cell;
                c->setType(POINT);
                c->setMinDist((*it)->getMinDist());
                c->setOrderID((*it)->getOrderID());
                c->setPoint(*it);
                pq.push(c);
            }
        }
        //there is a rectangle with min distance
        if(top->getType() == RECTANGLE){
            //insert cells in the rectangle to the priority queue
            for(row=top->getIndexI(); row<top->getIndexI1(); row++){
                for(col=top->getIndexJ(); col<top->getIndexJ1(); col++){
                    if(table[row][col] != NULL){
                        table[row][col]->computeMinDist(lon, lat);
                        pq.push(table[row][col]);
                    }
                }
            }

            //insert next bigger rectangle in same direction
            pushRectangle(orig_i,orig_j,(top->getLevel())+1,top->getDirection(),lon,lat,pq);
        }

        //there is a point with min distance
        if(top->getType() == POINT){
            results.push_back(new Point((top->getPoint())->getX(), (top->getPoint())->getY(), (top->getPoint())->getOrderID()));
            ctr++;
        }
    }

    //-----------------------------
}


// TODO::
// "push_back" your answers in the vector "results", which should contains Point* of all checkins inside the circle of size "radius",
//     of which center is (x, y) in format of (lon, lat)
// The order of checkins inside "results" is not important. However, if two points are the same distance away return the one with the smaller order_id.
// Watch out boundary cases and float accuracy issues when finishing this function. 
void Grid::getRange(double lon, double lat, double radius, std::vector<Point*>& results){

    double x = lon; double y = lat;

	// NOTE: radius is in km. Need to transfer into geo distance; lon & lat have different transformation
	double radius_lat = radius * 360 / EARTH_CIRCUMFERENCE;                            // radius_lat is equal no matter the lon
	double radius_lon = radius * 360 / (EARTH_CIRCUMFERENCE * cos(y * DEG_TO_RAD));    // radius_lon changes according to the value of lat

    //------------YOUR CODE HERE----

    double adjust_lon_max = (lon+radius_lon > MAX_LON)? MAX_LON : lon+radius_lon;
    double adjust_lon_min = (lon-radius_lon<MIN_LON)?MIN_LON:lon-radius_lon;
    double adjust_lat_max = (lat+radius_lat>MAX_LAT)?MAX_LAT:lat+radius_lat;
    double adjust_lat_min = (lat-radius_lat<MIN_LAT)?MIN_LAT:lat-radius_lat;
    
    //if circle inside a cell, below code takes care of it. range would be that cell only.
    for(int r=getIntI(adjust_lon_min); r<=getIntI(adjust_lon_max); r++){
        for(int c=getIntJ(adjust_lat_min); c<=getIntJ(adjust_lat_max); c++) {
            if(table[r][c] != NULL){
                //cell fully covered in circle->all points in it in result
                if(table[r][c]->fullyCoveredByCircle(lon, lat, radius)){
                    for (auto it = table[r][c]->getCheckIns()->begin(); it != table[r][c]->getCheckIns()->end(); ++it) {
                        results.push_back(new Point((*it)->getX(), (*it)->getY(), (*it)->getOrderID()));
                    }
                }
                //if cell intersection with circle->check each point individually in grid for it's dist from the point 
                else if(table[r][c]->intersectsWithCircle(lon, lat, radius)) {
                    for (auto it = table[r][c]->getCheckIns()->begin(); it != table[r][c]->getCheckIns()->end(); ++it) {
                        if((*it)->computeMinDist(lon, lat) < radius){
                            results.push_back(new Point((*it)->getX(), (*it)->getY(), (*it)->getOrderID()));
                        }
                    }
                }
            }
        }
    }

    //------------------------------
}
//test
int Grid::getIntI(double x){
	// get corresponding coordinate for given lon, lat
    int q_x = (int)((x - MIN_LON)/DELTA_LON);
    
    if(q_x >=0 && q_x < X_granularity){
        return q_x;
    } else if(q_x < 0){
        return 0;
    } else {
        return X_granularity - 1;
    } 
}

int Grid::getIntJ(double y){
	// get corresponding coordinate for given lon, lat
    int q_y = (int)((y - MIN_LAT)/DELTA_LAT);
    
    if(q_y >=0 && q_y < Y_granularity){
        return q_y;
    } else if(q_y < 0){
        return 0;
    } else {
        return Y_granularity - 1;
    } 
}

void Grid::pushRectangle(int i, int j, int level, int direction, double longi, double lati, std::priority_queue <Cell*, std::vector<Cell*>, Cell::ascending>& p){
    Cell* temp = new Cell;
    if(direction == UP){
        temp->setDimensions(MIN_LON+((i+level)*DELTA_LON), MIN_LAT+((j-level+1)*DELTA_LAT), MIN_LON+((i+level+1)*DELTA_LON), MIN_LAT+((j+level+1)*DELTA_LAT));
        temp->setDirection(UP);
        temp->setIndex(i+level, j-level+1);
        temp->setIndex1(i+level+1, j+level+1);
    } else if(direction == RIGHT){
        temp->setDimensions(MIN_LON+((i-level)*DELTA_LON), MIN_LAT+((j+level)*DELTA_LAT), MIN_LON+((i+level)*DELTA_LON), MIN_LAT+((j+level+1)*DELTA_LAT));
        temp->setDirection(RIGHT);
        temp->setIndex(i-level, j+level);
        temp->setIndex1(i+level, j+level+1);
    } else if(direction == DOWN){
        temp->setDimensions(MIN_LON+((i-level)*DELTA_LON), MIN_LAT+((j-level)*DELTA_LAT), MIN_LON+((i-level+1)*DELTA_LON), MIN_LAT+((j+level)*DELTA_LAT));
        temp->setDirection(DOWN);
        temp->setIndex(i-level, j-level);
        temp->setIndex1(i-level+1, j+level);
    } else {
        temp->setDimensions(MIN_LON+((i-level+1)*DELTA_LON), MIN_LAT+((j-level)*DELTA_LAT), MIN_LON+((i+level+1)*DELTA_LON), MIN_LAT+((j-level+1)*DELTA_LAT));
        temp->setDirection(LEFT);
        temp->setIndex(i-level+1, j-level);
        temp->setIndex1(i+level+1, j-level+1);
    }
    temp->setType(RECTANGLE);
    temp->computeMinDist(longi, lati);
    temp->setLevel(level);
    p.push(temp);
}
//test






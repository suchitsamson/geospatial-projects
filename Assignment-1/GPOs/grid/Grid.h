class Grid {

private:
    Cell* table[X_granularity+1][Y_granularity+1];
    int x, y;
    std::map<int , Point*>* locations;

public:
    Grid ();
    ~Grid ();

    Cell* getCell(double x, double y);
    Cell* getCell(int i, int j);
    bool addCheckIn(Point* user);

    void getkNN(double x, double y, int k, std::vector<Point*>& results);
    void getRange(double x, double y, double radius, std::vector<Point*>& results);

    Cell* makeCell(double x, double y);
    //test
    int getIntI(double x);
    int getIntJ(double x);
    void pushRectangle(int i, int j, int level, int direction, double longi, double lati, std::priority_queue <Cell*, std::vector<Cell*>, Cell::ascending>& p);
    //test
};


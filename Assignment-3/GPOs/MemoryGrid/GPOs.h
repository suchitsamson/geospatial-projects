#ifndef  GPOS_H
#define  GPOS_H

class GPOs : public IGPOs
{

private:
    map<int, Point*> locations;
    // Point* locations2[DATASET_SIZE];
    map<int, Point*>::iterator it;
    //int* pages;
    int kNNExecutions;
    int LocationExecutions;
    int NextNNExecutions;
    int RangeExecutions;

    // nextNN without the incremental approach of NN
    vector<res_point*>* nextNNList;
    int computedNN, returnedNN, finalNextNN;
    bool flagNextNN;
    int objects;
    Utilities util;
	IncrVisitor *incrVis;
	int pureNNexec;

public:
    Grid *grid;
    GPOs(const char* gridFileName, int numOfFiles = 1);
    GPOs();
    ~GPOs ();
    vector<int> ids;


    virtual void getLocation(int id, double* result);
    virtual res_point* getNextNN_obsolete(double x, double y);
	virtual res_point* getNextNN(double x, double y);

    virtual vector<res_point*>* getkNN(double x, double y, int k);
    virtual vector<res_point*>* getRange(double x, double y, double radius);
    
    virtual void clearNextNN();

    bool loadLocations(const char* fileName);

    void updateCheckin(Point* p);

};
#endif // ! GPOS_H
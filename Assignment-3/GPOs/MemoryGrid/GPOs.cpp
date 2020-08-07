#include "../../headersMemory.h"

GPOs::GPOs (const char* gridFileName, int numOfFiles){
    kNNExecutions = 0;
    LocationExecutions = 0;
    NextNNExecutions = 0;
    RangeExecutions = 0;
	pureNNexec = 0;

    grid = new Grid;

    loadLocations(gridFileName);
	
    objects = 0;

    computedNN = returnedNN = finalNextNN = 0;
    nextNNList = new vector<res_point*>();
    flagNextNN = true;
}    


GPOs::GPOs (){
    kNNExecutions = 0;
    LocationExecutions = 0;
    NextNNExecutions = 0;
    RangeExecutions = 0;
	pureNNexec = 0;

    grid = new Grid;

    objects = 0;

    // nextNN without incremental approach of NN
    computedNN = returnedNN = finalNextNN = 0;
    nextNNList = new vector<res_point*>();
    flagNextNN = true;
}    

GPOs::~GPOs (){

    delete grid;
    delete &locations;
}


void GPOs::getLocation(int id, double* result){
    LocationExecutions++;

    it = locations.find(id);

    if(it!=locations.end()){
        result[0]= (*it).second->getX();
        result[1]= (*it).second->getY();
    }
    else{
        result[0] = -1000;
    }
}


res_point* GPOs::getNextNN_obsolete(double x, double y){
	if(pureNNexec == 0)
		incrVis = new IncrVisitor(x, y);
		
	grid->getNextNN(*incrVis, 1);	

	pureNNexec++;
	
	return incrVis->getNext();
}

res_point* GPOs::getNextNN(double x, double y) {
    int incrStep=500;
	if (computedNN <= returnedNN && flagNextNN) {
		NextNNExecutions++;
		computedNN += incrStep;
		
		vector<res_point*>* kNN = grid->getkNN(x, y, computedNN);
		int size = kNN->size();

		for (int i = returnedNN; i < size; i++) {
			nextNNList->push_back(util.copy((*kNN)[i]));
		}

		while (!kNN->empty()) {
			delete kNN->back();
			kNN->pop_back();
		}
		delete kNN;

		int newNNsize = nextNNList->size();
		
		if (computedNN > newNNsize) { // no more
			flagNextNN = false;
			computedNN = newNNsize;
		}
	}


	if (computedNN > returnedNN) {
		return (*nextNNList)[returnedNN++];
	}
	else {
		return NULL;
	}
}


vector<res_point*>* GPOs::getkNN(double x, double y, int k){
    kNNExecutions++;

    vector<res_point*>* res = grid->getkNN(x, y, k);

    return res;
}


vector<res_point*>* GPOs::getRange(double x, double y, double radius){
    RangeExecutions++;

    vector<res_point*>* res = grid->getRange(x, y, radius);

    return res;
}

void GPOs::updateCheckin(Point* p){
    it = locations.find(p->getID());

    if(it!=locations.end()){
        grid->updateCheckIn(p, (*it).second->getX(), (*it).second->getY());
        locations.insert(pair<int, Point*>(p->getID(), p));
    }
}

bool GPOs::loadLocations(const char* fileName){

    ifstream fin(fileName);
    if (! fin)
    {
        std::cerr << "Cannot open checkins file " << fileName << std::endl;
        return false;
    }

    cout << "HashTable: [ User_id -> location ] Loading from " << fileName << endl;

    int op, id;
    double x1, x2, y1, y2;
    int count = 0;
    Point* u;

    while (fin){
        fin >> op >> id >> x1 >> y1 >> x2 >> y2;
        if (! fin.good()) continue; // skip newlines, etc.
        u = new Point(x1, y1, id);

        //locations2[id] = u;
        locations.insert(pair<int, Point*>(id, u));

        grid->addCheckIn(u);

        ids.push_back(id);

        count ++;
        if(count%100000==0)
            cout << count << endl;
    }

    fin.close();
    cout << "Done! Num of users: " <<  count << endl;
	DATASET_SIZE = count;

    return true;
}

void GPOs::clearNextNN(){

    while(!nextNNList->empty()) {
        delete nextNNList->back();
        nextNNList->pop_back();
    }

    delete nextNNList;
	if (pureNNexec > 0)
		delete incrVis;

    nextNNList = new vector<res_point*>();
    computedNN = returnedNN = finalNextNN = objects = 0;
    flagNextNN = true;
	
	pureNNexec = 0;
}

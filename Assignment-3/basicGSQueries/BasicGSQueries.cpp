#include "../headers.h"

SimpleQueries::SimpleQueries(IGPOs *spatialIndex, ISPOs *socialGraph){
    spos = socialGraph;
    gpos = spatialIndex;
    strcpy(f, "sum");
}

SimpleQueries::~SimpleQueries(){}

// getfriends and get user location
Group* SimpleQueries::getMyFriendsInRange(double x, double y, double radius, res_point* user){

	Group* result = new Group(user, MAXGROUPSIZE, f);
	int* friends;
	unsigned int friendsSize = 0;
	
	/* ------------------ Your code starts here ------------------ */
	// You should "return result;" in this part. If there is no valid result to return, use the code below.
	
	vector<res_point*>* temp = new vector<res_point*>();
	spos->getFriends(user->id, friends, friendsSize);

	for(unsigned int i=0; i< friendsSize; i++){
		double re[2];
		gpos->getLocation(friends[i],re);
		if(re[0]!=-1000 && util.computeMinimumDistance(x,y,re[0],re[1])<radius){
			res_point* r_point = new res_point();
			r_point->id = friends[i];
			r_point->dist = util.computeMinimumDistance(x,y,re[0],re[1]);
			temp->push_back(r_point);
		}
	}
	
	util.sortResPoint_AscendingDist(temp);

	for(auto it=temp->begin(); it!=temp->end(); it++){
		result->addFriend(*it);
	}

	/* ------------------ Your code ends here ------------------ */

	//delete result;
	return result;
}

//get friends, for each one of them compute the mindist and return the k closest
Group* SimpleQueries::getClosestFriends(double x, double y, res_point* user, unsigned int m){

	Group* result = new Group(user, m, f);
	priority_queue <res_point*, vector<res_point*>, res_point_ascending_dist >* heap = new priority_queue <res_point*, vector<res_point*>, res_point_ascending_dist >();
	int* friends;
	unsigned int friendsSize = 0;

	/* ------------------ Your code starts here ------------------ */
	// You should "return result;" in this part. If there is no valid result to return, use the code below.
	
	spos->getFriends(user->id, friends, friendsSize);

	for(unsigned int i=0; i< friendsSize; i++){
		double re[2];
		gpos->getLocation(friends[i],re);
		if(re[0]!=-1000){
			res_point* r_point = new res_point();
			r_point->id = friends[i];
			r_point->dist = util.computeMinimumDistance(x,y,re[0],re[1]);
			heap->push(r_point);
		}
	}

	friendsSize = 0;
	while (!heap->empty() && friendsSize<m-1)
    { 
        result->addFriend(heap->top()); 
		heap->pop();
		friendsSize++;
    } 
	
	/* ------------------ Your code ends here ------------------ */

	//delete result;
	return result;
}
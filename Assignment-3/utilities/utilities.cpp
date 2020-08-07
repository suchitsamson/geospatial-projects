#include "../headers.h"
#include "../headersMemory.h"

Utilities::Utilities(){

    srand((unsigned)time(NULL));

}

Utilities::~Utilities(){}


int Utilities::getRandomInteger(int min, int max){
    //srand((unsigned)time(NULL));
    return (rand()%(max-min+1))+min;

}

double Utilities::getX(int p, int mod){

    int x = rand()%mod;
    int x2 = rand()%1000;

    double f2 = (double)x2/1000000.0f;
    double f  = (double)x/1000.0f;

    return p+f2+f;
}



void Utilities::addToSortedList(int *list,int n,int x){

    int i;
    for(i = n-2; i > 1 && list[i] > x; i--)
        list[i+1] = list[i];

    list[i+1] = x;
}

void Utilities::sortResPoint_AscendingId(vector<res_point*>* vc){

    struct res_point_ascending_id tmp;
    sort(vc->begin(), vc->end(), tmp);

}

void Utilities::sortResPoint_AscendingDist(vector<res_point*>* vc){

    struct res_point_ascending_dist tmp;
    sort(vc->begin(), vc->end(), tmp);
}

// erase from the vector the res_points whose dist is greater than thres
void Utilities::updateUsersInValidRange(vector<res_point*>* res, double thres){
    unsigned int i = 0;
    while(i < res->size()){
        if((*res)[i]->dist > thres)
            res->erase(res->begin()+i);
        else
            i++;
    }
}

/*
Group* Utilities::computeMyGroup(vector<res_point*>* usersInRange, int* friends, int friendsSize, res_point* p, int m){

    Group* result = new Group(p);
    priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist> userFriends;

    int users = usersInRange->size();

    if(friendsSize > users){
        for(int i = 0; i< users; i++){
            if(binarySearch(friends, 0, friendsSize, (*usersInRange)[i]->id))
                userFriends.push(copy((*usersInRange)[i]));
        }
    }
    else{
        for(int i = 0; i< friendsSize; i++){
            res_point* tmp = binarySearch_res_point(usersInRange, 0, users, friends[i]);
            if(tmp != NULL)
                userFriends.push(copy(tmp));
        }
    }

    int j = 0;
    double adist = p->dist;
    while(!userFriends.empty()){
        res_point*tmp = userFriends.top();
        if(j < m){
            adist+=tmp->dist;
            j++;
        }
        result->addFriend(tmp);
        userFriends.pop()
    }
    result->adist = adist;

    return result;

}
*/

bool Utilities::binarySearch(int sortedArray[], int first, int last, int key) {
    // function:
    //   Searches sortedArray[first]..sortedArray[last] for key.
    // returns: index of the matching element if it finds key,
    //         otherwise  -(index where it could be inserted)-1.
    // parameters:
    //   sortedArray in  array of sorted (ascending) values.
    //   first, last in  lower and upper subscript bounds
    //   key         in  value to search for.
    // returns:
    //   index of key, or -insertion_position -1 if key is not
    //                 in the array. This value can easily be
    //                 transformed into the position to insert it.

    while (first <= last) {
        int mid = (first + last) / 2;  // compute mid point.
        if (key > sortedArray[mid])
            first = mid + 1;  // repeat search in top half.
        else if (key < sortedArray[mid])
            last = mid - 1; // repeat search in bottom half.
        else
            return true;     // found it. return position /////
    }
    return false;    // failed to find key
}

bool Utilities::binarySearch(vector<int>* sortedArray, int first, int last, int key) {
    // function:
    //   Searches sortedArray[first]..sortedArray[last] for key.
    // returns: index of the matching element if it finds key,
    //         otherwise  -(index where it could be inserted)-1.
    // parameters:
    //   sortedArray in  array of sorted (ascending) values.
    //   first, last in  lower and upper subscript bounds
    //   key         in  value to search for.
    // returns:
    //   index of key, or -insertion_position -1 if key is not
    //                 in the array. This value can easily be
    //                 transformed into the position to insert it.

    while (first <= last) {
        int mid = (first + last) / 2;  // compute mid point.
        if (key > (*sortedArray)[mid])
            first = mid + 1;  // repeat search in top half.
        else if (key < (*sortedArray)[mid])
            last = mid - 1; // repeat search in bottom half.
        else
            return true;     // found it. return position /////
    }
    return false;    // failed to find key
}


res_point* Utilities::binarySearch_res_point(vector<res_point*>* sortedArray, int first, int last, int key) {
    // function:
    //   Searches sortedArray[first]..sortedArray[last] for key.
    // returns: index of the matching element if it finds key,
    //         otherwise  -(index where it could be inserted)-1.
    // parameters:
    //   sortedArray in  array of sorted (ascending) values.
    //   first, last in  lower and upper subscript bounds
    //   key         in  value to search for.
    // returns:
    //   index of key, or -insertion_position -1 if key is not
    //                 in the array. This value can easily be
    //                 transformed into the position to insert it.
    while (first <= last) {
        int mid = (first + last) / 2;  // compute mid point.
        if (key > (*sortedArray)[mid]->id)
            first = mid + 1;  // repeat search in top half.
        else if (key < (*sortedArray)[mid]->id)
            last = mid - 1; // repeat search in bottom half.
        else{
            return (*sortedArray)[mid];     // found it. return position /////
        }
    }

    return NULL;    // failed to find key
}

double Utilities::computeMinimumDistance(double lon1, double lat1, double lon2, double lat2){
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = DEG_TO_RAD * lat1;
	lon1r = DEG_TO_RAD * lon1;
	lat2r = DEG_TO_RAD * lat2;
	lon2r = DEG_TO_RAD * lon2;
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return (2.0 * EARTH_RADIUS_IN_KILOMETERS * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)));
}

res_point* Utilities::copy(res_point* toBeCopied){

    res_point* rp = new res_point();
    rp->id = toBeCopied->id;
    rp->x = toBeCopied->x;
    rp->y = toBeCopied->y;
    rp->dist = toBeCopied->dist;

    return rp;
}

res_point* Utilities::createResultPoint(int id, double x, double y, double distance){

    res_point* rp = new res_point();
    rp->id = id;
    rp->x = x;
    rp->y = y;
    rp->dist = distance;

    return rp;
}

// Compute the intersection of two sets. 
// DO NOT CHANGE THIS FUNCTION
size_t Utilities::computeSetIntersection(std::unordered_set<size_t>& _f1, std::unordered_set<size_t>& _f2) {
	size_t intersections = 0;

	if (_f1.size() == 0 || _f2.size() == 0)
		return 0;
	if (_f1.size() > _f2.size()) {
		for (auto it = _f2.begin(); it != _f2.end(); it++) {
			size_t id = *it;
			if (_f1.find(id) != _f1.end()) {
				intersections++;
			}
		}
	}
	else {
		for (auto it = _f1.begin(); it != _f1.end(); it++) {
			size_t id = *it;
			if (_f2.find(id) != _f2.end()) {
				intersections++;
			}
		}
	}
	return intersections;
}

#include "../headers.h"


Group::Group(){
    friends = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();
    longest_dist_i = 0;
    finished_flag = false;
    m = 0;
    max_dist = 0;
    f = (char*) malloc(sizeof(char)*3);
	f = strcpy(f, (char*)"sum");
}


Group::Group(res_point* user, int cardinality, char* function){
    m = cardinality;
    id = user->id;
    adist = user->dist;
    user_dist = user->dist;
    max_dist = user->dist;
    f = (char*) malloc(sizeof(char)*3);
    f = strcpy(f, function);
    friends = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();
    
    longest_dist = user->dist;
    longest_dist_i = 0;
    finished_flag = false;
}


Group::Group(res_point* user){
    m = MAXSC;
    id = user->id;
    adist = user->dist;
    user_dist = user->dist;
    max_dist = user->dist;
    friends = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();
    
    longest_dist = user->dist;
    f = (char*) malloc(sizeof(char)*3);
    f = strcpy(f, (char *)"sum");
    longest_dist_i = 0;
    finished_flag = false;
	
}


Group::~Group(){

    if(friends==NULL) return;
    while(!friends->empty()) {
        delete friends->top();
        friends->pop();
    }
    delete friends;
}	


Group::Group(Group* g){
    m = g->m;
    id = g->id;
    adist = g->adist;
    user_dist = g->user_dist;
    longest_dist = g->longest_dist;
    max_dist = g->max_dist;
    finished_flag = g->finished_flag;
    f = (char*) malloc(sizeof(char)*3);
    f = strcpy(f, g->f);
    friends = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();
    
    priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>* temporary = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();

    // cout << "---------------------------------------------- 1" <<endl;

    while(!g->friends->empty()) {
        res_point* c = g->friends->top();
        friends->push(util.copy(c));
        temporary->push(c);
        g->friends->pop();
    }

    while(!temporary->empty()) {
        res_point* c = temporary->top();
        g->friends->push(c);
        temporary->pop();
    }
    //cout << "---------------------------------------------- 2" <<endl;
    //delete tmp;
}


double Group::getBestDist(){
    if(strcmp(f, "sum"))
        return adist;
    else
        return max_dist;

}

double Group::getMaxDist(){
        return max_dist;

}


double Group::getAdist(){
    return adist;
}       


priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>* Group::getFriends(){
    return friends;
}


void Group::addFriend(res_point* _friend){
    friends->push(util.copy(_friend));
	
    if(friends->size() < m){
        adist += _friend->dist;
        if(_friend->dist > max_dist)
            max_dist = _friend->dist;
    }
}   

bool Group::finished(){
    return finished_flag;
}


void Group::updateLongestDist(double distance){

    if(distance < 0){
        longest_dist_i = 1;
        longest_dist = friends->top()->dist;
    }
    else{
        if(longest_dist_i != (int)friends->size()){
            vector<res_point*>* tmp = new vector<res_point*>();
            while(!friends->empty() && friends->top()->dist < distance){
                tmp->push_back(friends->top());
                friends->pop();
                longest_dist_i++;
            }

            longest_dist = friends->top()->dist;

            for(int i = 0; i < (int)tmp->size(); i++){
                friends->push((*tmp)[i]);
            }
        }
        else
            finished_flag = true;
    }
}


double Group::getLongestDistance(){
    return longest_dist;
} 


int Group::size(){
    return friends->size()+1;
} 


void Group::print(){
    cout <<"--------------------------------------" << endl;
    cout << "User ID = " << id << " distance = " << user_dist <<" km"<<endl;
	cout<<"Friends Size = "<<friends->size()<<endl;
    cout << "Friends = {";
    priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>* tmp = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();

    while(!friends->empty()) {
        res_point* c = friends->top();
        tmp->push(c);
        friends->pop();
    }

    while(!tmp->empty()) {
        res_point* c = tmp->top();
        friends->push(c);
        cout << "(" << c->id << ", " << c->dist <<" km"<< "), ";
        tmp->pop();
    }
	if(friends->empty())
		cout << "}" << endl;
	else
		cout << "\b\b}" << endl;
    cout << "adist = " << adist <<" km"<<endl;
    cout << "max_dist = " << max_dist <<" km"<<endl;
    cout <<"--------------------------------------" << endl;
	delete tmp;
}        

void Group::print_result(std::ofstream& fout) {
	if (friends->empty()) {
		fout << "Empty Output\n";
		return;
	}

	priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>* tmp = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();

	while (!friends->empty()) {
		res_point* c = friends->top();
		tmp->push(c);
		friends->pop();
	}

	while (!tmp->empty()) {
		res_point* c = tmp->top();
		friends->push(c);
		fout << c->id << " ";
		tmp->pop();
	}
	fout << std::endl;
	delete tmp;
}
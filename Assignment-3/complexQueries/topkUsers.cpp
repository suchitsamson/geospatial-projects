#include "../headers.h"
#include <assert.h>

topkUsers::topkUsers(IGPOs *spatialIndex, ISPOs *socialGraph, SimpleQueries *simpleQueries){
	spos = socialGraph;
	gpos = spatialIndex;
	sq = simpleQueries;
}

topkUsers::~topkUsers(){}

bool res_point_ascending_dist_cmp(res_point* a, res_point* b) {
	if (a->dist > b->dist) return true;
	if (b->dist > a->dist) return false;
	return (a->id > b->id);
}

// NSG of size m by its adist to (x, y)
// ATTENTION: You only need to implement either one of NSG_lazy or NSG_eagerstar.
//  NSG_eagerstar is the better option.
Group* topkUsers::NSG(double x, double y, int m) {
	/* ------------------ Your code starts here ------------------ */
	// You should "return result;" in this part. 

	m=m-1;
	gpos->clearNextNN();

	double b_s=INT_MAX;
	double b_un=0;
	Group* R=new Group();
	Group* F_seen=new Group();
	map<int, Group*> F_Map;
	res_point* last;
	int ctr=0;

	while(b_un<b_s){
		res_point* ui = gpos->getNextNN(x,y);
		Group* F = new Group(sq->getMyFriendsInRange(x,y,b_s,ui));
		priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>* tmp = new priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>();
		while(!F->friends->empty()){
			res_point* u = F->friends->top();
			F->friends->pop();
			tmp->push(u);
		}
		Group* NSGui = new Group(ui);
		ctr=1;
		while(!tmp->empty()){
			res_point* u = tmp->top();
			tmp->pop();
			F->addFriend(u);
			if(ctr<m){
				NSGui->addFriend(u);
				ctr++;
			}
		}

		if(NSGui->friends->size()==m && NSGui->adist<b_s){
			R=new Group(NSGui);
			b_s=NSGui->adist;
		}

		while(!F->friends->empty()) {
			res_point* u = F->friends->top();
			F->friends->pop();
			auto iter=F_Map.find(u->id);
			if(iter==F_Map.end()){
				F_seen->addFriend(u);
				Group* F_seen_1=new Group(u);
				F_seen_1->addFriend(ui);
				F_Map.insert({u->id, F_seen_1});
			}
			else{
				if(iter->second->friends->size()<m){
					iter->second->addFriend(ui);
				}
				if(iter->second->friends->size()==m && iter->second->adist<b_s){
					R=new Group(iter->second);
					b_s=iter->second->adist;
				}
			}
		}
		b_un=m*ui->dist;
		last=ui;
	}

	while(!F_seen->friends->empty()){
		res_point* u = F_seen->friends->top();
		F_seen->friends->pop();
		auto iter = F_Map.find(u->id);
		Group* NSGu =iter->second;

		if(NSGu->friends->size()<m && NSGu->adist+(m-NSGu->friends->size())*last->dist<b_s){
			NSGu = sq->getClosestFriends(x,y,u,m+1);
			if(NSGu->friends->size()==m && NSGu->adist<b_s){
				R=new Group(NSGu);
				b_s=NSGu->adist;
			}
		}
	}
	
	return R;
	
	/* ------------------ Your code ends here ------------------ */
	
}
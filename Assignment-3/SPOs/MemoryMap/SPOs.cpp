#include "../../headersMemory.h"

SPOs::SPOs() { 
    areFriendsExecutions = getFriendsExecutions = 0;
}

int SPOs::getAreFriendsExecutions(){
    return areFriendsExecutions;
}

int SPOs::getGetFriendsExecutions(){
    return getFriendsExecutions;
}

/*
loads the social graph into a map/hashtable containing
(id, value) pair. The "value" data structure stores the
ids of all friends of a given user.
*/
int SPOs::load(const char* file){

    ifstream fin(file);
    if (!fin){
        cout << "Cannot open Social graph file " << file << endl;
        return -1;
    }

    int id, size;
    unsigned int times = 0;
    int totalFriends = 0;
    cout << "Loading the Social Graph from " << file << endl;
    Value* entry;
    while(fin){ //NUMOFUSERS

        fin >> id >> size;
        if (! fin.good()){
            // cout << "fin is not good: id = " << id << endl;
            continue;
        }

        entry = new Value(size, id);

        int* list = (int*) malloc(sizeof(int)*size);
        totalFriends+=sizeof(int)*size;
        for(int i = 0; i<size; i++){
            fin >> list[i];
        }
        entry->setList(list, size);

        //ids.push_back(id);

        hashTable.insert(pair<int, Value*>(id, entry));

        times++;
        if(times%1000000 == 0)
            cout << times << endl;
    }
    fin.clear();
    fin.close();
    cout << times << endl;
    cout << "Done!" << endl;
    cout << "totalFriends = " << totalFriends/sizeof(int) << endl;
    return 0;
}

/*
returns the size of the list of friends of a given user (id)
as the integer "numOfFriends" along with the list in integer
array "friends"
*/
void SPOs::getFriends(int id, int*& friends, unsigned int &numOfFriends){
    getFriendsExecutions++;

    Value* v = NULL;
    map<int, Value*>::iterator it = hashTable.find(id);
    if(it != hashTable.end()){
        //element found;
        v = it->second;
    }
    else {
        numOfFriends = 0;
        friends = (int*)malloc(sizeof(int)*numOfFriends);
    }

    if(v!=NULL){
        numOfFriends = v->getListSize();
        int* tmp = v->getList();
        friends = (int*)malloc(sizeof(int)*numOfFriends);

        for(unsigned int i=0; i< numOfFriends; i++){
            friends[i] = tmp[i];
        }
        free(tmp);
    }

}

/*
iterates through the list of friends of user1 to find
user2. Returns boolean variable denoting the same.
*/
bool SPOs::areFriends(int user1, int user2){
    areFriendsExecutions++;

    Value* v = NULL;
    map<int, Value*>::iterator it = hashTable.find(user1);
    if(it != hashTable.end()){
        //element found;
        v = it->second;
    }

    if(v != NULL){
        int size = v->getListSize();
        int* f = v->getList();

        for(int j = 0; j < size; j++){
            if (f[j] == user2){
                return true;
            }
        }
        free(f);
    }

    return false;
}
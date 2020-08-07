#ifndef SPOS_H
#define SPOS_H


class SPOs : public ISPOs
{
private:
    map<int, Value*> hashTable;
//    Value* hashTable2[DATASET_SIZE];
    int valueCapacity;
    char hashTableFileName[100];
    int areFriendsExecutions, getFriendsExecutions;
    Utilities util;

public:
    SPOs();
    ~SPOs() {}

    vector<int> ids;

    int load(const char* file);

    // to be implemented by ISPOs
    virtual void getFriends(int id, int*& friends,unsigned int& numOfFriends);

    virtual bool areFriends(int user1, int user2);

	
    int getAreFriendsExecutions();
    int getGetFriendsExecutions();

};
#endif // !SPOS_H
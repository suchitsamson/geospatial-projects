class Group {	      

public:
    int id;
    double user_dist;
    double adist;
    double longest_dist;
    int longest_dist_i;
    bool finished_flag;
    Utilities util;
    unsigned int m;
    double max_dist;
    char* f;

    priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>* friends;

public:
    Group();
    Group(Group* g);
    Group(res_point* user, int cardinality, char* function);
    Group(res_point* user);
    ~Group();

    double getBestDist();
	double getMaxDist();
    double getAdist();

    void addFriend(res_point* _friend);

    priority_queue<res_point*, vector<res_point*>, res_point_ascending_dist>* getFriends();
    int size();
    void print();
	void print_result(std::ofstream& fout);


    bool finished();
    void updateLongestDist(double distance);

    double getLongestDistance();


    struct ascending : public std::binary_function<Group*, Group*, bool>
    {
        bool operator()(const Group* __x, const Group* __y) const {
            if(strcmp(__x->f, "max") == 0)
                return __x->max_dist > __y->max_dist;
            else
                return __x->adist > __y->adist;
        }
    };

    bool operator<( const Group* other) const
    {
        return id < other->id;
    }

    struct ascendingLongDist : public std::binary_function<Group*, Group*, bool>
    {
        bool operator()(const Group* __x, const Group* __y) const { return __x->longest_dist > __y->longest_dist; }
    };

    struct descendingLongDist : public std::binary_function<Group*, Group*, bool>
    {
        bool operator()(const Group* __x, const Group* __y) const { return __x->longest_dist < __y->longest_dist; }
    };

};


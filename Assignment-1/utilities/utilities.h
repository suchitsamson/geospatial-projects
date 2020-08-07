// Useful functions. 

namespace utilities {

	double distanceBetween(double lat1, double lon1, double lat2, double lon2);
	size_t computeSetIntersection(std::unordered_set<size_t>& _f1, std::unordered_set<size_t>& _f2);

}//namespace

struct delete_pointer_element
{
    void operator()( Point* element ) const
    {
        delete element;
    }
};

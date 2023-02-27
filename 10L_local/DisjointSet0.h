/* Sets are disjoint if the sets are all pairwise disjoint.                  *
 * For example, the sets {1,2}, {3,6}, {10,41} are  disjoint,                *
 * whereas the sets {3,2}, {2,8} are not, due to the common element 2.       *
 * A disjoint set is a set containing disjoint sets. Another name   		 *
 * for this data structure is the union-find.                                *
 * 
 * This particular implementation uses an uptree that is built with an       *
 * underlying std::map. All elements are int type                            *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



#include <map>
using namespace std;

class DisjointSet{
private:
    std::map<int, int> parents; // access to set representitives
    std::map<int, int> depths; // used for path compression
public:
    DisjointSet(){};
    
    /**
	 * Creates a singleton set from the parameter.
	 */
    void createSet(int);
    
    /**
	 * Finds and returns the representative of the set which contains the
	 * parameter. Implements path compression.
	 */
    int findSet(int p);
    
    /**
	 * Combines the sets which contain the parameters. Return false if two 
     * parameters are already in the same set; otherwise, union the two sets
     * by rank and return true
	 */
    bool unionSets(int p, int q);
    
};

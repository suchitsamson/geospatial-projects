/* ---------------------------------------------------------------------------- */
// Feel free to modify whatever you need for debug purposes.

// NOTICE #1: When doing transformation of data, ALWAYS use constants provided in headers.h. Otherwise, you may suffer from float accuracy issues.
// NOTICE #2: All coordinates are suggested be processed as (LON, LAT) format.
//
// All functions are not always useful. Feel free to ignore some of them. Also you can create your own.
/* ---------------------------------------------------------------------------- */

#include "headers.h"
#include "headersMemory.h"
#include "SPOs/MemoryMap/SPOs.h"

#include <chrono>
#include <assert.h>

#ifndef GLOBALS
#define GLOBALS

//initializing extern variables
double DELTA_LAT = 0;
double DELTA_LON = 0;
double MIN_LAT = 0;
double MAX_LAT = 0;
double MIN_LON = 0;
double MAX_LON = 0;
double DATASET_SIZE = 5868;
int MAXSC = DATASET_SIZE;
double MAXDIST = std::numeric_limits<double>::max();

const char *DATASET_PATH;
const char *checkins_file, *query_file, *query_answer_file, *query_results_file, *grading_file, *social_file;
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
#endif


int main(int argc, char *argv[]){

  checkins_file    = "data/checkins.txt";
  social_file = "data/socialGraph.txt";
  query_file       = "data/queries_example.txt";
  query_results_file = "data/results_example.txt";

  // These files are used for local grading.
  query_answer_file  = "data/answers_example.txt";
  grading_file = "data/grades.txt";

  //Tokyo area, 25x35 km^2. DO NOT CHANGE THEM!
  MIN_LAT = 30.12;
  MAX_LAT = 30.41;
  MIN_LON = -97.90;
  MAX_LON = -97.54;

  DATASET_SIZE = 5868;

  DELTA_LAT = ((MAX_LAT - MIN_LAT)/ (Y_granularity-1));
  DELTA_LON = ((MAX_LON - MIN_LON)/ (X_granularity-1));

  // Building up the Grid
  GPOs* gpos = new GPOs(checkins_file);
  SPOs* spos = new SPOs();
  spos->load(social_file);
  SimpleQueries* s_queries = new SimpleQueries(gpos, spos);
  topkUsers* t_queries = new topkUsers(gpos, spos, s_queries);
  Utilities* util = new Utilities();

  //open query file
  std::ifstream fin_query(query_file);
  if (!fin_query){
      std::cerr << "Cannot open data file " << query_file << "." << std::endl;
      return false;
  }

  // create your result file
  std::ofstream fout_query_results(query_results_file);
  if (!fout_query_results) {
	  std::cerr << "Cannot create result file " << query_results_file << "." << std::endl;
	  return false;
  }

  auto t0 = Time::now();
  int counter  = 0;
  // reading each query
  while(fin_query){
	  // skip blank lines
	  if (!fin_query.good()) {
		  std::string blank;
		  std::getline(fin_query, blank);
		  continue;
	  }
      double lat,lon,var;
	  int id;
	  std::string query_type;

	  
      fin_query >> query_type;
	  
	  // Nearest Friends
      if (!query_type.compare("NF")){
            // std::cout << "Query Nearest Friends" << std::endl;
            
			int k;
			fin_query >> lon >> lat >> id >> k;
			
			
			res_point* user = new res_point();
			user->id = id;
			double location_user[2];
			gpos->getLocation(id, location_user);
			user->x = location_user[0];
			user->y = location_user[1];
			user->dist = util->computeMinimumDistance(lon, lat, user->x, user->y);
			Group* results;
			results = s_queries->getClosestFriends(lon, lat, user, k);
			// assert(results != NULL);
			results->print_result(fout_query_results);
			// delete results;
			delete user;
      }
	  // Range Friends
	  else if (!query_type.compare("RF")){
            // std::cout << "Query Range Friends " << std::endl;
			Group* results;
			fin_query >> lon >> lat >> id >> var;

			res_point* user = new res_point();
			user->id = id;
			double location_user[2];
			gpos->getLocation(id, location_user);
			user->x = location_user[0];
			user->y = location_user[1];
			user->dist = util->computeMinimumDistance(lon, lat, user->x, user->y);
			results = s_queries->getMyFriendsInRange(lon, lat, var, user);
			// assert(results != NULL);
			results->print_result(fout_query_results);
			// delete results;			
			delete user;			
      }
	  // Nearest Star Group
	  else if (!query_type.compare("NSG")){
	  		// std::cout << "NSG " << counter + 1 << std::endl;	  					
			Group* results;
			unsigned int size;
			fin_query >> lon >> lat >> size;
			results = t_queries->NSG(lon, lat, size);
			// assert(results != NULL);
			results->print_result(fout_query_results);
			//delete results;
	  }
	  else
	  {
		  continue;
	  }
      counter++;
  }

  ms d = std::chrono::duration_cast<ms>(Time::now() - t0);
  std::cout<<"Your execution time was "<< d.count() << "ms for "<<counter<<" queries and your grades are NOT located in " <<grading_file<<"\n";
  fin_query.close();
  fout_query_results.close();
  
  

  return 0;
}

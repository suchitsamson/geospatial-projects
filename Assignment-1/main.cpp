/* ---------------------------------------------------------------------------- */
// Feel free to modify whatever you need for debug purposes.

// NOTICE #1: When doing transformation of data, ALWAYS use constants provided in headers.h. Otherwise, you may suffer from float accuracy issues.
// NOTICE #2: All coordinates are suggested be processed as (LON, LAT) format. Even though they are in (LAT, LON) format in input checkin files.
// NOTICE #3: Remember to avoid memory leakage. I generally use no more than 150MB or memory.
//
// All functions are not always useful. Feel free to ignore some of them. Also you can create your own.
/* ---------------------------------------------------------------------------- */

#include "headers.h"
#include <chrono>

#ifndef GLOBALS
#define GLOBALS

//initializing extern variables
double DELTA_LAT = 0;
double DELTA_LON = 0;
double MIN_LAT = 0;
double MAX_LAT = 0;
double MIN_LON = 0;
double MAX_LON = 0;
double DATASET_SIZE = 1000;

const char *DATASET_PATH;
const char *checkins_file, *query_file, *query_answer_file, *query_results_file, *grading_file;
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
#endif

// reading data from result/answer files. 
void readin(std::ifstream* s, std::vector<size_t>& sv, const char flag = ' ') {
	int num = -1;
	while ((*s)>>num){
		sv.push_back(num);
		char c;
		while ((c = s->get()) == ' ' || c == '\r');
		if (c == '\n') break;
		s->unget();
	}
	return;
}

// This is only a local grading function. It should not affect your result output by any means.
// The function compares result from the given correct answer and your result. 1 point each query. DO NOT CHANGE THIS FUNCTION
// returning -1 means that the function skips a blank line (usually at the end of file)
int gradeResults(std::ifstream& fin_result, std::ifstream& fin_answer){
	std::vector<size_t> answers;
	std::vector<size_t> results;
	readin(&fin_result, results);
	readin(&fin_answer, answers);

	if (answers.size() == 0 && results.size() == 0) return -1;

	std::unordered_set<size_t> result_ids(results.begin(), results.end());
	std::unordered_set<size_t> answer_ids(answers.begin(), answers.end());

	if (result_ids.size() != answer_ids.size()) return 0;
	if( utilities::computeSetIntersection(result_ids, answer_ids) == results.size()) return 1;
	
	return 0;
}


int main(int argc, char *argv[]){

  checkins_file    = "data/checkins.txt";
  query_file       = "data/queries.txt";
  query_results_file = "data/results.txt";

  // These files are used for local grading.
  query_answer_file  = "data/queries_answers.txt";
  grading_file = "data/grades.txt";

  //Define spatial extent of Tokyo,
  //about 25x35 km^2.
  MIN_LAT = 35.55;
  MAX_LAT = 35.76;
  MIN_LON = 139.49;
  MAX_LON = 139.91;

  DATASET_SIZE = 1000;

  DELTA_LAT = ((MAX_LAT - MIN_LAT)/ (Y_granularity-1));
  DELTA_LON = ((MAX_LON - MIN_LON)/ (X_granularity-1));

  // Building up the Grid Index from the checkins in the file
  GPOs* gpos = new GPOs(checkins_file);

  //open query file
  std::ifstream fin_query(query_file);
  if (!fin_query){ std::cerr << "Cannot open data file " << query_file << "." << std::endl; return false; }

  //you will execute the queries in the above file
  // and write the result of the execution to the following file
  std::ofstream fout_query_results(query_results_file);
  if (!fout_query_results) { std::cerr << "Cannot create result file " << query_results_file << "." << std::endl; return false; }

  auto t0 = Time::now();	//chrono
  int counter  = 0;
  // reading each query
  while(fin_query){
	  // skip blank lines
	  if (!fin_query.good()) { std::string blank; std::getline(fin_query, blank); continue; }
      double lat,lon,var;
	  std::string query_type;

	  // Input format: latitude longitude (k for NN or radius for RQ) (NN or RQ)
      fin_query >> lat >> lon >> var >> query_type;

      if(lat> MIN_LAT && lat < MAX_LAT && lon > MIN_LON && lon < MAX_LON){
		// Nearest Neighbor Queries
        if (!query_type.compare("NN")){
            // std::cout << "Query k-nearest neighbor" << std::endl;
            int k = (int)var;
			
			std::vector<Point*> results;
			gpos->getkNN(lon, lat, k, results);
			
			for (std::vector<Point*>::iterator it = results.begin(); it != results.end(); it++){
				if ((*it) == NULL) continue;
				fout_query_results << (*it)->getOrderID() << " ";
				delete (*it);
			}
			fout_query_results << std::endl;
        }
		// Range Queries
		else if (!query_type.compare("RQ")){
            // std::cout << "Query check-ins in range " << std::endl;
			std::vector<Point*> results;
			gpos->getRange(lon, lat, var, results);

			for (std::vector<Point*>::iterator it = results.begin(); it != results.end(); it++) {
				if ((*it) == NULL) continue;
				fout_query_results << (*it)->getOrderID() << " ";
				delete (*it);
			}
			fout_query_results << std::endl;
        }
        counter++;
   	  }
  }
  fin_query.close();
  fout_query_results.close();

  ms d = std::chrono::duration_cast<ms>(Time::now() - t0);
  std::cout<<"Your execution time was "<< d.count() << " ms for "<<counter<<" queries and your grades are located in " <<grading_file<<"\n";
  
  
  // A rudimentary grader is provided below.
  // All following codes are used for local grading. 
  // You should REMOVE them before you submit your codes to avoid unexpected crash during assignment grading!
  std::ifstream fin_query_results(query_results_file);
  if (!fin_query_results) { std::cerr << "Cannot open results file " << query_results_file << "." << std::endl; return false; }

  std::ifstream fin_query_answers(query_answer_file);
  if (!fin_query_answers) { std::cerr << "Cannot open data file " << query_answer_file << "." << std::endl; return false; }

  std::ofstream fout_grades(grading_file);
  if (!fout_grades) { std::cerr << "Cannot create grading file " << grading_file << "." << std::endl; return false; }

  int query_counter = 0, correct_answers = 0;
  while (fin_query_results && fin_query_answers) {
	  int result_score = gradeResults(fin_query_results, fin_query_answers);
	  // Skipping blank lines
	  if (result_score < 0) continue;

	  correct_answers += result_score;
	  query_counter++;
	  fout_grades << "You get " << result_score << " point on query No." << query_counter << std::endl;
  }
  fout_grades << "You get " << correct_answers << " points out of " << query_counter << std::endl;


  return 0;
}

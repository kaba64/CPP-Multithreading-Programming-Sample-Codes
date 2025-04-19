#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include <cmath>
#include "printScheduleGroups.h"

int main(int argc,char* argv[]) {
  constexpr int numThread{4}, chunk_sch{22}, N{120};
  /* static  dynamic  guided*/
  const std::string name_sch{"dynamic"};
  
  /* Approximate the guided chunk size for the guided scheme*/
  auto group_size = [&](int remaining) {return std::min(remaining,std::max(chunk_sch,static_cast<int>
				       (std::ceil(remaining/(1.0*numThread)))));};
  
  std::vector<double> data(N);
  std::vector<std::vector<std::pair<int,int>>> subRegions(numThread);
  
#pragma omp parallel num_threads(numThread)
  {
    int thread_id = omp_get_thread_num();
    int local_chunk = name_sch == "guided" ? 0 : (name_sch == "auto" ? std::ceil(N/(1.0*numThread)) : chunk_sch);
    int local_count = 0;

#pragma omp for schedule(dynamic,chunk_sch)
    for (int i = 0; i < N; ++i) {
      data[i] = static_cast<double>(i);
      
      if (name_sch == "guided" && local_chunk == 0) {local_chunk = group_size(N - i);}

      subRegions[thread_id].emplace_back(local_chunk, i);
      ++local_count;
      
      if (local_count == local_chunk){
	local_count = 0;
	if(name_sch == "guided")
	  local_chunk = 0;
      }
    }
  }  
  printSchedule(subRegions, name_sch);
  return 0;
}           

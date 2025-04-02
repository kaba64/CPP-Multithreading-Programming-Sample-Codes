#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <execution>
#include <cstdlib>
#include "common.h"

int main(int argc,char* argv[]){

  constexpr int N{1<<20};
  constexpr double bound_a{4.8}, bound_b{4.81};
  
  std::vector<double> data(N,0.0);
  int index{0};
  auto codition = [&](const auto& value){return (value>bound_a && value<bound_b);};
  
#pragma omp parallel
  {
    Random<double> random(0, 5);
#pragma omp for
    for(auto& x:data){x = random.randomNumber();}
  }
  
  /*The usage of OpenMP for a loop 
    with *break* inside it is not allowed*/
  //#pragma omp parallel for
  for(int i=0;i<static_cast<int>(data.size());++i){
    if(codition(data[i])){
      index=i; break;
    }
  }
  
  /*The usage of the STL algorithm and execution policy*/
  const auto it = std::find_if(std::execution::par,data.begin(), data.end(),codition);
  int index_findif = std::distance(data.begin(),it);
  
  std::cout<<"data["<<index<<"] = "<<data.at(index)<<"\n";
  std::cout<<"data["<<index_findif<<"] = "<<data.at(index_findif)<<"\n";
  
  return EXIT_SUCCESS;
}

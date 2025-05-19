#include "headers.h"

template<typename Iterator, typename T>
void partialSum(Iterator begin, Iterator end, T& parSum) {
    parSum = std::accumulate(begin, end, T{0});
}

int main(int argc,char* argv[]){
  
  int N{1 << 22}, threadNum{2}, mid{N / threadNum};
  std::vector<double> data(N), parSum(threadNum);

  std::fill(data.begin(), data.end(), 1.0);

  auto start = std::chrono::high_resolution_clock::now();
  const std::clock_t c_style_start = std::clock();
  using Iterator = std::vector<double>::iterator; 

  {
    std::jthread t1(partialSum<Iterator, double>,
		    data.begin(), data.begin() + mid, std::ref(parSum[0]));
    std::jthread t2(partialSum<Iterator,double>,
		    data.begin() + mid, data.end(), std::ref(parSum[1]));
  }
  
  [[maybe_unused]] double sum = std::accumulate(parSum.begin(),parSum.end(),0.0);
  
  const std::clock_t c_style_end = std::clock();
  const auto end = std::chrono::high_resolution_clock::now();
  
  std::cout<<std::fixed << std::setprecision(5);
  std::cout<<"\nCPU time : "<<1000.0*(c_style_end-c_style_start)/CLOCKS_PER_SEC <<" ms \n\n"; 
  std::cout << "\nWall clock time: "
	    << std::chrono::duration<double,std::milli>(end - start).count() << " ms\n\n";

  return 0;
}

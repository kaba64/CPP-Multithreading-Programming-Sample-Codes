/*
 * Using C++ multithreading to compute the sum of an array
 Refereces:
 * [1] C++ Programming Language, Fourth Edition
 * [2] C++ Concurrency in Action, Second Edition
 * Programmed by: Kazem Bazesefidpar
 * Email: bazesefidpar64@gmail.com                                                                                                 
 */
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <cmath>
#include <numeric>
#include "threadGuard.h"

/*funcion to run on each thread*/
template<typename Iterator, typename T>
void partialSum(Iterator begin, Iterator end, T& parSum) {
  parSum = static_cast<T>(0);
  std::for_each(begin, end, [&parSum](const auto& i) { parSum += i; });
}

template<typename Iterator, typename T>
void LaunchThreads(Iterator begin, Iterator end, const size_t& N,
		   const size_t& threadNum, std::vector<T>& sumP){
  /*std::vector will invoke the destructor of threadGuard automatically*/
  std::vector<threadGuard> threadGuards;
  size_t step = std::ceil(N / static_cast<double>(threadNum));

  for (size_t i = 0; i < threadNum; ++i) {
    Iterator threadBegin = begin + i * step;
    Iterator threadEnd = (i == threadNum - 1) ? end : (threadBegin + step);
    /*Launch a new thread and move it to the threadGuard object*/
    std::thread t(partialSum<Iterator, T>, threadBegin, threadEnd, std::ref(sumP[i]));
    threadGuards.emplace_back(std::move(t));
  }
}

int main() {
  const size_t N = 5566;
  size_t threadNum = std::thread::hardware_concurrency();
  std::vector<double> data(N), sumP(threadNum);
  double sumAll = 0.0;
  /*Initialize the data*/
  std::generate(data.begin(), data.end(), []() { return 1.0; });
  
  LaunchThreads(data.begin(), data.end(), N, threadNum, sumP);
  /*Summing the partial sums of each thread*/
  sumAll = std::accumulate(sumP.begin(), sumP.end(), 0.0);
  
  std::cout << "Sum of the data = " << sumAll << "\n";
  
  return 0;
}     

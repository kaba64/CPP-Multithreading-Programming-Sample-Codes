#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <barrier>
#include <type_traits>
#include <syncstream>
#include <random>

template<typename T>
class Random{
private:
  T a, b;
  std::mt19937 generator;  /* Mersenne Twister generator */
public:
  Random(const T aIn = 0, const T bIn = 1)
    : a(aIn), b(bIn), generator(std::random_device{}()) {}  /* Use random_device for seeding*/
  T randomNumber() {
    /*https://en.cppreference.com/w/cpp/types/is_floating_point*/
    if constexpr (std::is_floating_point<T>::value) {
      /*https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution*/
      /* Generate a random T in the range [a, b) */
      std::uniform_real_distribution<T> distribution(a, b);
      return distribution(generator);
    } else {
      /* Generate a random int in the range [a, b] */
      std::uniform_int_distribution<T> distribution(a, b);
      return distribution(generator);
    }
  }
};

int main(int argc,char* argv[]) {
  /*Number of data*/
  const int N = 1<<22;
  const int threadNum = std::max(1, std::thread::hardware_concurrency()-1);
  std::vector<double> data(N), normalized(N), sumP(threadNum,0.0);
  std::vector<std::jthread> threads(threadNum);
  /*Initialize the data*/
  Random<double> random;
  std::for_each(data.begin(),data.end(),[&random](auto& i){i = random.randomNumber();});
  /*Divide data equally between the threads*/
  const int step = std::ceil(N / static_cast<double>(threadNum));
  /*Iterators to pass functions*/
  std::vector<double>::iterator beginD, beginN, endD, endN;
  double norm{0};
  /*Construct Barrier with a custom CompletionFunction*/
  std::barrier sync_barrier(threadNum, [&norm, &sumP] {
    std::remove_reference_t<decltype(norm)> res = std::reduce(sumP.begin(), sumP.end());
    norm = (res > decltype(res){0}) ? std::sqrt(res) : decltype(res){0};
  });
  
  for (int i = 0; i < threadNum; ++i) {
    beginD = data.begin() + i * step;
    endD   = (i == threadNum - 1) ? data.end() : (beginD + step);
    beginN = normalized.begin() + i * step;
    endN   = (i == threadNum - 1) ? normalized.end() : (beginN + step);
    /*Launch a new thread*/
    threads[i] = std::jthread([=,&norm,&sync_barrier,&sumP](){
      
      /*Commpute the square of each element and sum them*/
      sumP[i] = std::accumulate(beginD,endD,std::remove_reference_t<decltype(*beginD)>{0},
				[](auto acc, auto val) {return acc + val * val;});
      
      /*Wait for all threads to reach and perform the reduction*/
      sync_barrier.arrive_and_wait();
      
      if(norm>std::remove_reference_t<decltype(*sumP.begin())>{0}){
	/*Compute the normal of the vector on each thread*/
	std::transform(beginD,endD,beginN,[norm](auto i){return i/norm;});
      }else{
	std::osyncstream(std::cout)<<"Division by zero. normalized filled by zero\n";
	std::fill(beginN,endN,std::remove_reference_t<decltype(*beginN)>{0});
      }
    });
  }

  for(auto& t:threads){t.join();}
  
  double sum = std::accumulate(data.begin(), data.end(), 0.0,
			       [](double acc, double val) {
				 return acc + val * val;});
  /* Compute the norm */
  double norm_s = std::sqrt(sum);

  /* Normalize the data*/
  std::vector<double> normalized_s(N);
  std::transform(data.begin(), data.end(), normalized_s.begin(),
		 [norm_s](double val) { return val / norm_s; });
  
  double eps{1e-11};
  for (int i = 0; i < N; ++i) {
    if(std::abs(normalized[i]-normalized_s[i])>eps){
      std::cerr << "\n\nError\n\n";
      return 1;
    }
  }
  std::cout<<"\n\nThe result of parallel and serial excutions were the same.\n\n";
  return 0;
} 

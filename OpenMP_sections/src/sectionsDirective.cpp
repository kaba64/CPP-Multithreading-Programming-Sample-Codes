#include <iostream>
#include <unistd.h>
#include <omp.h>

int main(int argc,char* argv[]) {
  omp_lock_t lock;  omp_init_lock(&lock);
  int a{0};
#pragma omp parallel sections
  {
#pragma omp section
    {
      try {
	omp_set_lock(&lock);
	std::cout << "\nThread " << omp_get_thread_num() << " running section 1\n";
        omp_unset_lock(&lock);
	a = 100;
	throw std::runtime_error("Exception in section 1");
      } catch (const std::exception& e) {
	omp_set_lock(&lock);
	std::cout << "Caught in section 1: " << e.what() << "\n";
        omp_unset_lock(&lock);
      }
    }
#pragma omp section
    {
      sleep(1);
      omp_set_lock(&lock);
      std::cout << "\nThread " << omp_get_thread_num() << " running section 2\n";
      omp_unset_lock(&lock);
      ++a;
    }
  }  
  std::cout << "\nIn the main thread : a = "<<a<<"\n\n";
  omp_destroy_lock(&lock);
  return 0;
}                   

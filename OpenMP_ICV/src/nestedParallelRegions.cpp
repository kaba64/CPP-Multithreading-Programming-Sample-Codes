#include <iostream>
#include <cstdlib>
#include <omp.h>

int main(int argc,char* argv[]) {
  /*Enable nested parallelism*/
  omp_set_nested(1);
  
  /*Set maximum active parallel levels to two*/
  omp_set_max_active_levels(2);
  
  omp_lock_t lock;
  omp_init_lock(&lock);
  
#pragma omp parallel num_threads(2)
  {
    int level1 = omp_get_level();
    int thread1 = omp_get_thread_num();
    omp_set_lock(&lock);
    std::cout<<"Level "<<level1<<" - Thread "<<thread1<<"\n";
    omp_unset_lock(&lock);
     
    /*Nested parallel region*/
#pragma omp parallel num_threads(2)
    {
      int level2 = omp_get_level();
      int thread2 = omp_get_thread_num();
      omp_set_lock(&lock);
      std::cout<<"\tLevel "<<level2<<" - Thread "<<thread2<<" (Parent Thread "<<thread1<<")\n";
      omp_unset_lock(&lock);
      
      /*Attempt for deeper nesting*/
#pragma omp parallel num_threads(2)
      {
	int level3 = omp_get_level();
	int thread3 = omp_get_thread_num();
	omp_set_lock(&lock);
	std::cout<<"\tLevel "<<level3<<" - Thread "<<thread3<<" (Parent Thread "<<thread2<<")\n";
	omp_unset_lock(&lock);
      }
    }
  }
  return EXIT_SUCCESS;
}  

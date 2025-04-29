#include <iostream>
#include <omp.h>

int main (int argc, char *argv[]){

#pragma omp parallel num_threads(5)
  {
    int id_task_pro = omp_get_thread_num();
#pragma omp task
    {
#pragma omp critical
      std::cout<<"Thread ID : "<<omp_get_thread_num()<<
	" executing task created by Thread ID : "<<id_task_pro<<"\n";
    }
  }
  //////////////////////////////////////////////////////////////////
  std::cout<<"\nUsing single directive\n\n";
#pragma omp parallel num_threads(5)
#pragma omp single nowait
  {
    int id_task_pro = omp_get_thread_num();
    for(int i = 0;i<10;++i){
#pragma omp task
      {
#pragma omp critical
	std::cout<<"Thread ID : "<<omp_get_thread_num()<<
	  " executing task created by Thread ID : "<<id_task_pro<<"\n";
      }
    }
#pragma omp taskwait
#pragma omp critical
    std::cout<<"End of parent thread ID : "<<omp_get_thread_num()<<"\n";
  }
  
  return 0;
}               

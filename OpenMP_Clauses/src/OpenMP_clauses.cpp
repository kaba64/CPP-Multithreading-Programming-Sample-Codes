#include <iostream>
#include <omp.h>

int x_TP;
#pragma omp threadprivate(x_TP)

void O_variables(const int*const x_TP, const int*const x){
  std::cout << "ID = " << omp_get_thread_num() << "\t with address &x = "
	    << x<<"\t with value x = "<<*x<< "\n";
  std::cout << "ID = " << omp_get_thread_num() << "\t with address &x_TP = "
	    << x_TP<<"\t with value x_TP = "<<*x_TP<< "\n\n";
}

int main(int argc,char* argv[]){

  int x{100};
  x_TP = 1;
  
  omp_lock_t lock;
  omp_init_lock(&lock);

  std::cout<<"\n---------- In main thread -------------\n\n";
  O_variables(&x_TP,&x);
  
  std::cout<<"\n--------- Start first parallel region ---------\n\n";
  /*x is a private variable in this region*/
#pragma omp parallel copyin(x_TP) firstprivate(x) num_threads(2)
  {
    omp_set_lock(&lock);
    O_variables(&x_TP,&x);
    omp_unset_lock(&lock);
  }
  x_TP = -1;
  
  std::cout<<"\n--------- Start second parallel region ---------\n\n";
  /*x is reference to the variable defined in the main function*/
#pragma omp parallel num_threads(2)
  {
    omp_set_lock(&lock);
    O_variables(&x_TP,&x);
    omp_unset_lock(&lock);
  }
  return 0;
}     

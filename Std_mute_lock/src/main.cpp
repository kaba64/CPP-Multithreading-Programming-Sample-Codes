#include <iostream>
#include <mutex>
#include <cstdlib>

int main(int argc,char* argv[]){

  std::mutex m1, m2;
  
  std::lock_guard<std::mutex> lg(m1);
  std::cout<<"The size of std::lock_guard object : "<<sizeof(lg)<<"\n";
  std::cout<<"The alignment of std::lock_guard object : "<<alignof(lg)<<"\n\n";
  
  std::unique_lock<std::mutex> ul(m2);
  std::cout<<"The size of std::unique_lock object : "<<sizeof(ul)<<"\n";
  std::cout<<"The alignment of std::unique_lock object : "<<alignof(ul)<<"\n";
  
  return EXIT_SUCCESS;
}
 

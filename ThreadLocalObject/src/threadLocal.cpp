#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>

std::mutex mutexio;

thread_local int a;

void g(){
  std::unique_lock lk{mutexio};
  std::cout<<"Thread ID : "<<std::this_thread::get_id()<<
    "\t&a = "<<&a<<"\n\n";
}

void threadLocalObject(){
  a = 10;
  g();
}

int main(int argc,char* argv[]){
  {
    std::unique_lock lk{mutexio};
    std::cout<<"Main thread ID : "<<std::this_thread::get_id()<<
      "\t&a = "<<&a<<"\n\n";
  }
  
  std::jthread t1(threadLocalObject);
  std::jthread t2(threadLocalObject);
  
  return EXIT_SUCCESS;
}

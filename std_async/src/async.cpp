#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <syncstream>

auto printTask = [](const std::string& name){
  std::osyncstream(std::cout)<<"\nHi from task using "<<name<<
    " policy on a thread with ID : "<<std::this_thread::get_id()<<"\n\n";};

int main(int argc,char* argv[]) {

  std::cout<<"\nThe main thread ID : "<<std::this_thread::get_id()<<"\n\n";

  /*The task runs on a different thread than the main thread*/
  auto t1 = std::async(std::launch::async,printTask,"async");

  /*The task runs on the main thread*/
  auto t2 = std::async(std::launch::deferred,printTask,"deferred");

  /*The task can run on a differnt thread or the main thread*/
  auto t3 = std::async(printTask,"default");
  
  t1.wait(); t2.wait(); t3.wait();
  
  return 0;
}                       

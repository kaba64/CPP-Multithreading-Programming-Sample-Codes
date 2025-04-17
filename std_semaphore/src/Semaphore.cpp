#include <iostream>
#include <thread>
#include <mutex>
#include <mutex>

std::mutex mio;

void read_t(std::binary_semaphore& s){
  s.acquire();
  mio.lock();
  std::cout<<"ID : "<<std::this_thread::get_id()<<" acquired the semaphore\n\n";
  mio.unlock();
  s.release();
}

void write_t(std::binary_semaphore& s){
  
  mio.lock();
  std::cout<<"ID : "<<std::this_thread::get_id()<<" released the semaphore\n\n";
  mio.unlock();
  s.release();
}

int main(int argc,char* argv[]){

  std::binary_semaphore b_s_1{1};
  
  mio.lock();
  b_s_1.acquire();
  std::cout<<"\nID : "<<std::this_thread::get_id()<<" acquired the semaphore\n\n";
  mio.unlock();

  std::thread t1(read_t,std::ref(b_s_1)), t2(write_t,std::ref(b_s_1)); 
  t1.join(); t2.join();
  return 0;
}

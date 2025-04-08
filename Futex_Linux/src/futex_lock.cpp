#include <iostream>
#include <thread> 
#include <atomic>
#include <cstdlib>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <cerrno>

int sum = 1000;

/*The lock and unlock mechanism are adapted from
 https://manpages.ubuntu.com/manpages/bionic/man2/futex.2.html*/
class Futexlock{
private:                       // 0 : lock is free
  std::atomic<int> futex_addr; // 1 : look is not free
public:
  Futexlock(){futex_addr.store(0,std::memory_order_seq_cst);}
  
  void lock(){
    /*Try to acquire the lock in the user sapce*/
    while(true){
      int expected{0};
      /*Try acquiring the lock in user space at first attempt*/
      if(futex_addr.compare_exchange_strong(expected,1))
	break;
      
      /*Block the thread since lock is not available*/
      int wait = syscall(SYS_futex,reinterpret_cast<int*>(&futex_addr),
      			 FUTEX_WAIT,1,nullptr,nullptr,0);
      
      if(wait==-1 && errno != EAGAIN){
      	std::cerr<<"Error_FUTEX_WAIT\n";exit(EXIT_FAILURE);}
    }
  }
  
  void unlock(){
    int expected{1};
    if(futex_addr.compare_exchange_strong(expected,0)){
      /*Wake up a thread*/
      int wake = syscall(SYS_futex,reinterpret_cast<int*>(&futex_addr),
			 FUTEX_WAKE,0,nullptr,nullptr,0);

      if(wake==-1){std::cerr<<"Error_FUTEX_WAKE\n";exit(EXIT_FAILURE);}
    }
  }
};

void sum_together(Futexlock& lk,int amount){
  lk.lock();
  sum+=amount;
  lk.unlock();
}

int main(int argc,char* argv[]){

  Futexlock fulk;

  int t1_amount{1000}, t2_amount{2000};

  std::thread t1(sum_together,std::ref(fulk),t1_amount);
  std::thread t2(sum_together,std::ref(fulk),t2_amount);

  t1.join(); t2.join();

  std::cout<<"sum = "<<sum<<"\n";

  return EXIT_SUCCESS;
}

#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

template<typename T>
class Monitor_list{
private:
  std::list<T> data;
  std::mutex m;
  std::condition_variable cv;
public:
  
  void m_push_back(const T& val){
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    
    std::scoped_lock lk(m);
    std::cout<<"\n A thread locked mutex using std::scoped_lock in m_push_back\n\n";
    data.push_back(val);
    std::cout<<"\n A thread is going to be notified from m_push_back\n\n";
    cv.notify_one();
  }
  
  T m_pop_front(){
    std::unique_lock<std::mutex> lk(m);
    std::cout<<"\n A thread locked mutex using std::unique_lock in m_pop_front\n\n";
    cv.wait(lk, [&]{ return !data.empty(); });
    std::cout<<"\n A thread has been unblocked in m_pop_front\n\n";
    T val = data.front();
    data.pop_front();
    return val;
  }
};

void producer(Monitor_list<int>& ml) {
  ml.m_push_back(1);
}

void consumer(Monitor_list<int>& ml) {
  int val = ml.m_pop_front();
}

int main(int argc,char* argv[]){

  Monitor_list<int> ml;
  
  std::thread t1(producer, std::ref(ml));
  std::thread t2(consumer, std::ref(ml));
  
  t1.join(); t2.join();
  
  return 0;
}

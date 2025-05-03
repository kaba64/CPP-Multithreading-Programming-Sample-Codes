#include <iostream>
#include <future>
#include <thread>
#include <mutex>

std::mutex m;
#include "class_X.h"

void setX(std::promise<X>& p) {
    X x('P'); x.set(10);
    {
      std::scoped_lock lk(m); std::cout << "\nBefore set_value in setX \n";
    }
    try {
      p.set_value(std::move(x));                /*Put the result into promise*/
    }catch (...) {
      p.set_exception(std::current_exception());
    }
    {
      std::scoped_lock lk(m); std::cout << "\nAfter set_value in setX \n";
    }
}

int main(int argc,char* argv[]) {
  std::promise<X> promise;
  std::future<X> future = promise.get_future(); /*Get the future corresponding to the promise*/
  std::jthread t(setX, std::ref(promise)); /*launch a thread including a promise to return the result*/
  
  {
    std::scoped_lock lk(m); std::cout << "Before std::future::get()\n";
  }
  try{
    X x = future.get(); /* Wait and get the result through the promise*/
    {
      std::scoped_lock lk(m); std::cout << "\nGot X with value: "<<x.get()<< "\n";
    }
  }catch(const std::future_error& e){
    std::scoped_lock lk(m); std::cerr<<"\n Error : "<<e.what()<<"\n";
  }catch(...){
    std::scoped_lock lk(m); std::cerr<<"\n Error \n";
  }
  
  return 0;
}                       

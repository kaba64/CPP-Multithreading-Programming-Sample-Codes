#include <iostream>
#include <thread>
#include <string>
#include <syncstream>
#include <chrono>

void write_sync_out(const std::string& message){
  std::thread::id id = std::this_thread::get_id();
  
  std::osyncstream sync_out(std::cout);
  sync_out<<message;
  sync_out<<id<<"\n\n";

  /*Sleep for 250 milliseconds before allowing destruction*/
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  /*The characters are flushed when sync_out is destroyed*/
}

int main(int argc,char* argv[]){
  
  const std::string message{"Hi from the thread with ID : "};

  /*Write from main thread to the std::cout*/
  write_sync_out(message);

  /*Launch two threads to write std::cout*/
  std::jthread t1(write_sync_out,std::ref(message));
  std::jthread t2(write_sync_out,std::ref(message));
  
  return 0;
}                 

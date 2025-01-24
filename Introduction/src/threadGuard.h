/*threadGuard.h*/
/*Adapted from : C++ Concurrency in Action, Second Edition*/
class threadGuard{
private:
  std::thread t;
public:
  explicit threadGuard(std::thread tIn) : t(std::move(tIn)){
    if (!t.joinable()){throw std::logic_error("Not joinable thread!");}}
  
  void join(){if (t.joinable()) {t.join();}}
  void detach(){if (t.joinable()) {t.detach();}}
  
  ~threadGuard() {if (t.joinable()) {t.join();}}
  threadGuard(const threadGuard&) = delete;
  threadGuard& operator=(const threadGuard&) = delete;
  threadGuard(threadGuard&&) = default;
  threadGuard& operator=(threadGuard&&) = default;
};

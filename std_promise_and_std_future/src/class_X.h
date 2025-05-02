class X {
private:
    char p; int x;
public:
  X()noexcept{std::scoped_lock lk(m); std::cout << "\nX() \n";}
  X(const char pIn)noexcept : p(pIn), x(0){
    std::scoped_lock lk(m); std::cout << "\nX(const char pIn) for " << p << "\n";
  }
  void set(const int xIn) noexcept { x = xIn; }
  int get() const noexcept { return x; }
  ~X() {std::scoped_lock lk(m); std::cout << "\n~X() for " << p << "\n\n";}
  /* Move constructor and assignment*/
  X(X&& other)noexcept{
    std::scoped_lock lk(m); std::cout << "\nX(X&&) \n";
    p=other.p; other.p = '\0';
    x = other.x; other.x=0;
  }
  X& operator=(X&& other)noexcept{
    std::scoped_lock lk(m); std::cout << "\n=X(X&&) \n";
    p=other.p; other.p = '\0';
    x = other.x; other.x=0;
    return *this;
  }
  /*Deleting move constructor and assignment generates compilation error*/
  //X(X&&) = delete; X& operator=(X&&) = delete; 
  /*Copy constructor and assignment*/
  X(const X& other)noexcept{
    std::scoped_lock lk(m); std::cout << "\nX(const X&) \n";
    p=other.p; x = other.x;
  }
  X& operator=(const X& other) noexcept{
    std::scoped_lock lk(m); std::cout << "=\nX(const X&) \n";
    p=other.p; x = other.x;
    return *this;
  }
};    

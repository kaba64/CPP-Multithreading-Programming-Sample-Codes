#include <type_traits>
#include <random>

template<typename T>
class Random{
private:
    T a, b;
    std::mt19937 generator;  // Mersenne Twister generator                                                                           
public:
  Random(const T aIn = 0, const T bIn = 1)
    : a(aIn), b(bIn), generator(std::random_device{}()) {}  // Use random_device for seeding                                         
  T randomNumber() {
    /*https://en.cppreference.com/w/cpp/types/is_floating_point*/
    if constexpr (std::is_floating_point<T>::value) {
      /*https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution*/
      /* Generate a random T in the range [a, b) */
      std::uniform_real_distribution<T> distribution(a, b);
      return distribution(generator);
    } else {
      /* Generate a random int in the range [a, b] */
      std::uniform_int_distribution<T> distribution(a, b);
      return distribution(generator);
    }
  }
};

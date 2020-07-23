#include <thread>
#include <iostream>

class Wrapper {
  public:
      void member1() {
          std::cout << "i am member1" << std::endl;
      }
      void member2(const char *arg1, unsigned arg2) {
          std::cout << "i am member2 and my first arg is (" << arg1 << ") and second arg is (" << arg2 << ")" << std::endl;
      }
      std::thread member1Thread() {
          return std::thread(&Wrapper::member1, this);
      }
      std::thread member2Thread(const char *arg1, unsigned arg2) {
          return std::thread(&Wrapper::member2, this, arg1, arg2);
      }
};

int main() {
  Wrapper *w = new Wrapper();
  std::thread tw1 = w->member1Thread();
  tw1.join();
  w->member2Thread("hello", 100).detach();

    return 0;
 }
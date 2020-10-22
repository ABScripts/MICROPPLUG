#include <iostream>
#include <thread>
#include <chrono>

class A {
public:
  A(int a = 0)
    : m_A(a)
  {

  }

  int ADummy() const {

    for (int i = 0; i < 10; ++i)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Dummy A = " << i << " "<< std::this_thread::get_id() << std::endl;
      }

    return 10;
  }

  int m_A;
};

void dummy() {
  for (int i = 0; i < 10; ++i)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "dummy i = " << i << " "<< std::this_thread::get_id() << std::endl;
    }
}

int dummier(int a, int b) {
  std::cout << "dummier START " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  std::cout << "a + b = " << a + b << " " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(4000));
  std::cout << "dummier END " << std::this_thread::get_id() << std::endl;
  return a + b;
}

void pow(int &a) {
  a *= a;
  std::cout << "pow START " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  std::cout << "a^2= " << a << " " << std::this_thread::get_id() << std::endl;
}

int main()
{
  const A a;
  int result = 0;

  unsigned maxThreads = std::thread::hardware_concurrency();

  std::cout << "Max Threads: " << maxThreads << std::endl;

  //int a = 10, b = 15, c = 4;

  //  std::thread t(dummy);
  //  std::thread t2([&](){ c = dummier(a, b); });
  //  std::thread t3(pow, std::ref(c));
  std::thread t4([&]() { result = a.ADummy(); });

  for (int i = 0; i < 10; ++i)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << "main i = " << i << " " << std::this_thread::get_id()  << std::endl;
    }

  //  t2.join();
  //  t3.join();
  //  t.join();
  t4.join();

  //std::cout << "C = " << c << std::endl;
  std::cout << "Result = " << result << std::endl;
}

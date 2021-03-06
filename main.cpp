#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;
std::recursive_mutex recMutex1;

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
//  std::lock_guard<std::mutex> guard(mutex1);
  std::unique_lock<std::mutex> guard(mutex1, std::defer_lock);
  guard.lock();
  for (int i = 0; i < 10; ++i)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "dummy i = " << i << " "<< std::this_thread::get_id() << std::endl;
    }
  guard.unlock();
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

void showRectangle(char sym, int size) {
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  mutex1.lock();
  for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
          std::cout << sym;
        }
      std::cout << std::endl;
    }

  std::cout << std::endl;
  mutex1.unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void recI(int i) {
  recMutex1.lock();
  if (i < 0) {
      recMutex1.unlock();
      std::cout << std::endl;
      return;
    }
  std::cout << i << " ";
  recI(i-1);
  recMutex1.unlock();
}

void print1() {
  mutex1.lock();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  mutex2.lock();
  for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 10; ++j) {
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
          std::cout << "*";
        }
      std::cout << std::endl;
    }

  std::cout << std::endl;

  mutex1.unlock();
  mutex2.unlock();
}

void print2() {
  mutex2.lock();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  mutex1.lock();

  for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 10; ++j) {
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
          std::cout << "#";
        }
      std::cout << std::endl;
    }

  std::cout << std::endl;

  mutex1.unlock();
  mutex2.unlock();
}

int a = 0;

void minus() {
  for (int i = 0; i < 10000; ++i)
    a += 1;
}

void plus() {
  for (int i = 0; i < 10000; ++i)
    a += 1;
}

int main()
{
  auto start = std::chrono::steady_clock::now();
std::thread t3(minus), t4(plus);


  t3.join();
  t4.join();

  std::cout << a << std::endl;

  //  std::thread t1(showRectangle ,'#', 5);

  //  std::thread t2(showRectangle ,'*', 5);

  //  t1.join();
  //  t2.join();

  auto end = std::chrono::steady_clock::now();

  std::cout << "Time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ml" << std::endl;

  //  const A a;
  //  int result = 0;

  //  unsigned maxThreads = std::thread::hardware_concurrency();

  //  std::cout << "Max Threads: " << maxThreads << std::endl;

  //  //int a = 10, b = 15, c = 4;

  //  //  std::thread t(dummy);
  //  //  std::thread t2([&](){ c = dummier(a, b); });
  //  //  std::thread t3(pow, std::ref(c));
  //  std::thread t4([&]() { result = a.ADummy(); });

  //  for (int i = 0; i < 10; ++i)
  //    {
  //      std::this_thread::sleep_for(std::chrono::milliseconds(500));
  //      std::cout << "main i = " << i << " " << std::this_thread::get_id()  << std::endl;
  //    }

  //  //  t2.join();
  //  //  t3.join();
  //  //  t.join();
  //  t4.join();

  //  //std::cout << "C = " << c << std::endl;
  //  std::cout << "Result = " << result << std::endl;
}

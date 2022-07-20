#include <cstdlib>
#include <functional>
#include <iostream>
#include <mutex>

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "thread_executor.h"

static std::mutex print_mutex;

void f(int i) {
  print_mutex.lock();
  std::cout << "Thread " << i << " sleeping" << std::endl;
  print_mutex.unlock();
  sleep(2);
  print_mutex.lock();
  std::cout << "Thread " << i << " finished sleeping" << std::endl;
  print_mutex.unlock();
}

int main() {
  int n_threads = 2;
  ThreadExecutor executor(n_threads);
  std::cout << "Using " << n_threads << " threads" << std::endl;

  executor.run(f, 1);
  executor.run(f, 2);
  executor.run(f, 3);
  executor.run(f, 4);
  executor.run(f, 5);
  executor.run(f, 6);

  return 0;
}

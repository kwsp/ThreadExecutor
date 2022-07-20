#include <queue>
#include <thread>

#include <iostream>

class ThreadExecutor {
public:
  ThreadExecutor(int N_THREADS = std::thread::hardware_concurrency())
      : _N_THREADS(N_THREADS) {}

  ~ThreadExecutor() {
    join();
  }

  template <class Function, class... Args>
  void run(Function &&f, Args &&...args) {
    if (_threads.size() >= _N_THREADS) {
      if (_threads.front().joinable())
        _threads.front().join();
      _threads.pop();
    }
    _threads.emplace(f, std::forward<Args>(args)...);
  }

  // Wait for all threads to join
  void join() {
    while (!_threads.empty()) {
      _threads.front().join();
      _threads.pop();
    }
  }

private:
  std::queue<std::thread> _threads;
  int _N_THREADS;
};


// Andres.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <ctime>
#define PORT_MAX 100

using namespace std;

queue<int> jobs;
int outcome[PORT_MAX];

mutex tokyo; // the lock for the outcome array
mutex helsinki; // the lock for the job queue
mutex rio; // the lock for stdout

/* RAII Technique
*  Use objects to manage resources.
*/
class Lock {
private:
  mutex* m_Mutex;
public:
  explicit Lock(mutex* mtx)
  {
    mtx->lock();
    m_Mutex = mtx;
  }
  ~Lock()
  {
    m_Mutex->unlock();
  }
};

/* Functor
*/
class Worker {
public:
  int currentPort;
  string myName;

  virtual int operator() (string name, int max) 
  {
    myName = name;
    while (!jobs.empty()) 
    {
      // Get a port to work on
      getJob();
      // Do IPPort stuff
      for (int i = 0; i < max; i++) {}
      // Mark the status of the port after testing
      log();
      markPortAsOpen();
    }

    return 0;
  }
private:
  void log() {
    Lock mylock(&rio);
    cout << myName << " marking " << currentPort << " as open." << endl;
  }
  void markPortAsOpen() 
  {
    Lock mylock(&tokyo);
    outcome[currentPort] = 1;
  }
  void markPortAsClosed()
  {
    Lock mylock(&tokyo);
    outcome[currentPort] = 2;
  }
  void getJob() 
  {
    Lock mylock(&helsinki);
    currentPort = jobs.front();
    jobs.pop();
  }
};

int main()
{
  // populate the outcomes with untested indicators
  for (int i = 0; i < PORT_MAX; i++) {
    outcome[i] = i;
  }

  // add all the ports to the job queue
  for (int i = 0; i < PORT_MAX; i++) {
    jobs.push(i);
  }
  Worker pinger; 

  thread t1(pinger, "worker1", 999);
  thread t2(pinger, "worker2", 777);
  thread t3(pinger, "worker3", 555);
  thread t4(pinger, "worker4", 300);

  t1.join();
  t2.join();
  t3.join();
  t4.join();


  return 0;
}


//std::clock_t start;
//double duration;
//start = std::clock();
//duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
//std::cout << "Duration: " << duration << '\n';
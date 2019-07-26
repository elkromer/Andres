// Andres.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <ctime>
#include "ipworks.h"

#define PORT_MAX 200

using namespace std;

queue<int> jobs;
int outcome[PORT_MAX];

mutex tokyo; // the lock for the outcome array
mutex helsinki; // the lock for the job queue

void log(string msg) {
  cout << msg << endl;
}

class Scour : public IPPort {
public:
  virtual int FireConnectionStatus(IPPortConnectionStatusEventParams* e) {
    //log(e->ConnectionEvent);
    return 0;
  };
  virtual int FireDataIn(IPPortDataInEventParams* e) {
    //log(e->Text);
    return 0;
  };
  virtual int FireConnected(IPPortConnectedEventParams* e) {
    //log("Connected.");
    return 0;
  };
  virtual int FireDisconnected(IPPortConnectedEventParams* e) {
    //log("Disconnected.");
    return 0;
  };
};

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

  virtual int operator() () 
  {
    while (!jobs.empty()) 
    {
      doTCPHandshake() ? markPortAsClosed() : markPortAsOpen();
    }
    return 0;
  }
private:
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
  void getPort() 
  {
    Lock mylock(&helsinki);
    currentPort = jobs.front();
    jobs.pop();
  }
  int doTCPHandshake()
  {
    getPort();
    Scour s;
    s.SetRemoteHost("localhost");
    s.SetRemotePort(currentPort);
    int retcode = s.SetConnected(true);
    s.Reset();
    return (retcode ? retcode : 0);
  }
};
//s.SendLine("SSH-2.0-PuTTY_Release_0.72");

void initialize() {
  // populate the outcome array with indicators that the ports are untested
  for (int i = 0; i < PORT_MAX; i++) {
    outcome[i] = i;
  }
  // add all the ports to the job queue
  for (int i = 0; i < PORT_MAX; i++) {
    jobs.push(i);
  }
}

int main()
{
  initialize();
  cout << thread::hardware_concurrency << endl;

  Worker worker1;
  Worker worker2;
  Worker worker3;

  std::clock_t start;
  double duration;
  start = std::clock();
  thread t1(worker1);
  thread t2(worker2);
  thread t3(worker3);
  thread t4(worker1);
  thread t5(worker2);
  thread t6(worker3);
  thread t7(worker1);
  thread t8(worker2);
  thread t9(worker3);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  t9.join();
  duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
  std::cout << "Duration: " << duration << '\n';


  for (int i = 0; i < PORT_MAX; i++) {
    cout << i << ": " << ((outcome[i] == 1) ? "open":"closed") << endl;
  }

  return 0;
}
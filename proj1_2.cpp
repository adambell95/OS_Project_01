/*
  Names:        Parker Tuck, 
  Class:        CSCE 4600 - Operating Systems
  Instructor:   Armin R. Mikler
  Description:  This .cpp file should only do problem #1 as of right now
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>

#define NPROCESSES 10  // number of proceses required
#define MAXPROCESSES 40 // might take out later

using namespace std;

// need 200 processes
struct Process {
  int pid;        // just an identifier for the program, not required
  int burst_time; // 10 * 10^6 cycles – 50 *10^12 cycles
  double mem_size;   // .25 MB - 8 GB
};

class Processor {

private:

	struct node {
	  int pid_val;	//TODO int
    int burst_val;
    double mem_size_val;
	  struct node *next;
	};
	struct node *headPtr, *tailPtr;
	int numOfItems, avg_time, total_time, mem_avail;

public:

  Processor();
//  ~Processor();
  void add(const Process &);
  void remove();
  void print();
  void setP1MemAvail();   // should be 2 GB
  void setP2MemAvail();   // Shoudl be 2 GB
  void setP3MemAvail();   // should be 4 GB
  void setP4MemAvail();   // should be 4 GB
  void setP5MemAvail();   // should be 8 GB
	
};

Processor::Processor() {
  this->headPtr = NULL;
  this->tailPtr = NULL;
  this->numOfItems = 0;
  this->avg_time = 0;
  this->total_time = 0;
  this->mem_avail = 0;
}

/*
Processor::~Processor() {
   int idx = 0;
  for ( idx = 0; idx < numOfItems; idx++ ) {
    
  }
}
*/

/*
  Adds node to processor queue, no specific order in which the processes
  are listed as of right now.
*/
void Processor::add(const Process &processes) {
  struct node *newNodePtr = new node;
  newNodePtr->pid_val = processes.pid;
  newNodePtr->mem_size_val = processes.mem_size;
  newNodePtr->burst_val = processes.burst_time;
	newNodePtr->next = NULL;

	if ( numOfItems == 0 ) {
		this->headPtr = newNodePtr;
		this->tailPtr = newNodePtr;
		this->numOfItems++;
    this->total_time += processes.burst_time;
		return;
	}

	this->tailPtr->next = newNodePtr;
	this->tailPtr = newNodePtr;
	this->numOfItems++;
  
}

/*
*/
void Processor::remove() {
  if ( numOfItems == 0 )
    return;
}

/*
  Set memory available in this processor to 2 GB or 2000 MB
*/
void Processor::setP1MemAvail() {
  this->mem_avail = 2000;   // 2000 MB = 2 GB
}
/*
  Set memory available in this processor to 2 GB or 2000 MB
*/
void Processor::setP2MemAvail() {
  this->mem_avail = 2000;   // 2000 MB = 2 GB
}

/*
  Set memory available in this processor to 4 GB or 4000 MB
*/
void Processor::setP3MemAvail() {
  this->mem_avail = 4000;   // 4000 MB = 4 GB
}

/*
  Set memory available in this processor to 4 GB or 4000 MB
*/
void Processor::setP4MemAvail() {
  this->mem_avail = 4000;   // 4000 MB = 4 GB
}

/*
  Set memory available in this processor to 8 GB or 8000 MB
*/
void Processor::setP5MemAvail() {
  this->mem_avail = 8000;   // 8000 MB = 8 GB
}

/*
*/
void Processor::print() {
  if ( this->numOfItems == 0 ) {
    cout << "No processes in processor.\n";
    return;
  }
  
  struct node *tempPtr;
  tempPtr = this->headPtr;
  while ( tempPtr != NULL ) {
    cout << tempPtr->burst_val << endl;
    tempPtr = tempPtr->next;
  }
  cout << "total time: " << this->total_time << endl;
}

int findBurstTime();
double findMemSize();

int main() {

  Processor P1, P2, P3, P4, P5;
  P1.setP1MemAvail(); P2.setP2MemAvail(); P3.setP3MemAvail(); P4.setP4MemAvail(); P5.setP5MemAvail();
  struct Process p[NPROCESSES+1];
  int idx = 0, burstTotal = 0, burst_avg = 0;
  srand(time(NULL));
  
  for ( idx = 0; idx <= NPROCESSES; idx++ ) {
    p[idx].pid = idx;
    p[idx].burst_time = findBurstTime();  // change value later
    p[idx].mem_size = findMemSize()/100;    // change value later
    P1.add(p[idx]);     // this is how you add processes to processor
  }
  
  /*
  for (idx = 0; idx <+ NPROCESSES; idx++) {
    burstTotal += p[idx].burst_time;
    cout << p[idx].burst_time << endl;
  }*/
  
  //burst_avg = burstTotal / 200;
  //cout << endl << burst_avg << endl << endl;
  P1.print();
  
  return 0;
}

/*
  Returns a random number to each unique process between 10 * 10^6 cycles – 50 *10^12 cycles
*/
int findBurstTime() {
  // generating a few negative numbers, FIX LATER
  return rand() % (49999990000000) + (10000000); 
}

/*
  Returns a random number to each unique process between .25 MB - 8 GB
*/
double findMemSize() {
  return rand() % 799975 + 25 ; // number returned is divided by 100 
                                // to convert it back to MB
}




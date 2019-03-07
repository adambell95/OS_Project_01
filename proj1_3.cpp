/*
  Names:        Parker Tuck, Adam Bell
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
	int numOfItems, avg_time, total_time, mem_avail, speed_ghz;

public:

  Processor();
//  ~Processor();
  void add(const Process &);
  void remove();
  void print();
  void setP1speed();   // should be 2 GHz
  void setP2speed();   // should be 2 GHz
  void setP3speed();   // should be 3 GHz
  void setP4speed();   // should be 3 GHz
  void setP5speed();   // should be 4 GHz
  
};

Processor::Processor() {
  this->headPtr = NULL;
  this->tailPtr = NULL;
  this->numOfItems = 0;
  this->avg_time = 0;
  this->total_time = 0;
  this->mem_avail = 8000;  // 8 GB or 8000 MB
  this->speed_ghz = 0;
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
  Set speed of processor 1 to 2 Ghz
*/
void Processor::setP1speed() {
  this->speed_ghz = 2;  // speed set to 2 GHz
}

/*
  Set speed of processor 2 to 2 Ghz
*/
void Processor::setP2speed() {
  this->speed_ghz = 2;  // speed set to 2 GHz
}

/*
  Set speed of processor 3 to 3 Ghz
*/
void Processor::setP3speed() {
  this->speed_ghz = 3;  // speed set to 3 GHz
}

/*
  Set speed of processor 4 to 3 Ghz
*/
void Processor::setP4speed() {
  this->speed_ghz = 3;  // speed set to 3 GHz
}

/*
  Set speed of processor 5 to 4 Ghz
*/
void Processor::setP5speed() {
  this->speed_ghz = 4;  // speed set to 4 GHz
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
    cout << tempPtr->mem_size_val << endl;  // prints mem size of each process
//    cout << tempPtr->burst_val << endl;   // prints burst time of each process
    tempPtr = tempPtr->next;
  }
  cout << "total time: " << this->total_time << endl;
}

int findBurstTime();
double findMemSize();

int main() {

  Processor P1, P2, P3, P4, P5;
  P1.setP1speed(); P2.setP2speed(); P3.setP3speed(); P4.setP4speed(); P5.setP5speed();
  struct Process p[NPROCESSES+1];
  int idx = 0, burstTotal = 0, burst_avg = 0;
  srand(time(NULL));
  
  for ( idx = 0; idx <= NPROCESSES; idx++ ) {
    p[idx].pid = idx;
    p[idx].burst_time = findBurstTime();  // change value later
    p[idx].mem_size = findMemSize()/100;    // change value later
    P1.add(p[idx]);     // this is how you add processes to processor
  }
  
  
  for (idx = 0; idx <+ NPROCESSES; idx++) {
    burstTotal += p[idx].burst_time;
    if ( p[idx].mem_size > 4000 )
       P5.add(p[idx]);  // if mem size of process is > 4 GB, it has to go to processor 5
    //cout << p[idx].burst_time << endl;
  }
  
  //burst_avg = burstTotal / 200;
  //cout << endl << burst_avg << endl << endl;
  cout << "Processor 1 List:" << endl;
  P1.print();
  cout << "\nProcessor 2 List:\n"; 
  P2.print();
  cout << "\nProcessor 3 List:\n"; 
  P3.print();  
  cout << "\nProcessor 4 List:\n"; 
  P4.print();  
  cout << "\nProcessor 5 List:\n"; 
  P5.print();
  
  return 0;
}

/*
  Returns a random number to each unique process between 10 * 10^6 cycles – 50 *10^12 cycles
*/
int findBurstTime() {
  // TODO: generating a few negative numbers, FIX LATER
  return rand() % (49999990000000) + (10000000); 
}

/*
  Returns a random number to each unique process between .25 MB - 8 GB
*/
double findMemSize() {
  return rand() % 799975 + 25 ; // number returned is divided by 100 
                                // to convert it back to MB
}




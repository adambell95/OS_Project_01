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
	int numOfItems, avg_time, total_time, mem_avail, speed_ghz, processNum;

public:

  Processor();
  ~Processor();
  void add(const Process &);
  void remove();
  void print();
  void setProcessNum(int num);	// either 1, 2, 3, 4, or 5
  void setSpeed(int num);   // should be 2, 3, or 4 GHz

};

Processor::Processor() {
  this->headPtr = NULL;
  this->tailPtr = NULL;
  this->numOfItems = 0;
  this->avg_time = 0;
  this->total_time = 0;
  this->mem_avail = 8000;  // 8 GB or 8000 MB
  this->speed_ghz = 0;
  this->processNum = 0;
}


Processor::~Processor() {
   int idx = 0;
  for ( idx = 0; idx < numOfItems; idx++ ) {
	  this->remove();
  }
}


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
		this->total_time += newNodePtr->burst_val;
		return;
	}

	this->tailPtr->next = newNodePtr;
	this->tailPtr = newNodePtr;
	this->total_time += newNodePtr->burst_val;
	this->numOfItems++;
}

/*
 *
*/
void Processor::remove() {
  if ( numOfItems == 0 )
    return;

  // remove head node, assign next node as head, delete old head, decrease number of items in queue
    struct node *tempNode = this->headPtr;	// tempNode = node being removed
    this->headPtr = tempNode->next;			// assign the next node in queue as the headPtr
    delete tempNode;						// delete the old head node
    this->numOfItems--;						// decrease number of items in queue by one
}

/*
 *
 */
void Processor::setProcessNum(int num) {
	this->processNum = num; 	// either 1, 2, 3, 4, or 5
}

/*
  Set speed of processor 1 to 2 Ghz
*/
void Processor::setSpeed(int num) {
  this->speed_ghz = num;  // speed set to 2 GHz
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
  cout << "Turnaround Time of Processor " << this->processNum << ": " << this->total_time << endl;
}

int findBurstTime();
double findMemSize();

int main() {

  Processor P1, P2, P3, P4, P5;
  P1.setProcessNum(1); P2.setProcessNum(2); P3.setProcessNum(3); P4.setProcessNum(4); P5.setProcessNum(5);
  P1.setSpeed(2); P2.setSpeed(2); P3.setSpeed(3); P4.setSpeed(3); P5.setSpeed(4);

  struct Process p[NPROCESSES+1];
  int idx = 0, burstTotal = 0, burst_avg = 0, counter = 0;

  srand(time(NULL));

  for ( idx = 0; idx <= NPROCESSES; idx++ ) {
    p[idx].pid = idx;
    p[idx].burst_time = findBurstTime();  // change value later
    p[idx].mem_size = findMemSize()/100;    // change value later
    P1.add(p[idx]);     // this is how you add processes to processor
  }

  // TODO sort
  // processes with larger burst_times should be assigned to processors with higher speed (GHz)

  //burst_avg = burstTotal / 200;
  //cout << endl << burst_avg << endl << endl;
  P1.print(); P2.print(); P3.print(); P4.print(); P5.print();

  return 0;
}

/*
  Returns a random number to each unique process between 10 * 10^6 cycles – 50 *10^12 cycles
*/
int findBurstTime() {
  // TODO: generating a few negative numbers, FIX LATER
  return rand() % (4999999) + (1);
}

/*
  Returns a random number to each unique process between .25 MB - 8 GB
*/
double findMemSize() {
  return rand() % 799975 + 25 ; // number returned is divided by 100
                                // to convert it back to MB
}




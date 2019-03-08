/*
  Names:        Parker Tuck,
  Class:        CSCE 4600 - Operating Systems
  Instructor:   Armin R. Mikler
  Description:  This .cpp file should only do problem #1 as of right now
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>

#define NPROCESSES 200  // number of proceses required
#define NPROCESSORS 5	// number of processors required

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
	int numOfItems, avg_time, total_time, mem_avail, processNum;

public:

  Processor();
  ~Processor();
  void add(const Process &);
  void remove();
  void print();
  void setMemAvail(int memory);   // should be 2, 4, or 8 GB
  void setProcessNum(int num);
  bool isOverAvgTime(int avg_turnaround_time);
  int getTotalTime();

};

Processor::Processor() {
  this->headPtr = NULL;
  this->tailPtr = NULL;
  this->numOfItems = 0;
  this->avg_time = 0;
  this->total_time = 0;
  this->mem_avail = 0;
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
		this->total_time += processes.burst_time;
		return;
	}

	this->tailPtr->next = newNodePtr;
	this->tailPtr = newNodePtr;
	this->total_time += newNodePtr->burst_val;
	this->numOfItems++;

}

/*
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
  Set memory available in this processor to 2 GB or 2000 MB
*/
void Processor::setMemAvail(int memory) {
  this->mem_avail = memory;   // 2000 MB = 2 GB, 4000 MB = 4 GB, or 8000 MB = 8 GB
}

void Processor::setProcessNum(int num) {
	this->processNum = num;		// either 1, 2, 3, 4, or 5
}

/*
 * Returns true = turnaround time of processor is greater than the estimated optimal turnaround time per processor
 */
bool Processor::isOverAvgTime(int avg_turnaround_time) {
	return (this->total_time > avg_turnaround_time);
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
    //cout << tempPtr->burst_val << endl;
    tempPtr = tempPtr->next;
  }
  cout << "Number of Cycles on Processor " << this->processNum << ": " << this->total_time << endl;
}

/*
 *
 */
int Processor::getTotalTime() {
	return this->total_time;
}

int findBurstTime();
double findMemSize();
void sortProcessesByTime(struct Process processArray[], int arraySize);

int main() {

  Processor P[NPROCESSORS];
  for ( int idx = 0; idx < NPROCESSORS; idx++ ) {
	P[idx].setProcessNum(idx+1);
	if ( idx == 0 || idx == 1 )
		P[idx].setMemAvail(2000);
	else if ( idx == 2 || idx == 3 )
		P[idx].setMemAvail(4000);
	else
		P[idx].setMemAvail(8000);
  }

  struct Process p[NPROCESSES+1];

  int idx = 0, burstTotal = 0, burst_avg = 0, temp_burst = 0;;
  srand(time(NULL));
  //srand(1);

  for ( idx = 0; idx < NPROCESSES; idx++ ) {
    p[idx].pid = idx;
	temp_burst = findBurstTime();
	p[idx].burst_time = temp_burst;  // change value later; Value * 10^7
	burstTotal += temp_burst;
	p[idx].mem_size = findMemSize()/100;    // change value later
  }

  // sort processes into descending order
  sortProcessesByTime(p, NPROCESSES);

/*
  // prints either burst time or mem size of each processes
  for (idx = 0; idx <+ NPROCESSES; idx++) {
    //cout << p[idx].burst_time << endl;
    cout << p[idx].mem_size << endl;
  }
*/

  int smallCounter = 0, mediumCounter = 0, totalCounter = 0;
  for (idx = 0; idx < NPROCESSES; idx++) {
	  if ( p[idx].mem_size > 4000 ){
		  P[4].add(p[idx]);  // if mem size of process is > 4 GB, it has to go to processor 5
		  totalCounter++;
	  }
	  else if ( (p[idx].mem_size > 2000) && (p[idx].mem_size <= 4000) ) {
		  // alternates processors and assigns an even number of processes to each processor
		  if ( mediumCounter == 0 ) {
			  P[2].add(p[idx]);
			  mediumCounter = 1;
			  totalCounter++;
		  }
		  else {
			  P[3].add(p[idx]);
			  mediumCounter = 0;
			  totalCounter++;
		  }
	  }
	  else {
		  if ( smallCounter == 0 ) {
			  P[0].add(p[idx]);
			  smallCounter = 1;
			  totalCounter++;
		  }
		  else {
			  P[1].add(p[idx]);
			  smallCounter = 0;
			  totalCounter++;
		  }
	  }
  } // end for

//  cout << "\n" << totalCounter << endl;	// says it reaches 200 but the total times of the processes dont add up to the total
  	  	  	  	  	  	  	  	  	  	  	// time calculated in main??
//  return 0;

  cout << "Total cycles of all processes:    " << burstTotal;
  burst_avg = burstTotal/NPROCESSORS;
  cout << "\nOptimal cycles on each processor: " << burst_avg << endl;
  cout << "-------------------------------------------------\n";
  // print list of processes in each processor
  int maxTime = 0;
  for ( idx = 0; idx < NPROCESSORS; idx++ ) {
	  P[idx].print();
	  if ( maxTime < P[idx].getTotalTime() )  maxTime = P[idx].getTotalTime();
  }
  cout << "-------------------------------------------------\n";
  float max = maxTime, burst = burst_avg;
  float deviation = max/burst;
  cout << "Largest Number of Cycles on a Processor: " << maxTime << "    Percent difference: " << (deviation - 1) * 100 << "%";

  return 0;
}

/*
  Returns a random number to each unique process between 10 * 10^6 cycles – 50 *10^12 cycles
*/
int findBurstTime() {
  // generating a few negative numbers, FIX LATER
  return rand() % 4999999 + 1;
}

/*
  Returns a random number to each unique process between .25 MB - 8 GB
*/
double findMemSize() {
  return rand() % 799975 + 25 ; // number returned is divided by 100
                                // to convert it back to MB
}

/*
 * Uses in-place bubblesort of Process array using burst-time as basis for ordering.
 * Returns original array in descending burst-time order
 */
void sortProcessesByTime( struct Process processArray[], int arraySize ) {
	if ( arraySize < 2 )
		return;

    for ( int passCtr = 0; passCtr < arraySize; passCtr++ ) // loop arraySize times
    	for ( int ndx = 0; ndx < arraySize ; ndx++ )
    		// swap adjacent elts if in ascending order
            if ( processArray[ndx].burst_time < processArray[ndx+1].burst_time ) {
               struct Process tmpProcess = processArray[ndx];
               processArray[ndx] = processArray[ndx+1];
               processArray[ndx+1] = tmpProcess;
            }
}




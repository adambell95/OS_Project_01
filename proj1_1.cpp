/*
  Names:        Parker Tuck, Adam Bell
  Class:        CSCE 4600 - Operating Systems
  Instructor:   Armin R. Mikler
  Description:  proj1_1.cpp answers Question #1 of the assignment. This program will initialize a set of 5 processors, a set of
  	  	  	  	200 processes, sort the processes in descending order, assign the processes to processors, then display the
  	  	  	  	data to the screen for the user to see. The percent difference between the optimal number of cycles on each
  	  	  	  	processor and actual number of cycles on each processor is almost always below 5%.
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <bits/stdc++.h>

#define NPROCESSES 200  // number of processes required
#define NPROCESSORS 5	// number of processors required

using namespace std;

// need 200 processes
struct Process {
  int pid;        	 // just an identifier for the program, not required
  int burst_time; 	 // 10 * 10^6 cycles – 50 *10^12 cycles
  double mem_size;   // .25 MB - 8 GB
};

class Processor {

private:

	struct node {
	  int pid_val;
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
  void setProcessNum(int num);
  int getTotalTime();

};

/*
 * Processor constructor. Initializes all the original values of each processor to NULL or 0. Except the mem_avail
 * because in the instructions it states that all of the processors should have 8 GB of memory available.
 */
Processor::Processor() {
  this->headPtr = NULL;
  this->tailPtr = NULL;
  this->numOfItems = 0;
  this->avg_time = 0;
  this->total_time = 0;
  this->mem_avail = 8000;  // 8 GB or 8000 MB
  this->processNum = 0;
}

/*
 * Processor destructor. Deletes every process in its queue, starting with the headPtr
 */
Processor::~Processor() {
   int idx = 0;
  for ( idx = 0; idx < numOfItems; idx++ ) {
	  this->remove();
  }
}


/*
 * Adds node/process to the processor queue. Processes in the processor should be listed from processes
 * with the greatest burst time to the smallest burst time (descending order)
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
 * Only used by the destructor. Deletes each node in the processor queue one by one, starting with the headPtr.
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
 * Print the total turnaround time of the processor
*/
void Processor::print() {
  if ( this->numOfItems == 0 ) {
    cout << "No processes in processor.\n";
    return;
  }

  struct node *tempPtr;
  tempPtr = this->headPtr;
  while ( tempPtr != NULL ) {
//    cout << tempPtr->mem_size_val << endl;  // prints mem size of each process
//    cout << tempPtr->burst_val << endl;   // prints burst time of each process
    tempPtr = tempPtr->next;
  }
  cout << "Number of Cycles on Processor " << this->processNum << ": " << this->total_time << endl;
}

/*
 *	Set the processor value of each processor
 */
void Processor::setProcessNum(int num) {
	this->processNum = num;
}

/*
 *	returns total turnaround time of the processor to main
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
  }

  struct Process p[NPROCESSES+1];

  int idx = 0, burstTotal = 0, burst_avg = 0, temp_burst = 0, counter = 1;
  // srand(1);
  srand(time(NULL));

  // initialize set of processes
  for ( idx = 0; idx < NPROCESSES; idx++ ) {
    p[idx].pid = idx;
    temp_burst = findBurstTime();
    p[idx].burst_time = temp_burst;  // change value later = * 10^7
    burstTotal += temp_burst;
    p[idx].mem_size = findMemSize()/100;    // change value later
  }

  // sort processes into descending order
  sortProcessesByTime(p, NPROCESSES);

  // use RR to allocate processes
  for ( idx = 0; idx < NPROCESSES; idx++ ) {
    counter = idx % NPROCESSORS;
    P[counter].add(p[idx]);
  }

/*
  // prints entire list of process burst times
  for (idx = 0; idx <+ NPROCESSES; idx++) {
    //burstTotal += p[idx].burst_time;
    cout << p[idx].burst_time << endl;
    cout << p[idx].mem_size << endl;
  }
*/

  cout << "Total cycles of all processes:\t\t    " << burstTotal;
  burst_avg = burstTotal / 5;
  cout << "\nOptimal number of cycles on each processor: " << burst_avg << endl;
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
  cout << "Largest Number of Cycles on a Processor: " << maxTime << "\nPercent difference: " << (deviation - 1) * 100 << "%";
  cout << endl;
	
  return 0;
}

/*
  Returns a random number to each unique process between 10 * 10^6 cycles – 50 *10^12 cycles. Except I got rid of all
  the zeroes because the random function was having a hard time creating numbers that high. All burst time values should
  be regarded as that number * 10^7
*/
int findBurstTime() {
  // generating a few negative numbers, FIX LATER
  return rand() % 4999999 + 1;	// all numbers should be regarded to as * 10^7
}

/*
  Returns a random number to each unique process between .25 MB - 8 GB
*/
double findMemSize() {
  return rand() % 799975 + 25 ; // number returned is divided by 100 to convert it back to MB
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


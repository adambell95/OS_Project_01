/*
  Names:        Parker Tuck, Adam Bell
  Class:        CSCE 4600 - Operating Systems
  Instructor:   Armin R. Mikler
  Description:  proj1_3.cpp answers Question #3 of the assignment. This program will initialize 5 processors, 200 processes,
  	  	  	  	sort the processes in descending order, add the processes to processors based on their size because the processors
  	  	  	  	with larger speed (GHz) will be able to run through them faster, and then display the results of all the processes
  	  	  	  	to the screen for the user to see/analyze. The cycles are divided by the speed to give the turnaround time, this
  	  	  	  	was calculated by dividing the total number of cycles in each processor by the processor's GHz speed.
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>

#define NPROCESSES 200  // number of processes required
#define NPROCESSORS 5 	// number of processors required

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
		int pid_val;
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
  int getTotalTime();

};

/*
 * Class constructor. This initializes all of the value in a processor; makes the memory available of each processor 8 GB
 */
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

/*
 * Class destructor. Calls remove() which will remove all processes off of the processor one-by-one starting with the head.
 */
Processor::~Processor() {
   int idx = 0;
  for ( idx = 0; idx < numOfItems; idx++ ) {
	  this->remove();
  }
}


/*
  Adds node to processor queue. Queue should be in descending order
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
 * Removes processes from the processor queue one-by-one starting with the head.
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
 *	Sets the processor num of each processor created
 */
void Processor::setProcessNum(int num) {
	this->processNum = num; 	// either 1, 2, 3, 4, or 5
}

/*
  Set speed of processors to 2, 3, or 4 Ghz
*/
void Processor::setSpeed(int num) {
  this->speed_ghz = num;  // speed set to 2, 3, or 4 GHz
}

/*
 * Returns total time of the processor to main
 */
int Processor::getTotalTime() {
	if ( this->processNum == 1 || this->processNum == 2 )
		return ( this->total_time / 200 );
	else if ( this->processNum == 3 || this->processNum == 4 )
		return ( this->total_time / 300 );
	else
		return ( this->total_time / 400 );
}

/*
 * Prints the turnaround time of each processor
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
  if ( this->processNum == 1 || this->processNum == 2 )
	  cout << "Turnaround Time of Processor " << this->processNum << ": " << this->total_time/200 <<
	  	  	  " (Cycles in processor / " << this->speed_ghz << " GHz)" << endl;
  else if ( this->processNum == 3 || this->processNum == 4 )
	  cout << "Turnaround Time of Processor " << this->processNum << ": " << this->total_time/300 <<
	  	  " (Cycles in processor / " << this->speed_ghz << " GHz)" << endl;
  else
	  cout << "Turnaround Time of Processor " << this->processNum << ": " << this->total_time/400 <<
	  	  " (Cycles in processor / " << this->speed_ghz << " GHz)" << endl;

}

int findBurstTime();
double findMemSize();
void sortProcessesByTime(struct Process processArray[], int arraySize);

int main() {

  Processor P[NPROCESSORS];
  for ( int idx = 0; idx < NPROCESSORS; idx++ ) {
	  P[idx].setProcessNum(idx+1);
	  if ( idx == 0 || idx == 1 )
		P[idx].setSpeed(2);
	  else if ( idx == 2 || idx == 3 )
		P[idx].setSpeed(3);
	  else
		P[idx].setSpeed(4);
  }

  struct Process p[NPROCESSES+1];
  int idx = 0, burstTotal = 0, burst_avg = 0, temp_burst = 0;

  //srand(time(NULL));
  srand(15);

  for ( idx = 0; idx <= NPROCESSES; idx++ ) {
    p[idx].pid = idx;
    temp_burst = findBurstTime();
    p[idx].burst_time = temp_burst;  // change value later; Value * 10^7
    burstTotal += temp_burst;
    p[idx].mem_size = findMemSize()/100;    // change value later
  }

  // sort processes into descending order
  sortProcessesByTime(p, NPROCESSES);

  // Processes with larger burst times should go to processors with larger GHz
  int smallCounter = 0, mediumCounter = 0;
  for ( idx = 0; idx < NPROCESSES; idx++ ) {
	  if ( p[idx].burst_time > 3999999 )
		  P[4].add(p[idx]);
	  // 2999999
	  else if ( (p[idx].burst_time > 2500000) && (p[idx].burst_time <= 3999999) ) {
		  if ( mediumCounter == 0 ) {
			  P[3].add(p[idx]);
			  mediumCounter = 1;
		  }
		  else {
			  P[2].add(p[idx]);
			  mediumCounter = 0;
		  }
	  }
	  else {
		  if ( smallCounter == 0 ) {
			  P[1].add(p[idx]);
			  smallCounter = 1;
		  }
		  else {
			  P[0].add(p[idx]);
			  smallCounter = 0;
		  }
	  }
  } // end for

/*
  // prints entire list of process burst times
  for (idx = 0; idx <+ NPROCESSES; idx++) {
    cout << p[idx].burst_time << endl;
    //cout << p[idx].mem_size << endl;
  }
*/

  cout << "Total cycles of all processes:    " << burstTotal;
  burst_avg = burstTotal/NPROCESSORS;
  cout << "\nOptimal number of cycles on each processor: " << burst_avg << endl;
  cout << "-------------------------------------------------\n";
  // print list of processes in each processor
  int maxTime = 0;
  for ( idx = 0; idx < NPROCESSORS; idx++ ) {
	  P[idx].print();
	  if ( maxTime < P[idx].getTotalTime() )
		  maxTime = P[idx].getTotalTime();
  }
  cout << "-------------------------------------------------\n";
  cout << "Longest Processor Time: " << maxTime << " (Cycles in processor / GHz)" << endl;

  return 0;
}

/*
  Returns a random number to each unique process between 10 * 10^6 cycles – 50 *10^12 cycles
*/
int findBurstTime() {
  return rand() % (4999999) + (1);
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




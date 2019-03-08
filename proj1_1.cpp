/*
  Names:        Parker Tuck,
  Class:        CSCE 4600 - Operating Systems
  Instructor:   Armin R. Mikler
  Description:  This .cpp file should only do problem #1 as of right now
*/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <bits/stdc++.h>

#define NPROCESSES 10  // number of processes required
#define MAXPROCESSES 40 // might take out later

using namespace std;

// need 200 processes
struct Process {
  int pid;        	// just an identifier for the program, not required
  int burst_time; 	// 10 * 10^6 cycles – 50 *10^12 cycles
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

};

Processor::Processor() {
  this->headPtr = NULL;
  this->tailPtr = NULL;
  this->numOfItems = 0;
  this->avg_time = 0;
  this->total_time = 0;
  this->mem_avail = 8000;  // 8 GB or 8000 MB
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
    cout << tempPtr->burst_val << endl;   // prints burst time of each process
    tempPtr = tempPtr->next;
  }
  cout << "Turnaround Time of Processor " << this->processNum << ": " << this->total_time << endl;
}

/*
 *
 */
void Processor::setProcessNum(int num) {
	this->processNum = num;
}


int findBurstTime();
double findMemSize();
void sortDescending(Process p[], int nprocesses);
bool compareTwoProcesses(Process a, Process b);

int main() {

  Processor P1, P2, P3, P4, P5;
  P1.setProcessNum(1); P2.setProcessNum(2); P3.setProcessNum(3); P4.setProcessNum(4); P5.setProcessNum(5);

  struct Process p[NPROCESSES+1];

  int idx = 0, burstTotal = 0, burst_avg = 0, temp_burst = 0, counter = 1;
  srand(time(NULL));

  // initialize set of processes
  for ( idx = 0; idx <= NPROCESSES; idx++ ) {
    p[idx].pid = idx;
    temp_burst = findBurstTime();
    p[idx].burst_time = temp_burst;  // change value later
    burstTotal += temp_burst;
    p[idx].mem_size = findMemSize()/100;    // change value later

    if ( counter == 1 ) {
        P1.add(p[idx]);     // this is how you add processes to processor
        counter = 2;
    }
    else if ( counter == 2 ) {
    	P2.add(p[idx]);
    	counter = 3;
    }
    else if ( counter == 3 ) {
        P3.add(p[idx]);     // this is how you add processes to processor
        counter = 4;
    }
    else if ( counter == 4 ) {
        P4.add(p[idx]);     // this is how you add processes to processor
        counter = 5;
    }
    else {
    	P5.add(p[idx]);
    	counter = 1;
    }
  }

  int nprocesses = NPROCESSES;
//  sortDescending(*p, nprocesses);
//  sort(p, p + nprocesses, compareTwoProcesses);

  /*
  for (idx = 0; idx <+ NPROCESSES; idx++) {
    burstTotal += p[idx].burst_time;
    cout << p[idx].burst_time << endl;
  }*/


  // print list of processes in each processor
  P1.print(); P2.print(); P3.print(); P4.print(); P5.print();
  cout << "Total turnaround time of all processes: " << burstTotal;
  burst_avg = burstTotal / 5;
  cout << "\nOptimal turnaround time of each processor: " << burst_avg;

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
 *
 *
void sortDescending(Process p[], int nprocesses) {
	int idx = 0, ndx = 0;
	struct Process *tempPtr;
	for (idx = 0; idx < nprocesses; idx++ ) {
		for (ndx = idx + 1; ndx < nprocesses; ndx++) {
			if ( p[idx].burst_time < p[ndx].burst_time ) {
				tempPtr->burst_time = p[idx].burst_time;
				tempPtr->mem_size = p[idx].mem_size;
				tempPtr->pid = p[idx].pid;
				p[idx] = p[ndx];
				p[ndx] = tempPtr;
				delete tempPtr;
			}
		}
	}
}
*/
/*
 *
 */
bool compareTwoProcess(Process a, Process b) {
	return a.burst_time > b.burst_time;
}

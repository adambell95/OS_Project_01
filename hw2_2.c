/*
  Name:        Parker Tuck, parkertuck@my.unt.edu, prt0049, 11107228
  Class:       CSCE 4600.001 - Operating Systems Design
  Instructor:  Armin R. Mikler
  Description: Creates N number of processes globally defined underneath the "#include"'s and evenly distributes the number of CPU-cyles and
		memory footprint size so that the mean of all the process's CPU-cycles is 6,000 cycles and mean memory footprint size is
		20KB. The program will also display the distribution of CPU-cycles and mem-size of each process PID to the screen so that the
		user can see how they are distributed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define KPROCESSES 10

struct process {
  int pid;
  int cycles;
  int mem_size;
};

int findCycleNum( int mean_cycles, int idx, int positive, int negative);
int findKBNum( int mean_kb, int idx, int positive, int negative);

int main() {

  struct process p[KPROCESSES+1];
  int low_cycles = 1000, high_cycles = 11000, mean_cycles = 6000;   // number of cycles values for CPU-cycles requiredto complete the process
  int low_kb = 1, high_kb = 100, mean_kb = 20;                      // KB values for memory footprints
  int idx = 0, positive = 1, negative = 1;

  for ( idx = 1; idx <= KPROCESSES; idx++ ) {
    p[idx].pid = idx;
    p[idx].cycles = findCycleNum(mean_cycles, idx, positive, negative);
    p[idx].mem_size = findKBNum(mean_kb, idx, positive, negative);

    if ( idx % 2 == 0 )
      positive++;
    else if ( idx % 2 != 0 && idx != 1 )
      negative++;
  }

  // print values of each p[idx] to screen
  for ( idx = 1; idx <= KPROCESSES; idx++ ) {
    printf("PID Numer: %d\n", p[idx].pid);
    printf("CPU-cycles required to complete the process: %d CPU-cycles\n", p[idx].cycles);
    printf("Size of memory footprint: %dKB\n\n", p[idx].mem_size);
  }

  return 0;
}

/*
  Will return a random number of cycles back to main to be assigned to a unique PID number.
  Mean needs to be 6000
*/
int findCycleNum(int mean_cycles, int idx, int positive, int negative) {

  int temp = 0;

  if ( idx == 1 || positive > 5000 || negative > 5000 )   // if idx == 1, or positive/negative values are outside of cycles range
    return mean_cycles;                                   // return the mean value of cycles (6000)
  else if ( idx % 2 == 0 ) {
    temp = mean_cycles + positive;
    return temp;
  }
  else {
    temp = mean_cycles - negative;
    return temp;
  }
}

/*
  Will return a random number of memory footprint size back to main to be assigned to a unique PID number
*/
int findKBNum(int mean_kb, int idx, int positive, int negative) {

  int tempKB = 0;

  if ( idx == 1 || negative == 20 || positive == 80 )   // if idx is equal to one, or negative/positive values are outside the
    return mean_kb;                                     // range of memory footprint size, return mean value of KB (20)
  else if ( idx % 2 == 0 ) {
    tempKB = mean_kb + positive;
    return tempKB;
  }
  else {
    tempKB = mean_kb - negative;
    return tempKB;
  }
}

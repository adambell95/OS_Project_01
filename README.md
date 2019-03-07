# CSCE 4600
# Spring 2019
# Project #1

Your task is to develop a simulation of a dispatcher/scheduler that assigns processes (or jobs) to a set of available processors or
processing nodes.

Assume that your computing infrastructure has 5 processors available. Processors are identified as PA, PB, … Now
consider n = 200 processes with different runtime requirements. Specifically, each process has associated with it a
burst time (processing time) and a memory requirement. Burst-times are assigned at random (10 * 106 cycles – 50
*1012 cycles). Memory requirements are assigned at random (.25 MB – 8GB). For questions 1 – 3, you may
assume that the set of 200 processes is known a-priori; Hence, you will have to develop a function that can
generate this set with random burst-times and memory requirements.

We can assume that once a process has been dispatched to a specific processor, it will remain with this processor
and once started to execute, it will be completed, i.e., there is no preemption.

## 1. 
Suppose that all 5 processors are identical (i.e., same speed and memory), develop and implement a
scheduling algorithm that assigns the set 200 processes to the 5 processors such that the total turnaround
time to complete all 200 processes is minimized. Can you find the best assignment? How close does your
scheduler approximate the best assignment?

## 2. 
In order to execute a process on a specific processor, sufficient memory has to be available. Assume that
the processing nodes are identical in speed but have the following memory availability: PA= PB = 2 GB,
PC= PD = 4 GB and PE= 8GB. Modify your scheduling algorithm from Q1 to assign the processes to the
corresponding processors. Show how well your algorithm minimizes the turnaround time of the set of 200
processes.

## 3. 
Modify your scheduling algorithm developed in Q1 and Q2 and show the best assignment of processes if
the processors are identical, i.e., 8GB memory available but differ in speed. Specifically: PA= PB = 2 GHz,
PC= PD = 3 GHz and PE= 4 GHz

## 4. 
Last, but not least, develop a scheduling methodology that can deal with the sequential arrival of the 200
processes. That is, the scheduler cannot inspect the entire set of processes but must schedule them one by
one in the order that they arrive. What is the best turnaround time that you can achieve?
NOTE: you do not need to generate actual processes. You only work with the set of “synthetic” processes
created with the method you developed in HW#2.

--------------------------------------------------------------------------------------------------

Parker: I think it'd be better to use a queue to hold the processes in each processor. So that's what I started implementing in the code that I have written so far.
  ALSO ADD YOUR NAMES AT THE HEADER OF EACH FILE
  
  I also recommend that if you want to change code in the files, you should make your own copy of it so that if something doesn't work out, we are not lost on how to get it back to how it was originally.

#ifndef BIGQ_H
#define BIGQ_H
#include "pthread.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Pipe.h"
#include "File.h"
#include "Record.h"
#include <functional>
#include "Sorter.h"
#include "Run.h"
#include "PriorityQueue.h"
using namespace std;

class BigQ {

private:

    Pipe &in;
    Pipe &out;
    OrderMaker sortorder;
    int runlen;

    File sortedFile;
    int currentPages = 0;
    int runCount = 0;
    int totalRecords = 0;
    vector<pair<off_t, off_t>> runLocations;

    pthread_t worker_thread;
    static void* thread_starter(void *context);
    void* WorkerThread();

    void PhaseOne();
    void sortRuns(vector<Record>& runlenRecords);
    void writeSortedRunToFile(vector<Record>& runlenRecords);

    PriorityQueue pq;
    void PhaseTwoLinearScan();
    void PhaseTwoPriorityQueue();

public:
    BigQ (Pipe &in, Pipe &out, OrderMaker &sortorder, int runlen);
	~BigQ ();
};

#endif

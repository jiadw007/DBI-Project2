#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Sorter.h"
#include "Run.h"
#include <vector>
using namespace std;
class PriorityQueue{

private:
    bool empty;
    vector<Run> runs;
    Sorter sorter;
public:
    PriorityQueue(int runCount, OrderMaker& om);
    bool isEmpty();
    void getMinRecord(Record& toMe);
};

#endif // PRIORITYQUEUE_H

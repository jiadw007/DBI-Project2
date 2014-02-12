#ifndef SORTER_H
#define SORTER_H
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Record.h"

using namespace std;

class Sorter : binary_function<Record *, Record *, bool>{

private:

    OrderMaker * om;

public:
    Sorter(OrderMaker om);
    bool operator()(Record& first_record, Record& second_record);
    bool operator()(const Record& first_record, const Record& second_record);
    bool operator()(Record* first_record, Record* second_record);
    ~Sorter();

};

class PriorityQueueSorter : binary_function<PriorityQueueRecord *, PriorirtyQueueRecord * ,bool>{

private:
    OrderMaker * om;
public:
    PriorityQueueSorter(OrderMaker om);
    bool operator()(const PriorityQueueRecord& first_record, const PriorityQueueRecord& second_record);
    ~PriorityQueueSorter();

}

#endif // SORTER_H

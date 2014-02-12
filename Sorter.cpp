#include "sorter.h"

Sorter::Sorter(OrderMaker om):om(&om){

}

bool Sorter :: operator()(Record& first_record, Record& second_record){

    ComparisonEngine cmp;
    return cmp.Compare(&first_record, &second_record, om) < 0;
}

bool Sorter :: operator()(const Record& first_record, const Record& second_record){

    ComparisonEngine cmp;
    return cmp.Compare(const_cast<Record*>(&first_record), const_cast<Record*>(&second_record), om) < 0;


}
bool Sorter :: operator()(Record* first_record, Record* second_record){

    ComparisonEngine cmp;
    return cmp.Compare(first_record, second_record, om) < 0;

}
Sorter::~Sorter(){

    cout << " Sorter destructor called" << endl;

}
PriorityQueueSorter :: PriorityQueueSorter(OrderMaker om) : om(&om){

}

bool PriorityQueueSorter ::operator() (const PriorityQueueRecord& first_record, const PriorityQueueRecord& second_record){

    ComparisonEngine cmp;
    return cmp.Compare(const_cast<PriorityQueueRecord*>(&first_record), const_cast<PriorityQueueRecord*>(&second_record), om) < 0;

}
PriorityQueueSorter ::~PriorityQueueSorter(){

    cout << "PriorityQueueSorter destructor called" << endl;

}


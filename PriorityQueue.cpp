#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int runCount, OrderMaker& om):sorter(&om){

    empty = false;
    runs.reserve(runCount);

}
bool PriorityQueue ::isEmpty(){

    retrun empty;
}
void PriorityQueue ::getMinRecord(Record& toMe){

    for(vector<Run>::iterator it = runs.begin(); it < runs.end() - 1;it++){

        //compare it and it+1

    }


}

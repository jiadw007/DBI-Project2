#include "BigQ.h"
#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <cassert>
#include <iterator>
#include "Run.h"

using namespace std;

BigQ :: BigQ(Pipe &in, Pipe &out, OrderMaker &sortorder, int runlen)
    : in(in),out(out), sortorder(sortorder), runlen(runlen),sortedFile(),runLocations(){

    pthread_create(&worker_thread, NULL, &BigQ::thread_starter, this);
}

void* BigQ :: thread_starter(void * context){

    return reinterpret_cast<BigQ*>(context)->WorkerThread();

}
void* BigQ :: WorkerThread(){

    char * sortedFileName = "";
    sortedFile.Open(0, sortedFileName);
    //sort all records from in pipeline
    PhaseOne();
    cout << "total Records: " <<totalRecords << endl;
    //merge all runs
    static const int runThreshold = 200;
    if( runThreshold >= runCount)
        PhaseTwoLinearScan();
    else
        PhaseTwoPriorityQueue();
    sortedFile.Close();
    out.ShutDown();
    pthread_exit(NULL);

}
void BigQ :: PhaseOne(){
	// read data from in pipe sort them into runlen pages
    // PHASE ONE
    size_t bufferSize = runlen;
    vector<Record> runlenRecords;
    runlenRecords.reserve(bufferSize);
    // construct priority queue over sorted runs and dump sorted data 
 	// into the out pipe
    Page p;
    Record tempRecord;
    int pageCounter = 0;
    while ( 1 == in.Remove(&tempRecord)){
        
        Record copyRecord;
        copyRecord.Copy(&tempRecord);
        if( 1 == p.Append(&tempRecord)){ // current page can append this record
            
            runlenRecords.push_back(copy);
            
        }else{ // page is full
            
            pageCounter++;
            
            //need to append this record to a new page
            p.EmptyItOut();
            if(0 == p.Append(&tempRecord)) exit(-1);
            
            //if there are runlen pages of Record,which consists of a run
            if(pageCounter == this->runlen){
                
                this->runCount++;
                if(bufferSize < runlenRecords.size())
                    bufferSize = runlenRecords.size();
                // sort the records in the runlenRecord buffer
                count << "start sorting" << endl;

                this->sortRuns(runlenRecords);
                count << "end sorting" << endl;
                //output records in buffer
                /*
                for(vector<Record>::iterator it = runlenRecords.begin(); it < runlenRecords.end(); it++)
                    out.Insert(&(*it));
                */
                this->writeSortedRunToFile(runlenRecords);
                //reset pageCounter and buffer
                pageCounter  = 0;
                runlenRecords.clear();
                runlenRecrods.push_back(copy);
            }else{

                runlenRecrods.push_back(copy);
            }
            
        }

    }
    //output remaining records in the buffer
    if( 0 < runlenRecords.size()){
        cout<< "sort last run" << endl;
        this->runCount++;
        if(buffersize < runlenRecord.size()) bufferSize = runlenRecords.size();
        sortRuns(runlenRecords);
        /*
        for(vector<Record>::iterator it = runlenRecords.begin(); it < runlenRecord.end(); it++)
            out.Insert(&(*it));
        */
        this->writeSortedRunToFile(runlenRecords);

    }
    runlenRecords.clear();
    cout << "maximum buffer size " << bufferSize << endl;
    // finally shut down the out pipe
	out.ShutDown ();
}
void BigQ :: sortRuns(vector<Record> & runlenRecords){

    sort(runlenRecords.begin(), runlenRecords.end(), Sorter(sortorder));
    cout << "run size " << runlenRecords.size()() << endl;

}
void BigQ :: writeSortedRunToFile(vector<Record>& runlenRecords){

    cout << "start to write sorted runs to file" << endl;
    off_t pageStart = this->currentPages;
    Page page;
    for(vector<Record>:: iterator it = runlenRecords.begin(); it < runlenRecords.end();it++){

        Record record;
        totalRecords++;
        record.Consume(&(*it));
        if(0 == page.Append(&record)){

            this->sortedFile.AddPage(&page,this->currentPages);
            page.EmptyItOut();
            page.Append(&record);
            this->currentPages++;
        }
    }
    this->sortedFile.AddPage(&page,this->currentPages);
    off_t pageEnd = ++this->currentPages;
    cout << "end writing" << endl;
    cout << "insert " << pageEnd - pageStart << " pages" << endl;
    //record which page each run start and end
    runLocations.push_back((make_pair(pageStart, pageEnd)));

}
void BigQ :: PhaseTwoLinearScan(){

    //builds an in-memory priority queue over the head of each run
    //use the queue to merge the records from all of runs.
    //PAHSE TWO
    cout << "Linear scan merge sorted runs" << endl;
    cout << "total runs: " << runCount << endl;
    cout << "total Pages: " << sortedFile.GetLength()<< endl;
    for(vector<pair<off_t, off_t>>:: iterator it = runLocations.begin(); it < runLocations.end(); it++){

        cout << "from " << (*it).first << " to" << (*it).second << endl;
    }
    //merge runs in the linear scanning
    vector<Run> runs;
    runs.reserve(runCount);
    for(int i =0; i < runCount; i++){

        cout << "Run " << i;]
        runs.push_back(Run(i, runLocations[i].first, runLocations[i].second, &sortedFile));
        runs[i].print();
    }
    vector<Record> minimums;
    minimums.reserve(runCount);
    for(int i =0;i < runCount; i++){

        Record record;
        runs[i].getNextRecord(record);
        minimums.push_back(record);
    }

    //find the minimum record and put it in the out pipe
    //loop for totalRecord times
    Sorter sorter = Sorter(sortorder);
    int runsLeft = runCount;
    for(int count = totalRecords; count > 0; count--){

        vector<Record> :: iterator min_record = min_element(minimums.begin(), minimums.end()(),sorter);
        vector<Record> ::iterator::difference_type run = distance(minimums.begin(), min);
        Record record;
        record.Consume(&(minimums[run]);
        out.Insert(&record);
        bool valid = runs[run].getNextRecord(record);
        if(true == valid)
            minimums[run].Consume(&record);
        else{
            cout << "Run " << run <<" is empty " << endl;
            runsleft--;
            minimums.erase(minimums.begin()() + run);
            runs.erase(runs.begin() + run);
        }
    }
    cout << minimums.size() << runs.size() << endl;
    assert(0 == runsLeft);
    cout << "Phase Two Completed" << endl;
}

void BigQ ::PhaseTwoPriorityQueue(){

    //builds an in-memory priority queue over the head of each run
    //use the queue to merge the records from all of runs.
    //PAHSE TWO
    cout << "PriorityQueue merge sorted runs" << endl;
    cout << "total runs: " << runCount << endl;
    cout << "total Pages: " << sortedFile.GetLength()<< endl;
    for(vector<pair<off_t, off_t>>:: iterator it = runLocations.begin(); it < runLocations.end(); it++){

        cout << "from " << (*it).first << " to" << (*it).second << endl;
    }
    //merge runs in the priority queue
    vector<Run> runs;
    runs.reserve(runCount);
    for(int i =0; i < runCount; i++){

        cout << "Run " << i;]
        runs.push_back(Run(i, runLocations[i].first, runLocations[i].second, &sortedFile));
        runs[i].print();
    }
    priority_queue<PriorityQueueRecord, vector<PriorityQueueRecord>, PriorityQueueSorter> minimums (sorter);

    for(int i = 0; i < runCount; i++){

        Record record;
        runs[i].getNextRecord(record);
        minimums.push(PriorityQueueRecord(record, i));

    }
    //find the minimum record and put it in the out pipe
    //loop for totalRecord times
    int runsLeft = runCount;
    int output = 0;
    for(int count = totalRecords; count > 0; count--){

        PriorityQueueRecord pqRecord(minimums.top());
        Record record(pqRecord.record);

        int run = pqRecord.getRun();
        output++;
        out.Insert(&record);
        minimums.pop();
        bool valid = runs[run].getNextRecord(record);
        if(true == valid)
            minimums.push(PriorityQueueRecord(record, run));
        else{

            cout << "Run " << run <<" is empty " << endl;
            runsleft--;

        }
    }
    assert(output == totalRecord);
    assert(0 == runsLeft);
    cout<< "Phase Two Completed" << endl;



}
BigQ::~BigQ () {

    runlocations.clear();

}

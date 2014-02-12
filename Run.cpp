#include "Run.h"

Run :: Run(int runId, off_t start, off_t end, File* sortedFile)
    : runId(runId),start_offset(start), end_offset(end), cur_offset(start), empty(false){

    this->sortedFile = sortedFile;
    this->sortedFile->GetPage(&page,start_offset);
    cout<< "Run constructor called" << sortedFile->GetLength() << endl;
}
Run :: Run(const Run &run){

    cout<< "copy constructor called" << endl;
    runId = run.runId;
    start_offset = run.start_offset;
    end_offset = run.end_offset;
    cur_offset = run.cur_offset;
    empty = run.empty;
    run.sortedFile->AddPage(const_cast<Page*>(&run.p), cur_offset);
    sortedFile = run.sortedFile;
    sortedFile->GetPage(&page,cur_offset);

}

Run& Run :: operator =(const Run& run){

    runId = run.runId;
    start_offset = run.start_offset;
    end_offset = run.end_offset;
    cur_offset = run.cur_offset;
    empty = run.empty;
    run.sortedFile->AddPage(const_cast<Page*>(&run.p), cur_offset);
    sortedFile = run.sortedFile;
    sortedFile->GetPage(&page,cur_offset);

}
bool Run :: getNextRecord(Record& toMe){

    if(1 == page.GetFirst(&record)){// if there is a record in the page

        toMe.Consume(&record);
        return true;
    }else{ // current page is empty

        cur_offset++;
        if(cur_offset < end_offset){ //if next page is in bound

            sortedFile->GetPage(&page, cur_offset);
            if(1 == page.GetFirst((&record))){

                toMe.Consume(&record);
                return true;
            }else // error
                exit(-1);

        }else
            return false;
    }

}
void Run :: print(){

    cout << "Run " << runId << ", start_offset: " << start_offset <<", end_offset" << end_offset << endl;
}
Run :: ~Run(){

    cout << "Run destructor called" << endl;
    cout << "Destroy run " << runId << endl;

}

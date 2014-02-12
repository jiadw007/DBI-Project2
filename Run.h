#ifndef RUN_H
#define RUN_H
#include "Record.h"
#include "File.h"

using namespace std;
class Run{

private:
    int runId;
    off_t start_offset;
    off_t end_offset;
    off_t cur_offset;
    Page page ;
    Record record;
    bool empty;
    File * sortedFile;

public:
    Run(int runId, off_t start, off_t end, File* sortedFile);
    Run(const Run& run);
    Run& operator= (const Run& run);
    bool getNextRecord(Record& toMe);
    void print();
    ~Run();

};

#endif // RUN_H

#ifndef HEAPFILE_H
#define HEAPFILE_H

#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "GenericDBFile.h"

class HeapFile: public GenericDBFile {

public:

    HeapFile();
    ~HeapFile();
    int Create (char* fpath, fType file_type, void* startup);
    int Open (char*fpath);
    int Close();

    void Load(Schema& myschema, char* loadpath);
    void Add(Record& addme);
    void MoveFirst();
    int GetNext(Record& fetchme);
    int GetNext(Record& fetchme, CNF& cnf, Record& literal);

private:

    File f;
    Page curPage;
    off_t curPageIndex;

};
#endif // HEAPFILE_H

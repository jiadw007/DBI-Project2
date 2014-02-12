#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>


DBFile::DBFile () {

    fType f_type = heap;
    switch(f_type){

       case heap:
        cout<< "HeapFile Mode"<< endl;
        gdbFile = new HeapFile();
        break;
       case sorted:
        cout<<"sorted file, not implemented." << endl;
        exit(-1);
        break;
       case tree:
        cout<<" B-tree file, not implemented." << endl;
        exit(-1);
        break;
       default:
        cout<< "unknown type of file."<< endl;
        exit(-1);

    }

}

int DBFile::Create (char *f_path, fType f_type, void *startup) {

    assert(heap == f_type);
    return gdbFile->Create(f_path, f_type, startup);

}

void DBFile::Load (Schema &f_schema, char *loadpath) {

    gdbFile->Load(f_schema, loadpath);

}

int DBFile::Open (char *f_path) {

    return gdbFile->Open(f_path);

}

void DBFile::MoveFirst () {

    gdbFile->MoveFirst();
}

int DBFile::Close () {

    int result = gdbFile->Close();
    delete gdbFile;
    return result;
}

void DBFile::Add (Record &rec) {

    gdbFile->Add(rec);
}

int DBFile::GetNext (Record &fetchme) {

   return gdbFile->GetNext(fetchme);

}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {

    return gdbFile->GetNext(fetchme, cnf, literal);
}

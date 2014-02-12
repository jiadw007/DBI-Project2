#ifndef SORTER_H
#define SORTER_H

using namespace std;
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Record.h"
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

#endif // SORTER_H

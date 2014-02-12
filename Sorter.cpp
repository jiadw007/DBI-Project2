#include "sorter.h"

Sorter::Sorter(OrderMaker om):om(&om){

}

bool operator()(Record& first_record, Record& second_record){

    ComparisonEngine cmp;
    return cmp.Compare(&first_record, &second_record, om) < 0;
}

bool operator()(const Record& first_record, const Record& second_record){

    ComparisonEngine cmp;
    return cmp.Compare(const_cast<Record*>(&first_record), const_cast<Record*>(&second_record), om) < 0;


}
bool operator()(Record* first_record, Record* second_record){

    ComparisonEngine cmp;
    return cmp.Compare(first_record, second_record, om) < 0;

}
Sorter::~Sorter(){

    cout << " Sorter destructor called" << endl;

}

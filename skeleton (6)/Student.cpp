#include <iostream>
#include "Student.h"

using namespace std;

// TODO: Task 1.1
Student::Student(int sid,
                 const string& name,
                 const string& major,
                 bool isLocal,
                 int ECANum,
                 int travelFastest,
                 int travelCheapest,
                 bool isFirstApplication): sid{sid},name{name},major{major},isLocal{isLocal},ECANum{ECANum},travelFastest{travelFastest},travelCheapest{travelCheapest},isFirstApplication{isFirstApplication}, status{QUEUEING}{
                    int first;
                    if(isFirstApplication)
                        first = 1;
                    else 
                        first = 0;
                    
                    if(isLocal){
                        totalHallPoints = (travelCheapest + travelFastest)/4 + ECANum * 5 + first * 5;
                    }
                    else{
                        totalHallPoints = 15 + first * 20 + ECANum * 5;
                    } 
                 }

// TODO: Task 1.2
bool Student::operator==(int sid) const {
    if(this->sid == sid)
        return true;
    else
        return false;
}

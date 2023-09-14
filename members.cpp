#include "members.h"

//Constructors
    Members::Members(){
        member_name = "";
        fullness = 5;
    }

    Members::Members(string name){
        member_name = name;
        fullness = 50;
    }

//Getters
    int Members::getMemberFullness(){
        return fullness;
    }

    string Members::getMemberName(){
        return member_name;
    }

//Setters
    void Members::setMemberName(string name){
        member_name = name;
    }

    void Members::setMemberFullness(int new_fullness){
        fullness = new_fullness;
    }

    void Members::addMemberFullness(int fullness_added){
        fullness += fullness_added;
    }

    void Members::removeMemberFullness(){
        fullness--;
    }

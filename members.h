#include <iostream>
using namespace std;

class Members{
    private:
        string member_name;
        int fullness;
    
    public:
        //Constructor
        Members();
        Members(string name);

        //Getters
        int getMemberFullness(); //Returns members fullness level
        string getMemberName(); //Returns members name

        //Setters
        void setMemberName(string name); //Sets members name
        void setMemberFullness(int new_fullness); //Sets members fullness
        void addMemberFullness(int fullness_added); //Adds fullness
        void removeMemberFullness(); //Removes members fullness
};
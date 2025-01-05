#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
using namespace std;

//single responsibility principle
//a class should have only one reason to change
//if a class has more than one responsibility, it should be refactored
//each class should have only one job
struct Journal{
    string title;
    vector<string> entries;

    Journal(const string &title) : title(title){}

    void add_entry(const string& entry){
        static int count = 1;
        entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
    }

    //This is not a good idea approach because if we need to change the persistence code then it needs to be changed everywhere in codebase
    // rather than this can be moved to a separate class or struct
    void save(const string& filename){
        ofstream ofs(filename);
        for(auto& e : entries){
            ofs << e << endl;
        }
    }
};

struct PersistenceManager{
    void save(const Journal& j , const string& filename){
        ofstream ofs(filename);
        for(auto& e : j.entries){
            ofs << e << endl;
        }
    }
};

int main(){
    Journal journal("Dear Diary");
    journal.add_entry("I ate a bug today");
    journal.add_entry("I cried today");
    PersistenceManager pm;
    pm.save(journal , "diary.txt");
}
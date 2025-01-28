#include <iostream>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <map>

using namespace std;

class Database{
public:
    virtual int get_population(const string& name) = 0;
};

class SingletonDatabase  : public Database{
    map<string , int> capitals;
    SingletonDatabase(){
        cout << "Initializing database" << endl;
        ifstream ifs("capitals.txt");

        string s , s2;

        while(getline(ifs , s)){
            getline(ifs , s2);
            int pop = boost::lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get(){
        static SingletonDatabase db;
        return db;
    }

    int get_population(const string& name) override{
        return capitals[name];
    }
};

class DummyDatabase : public Database{
    map<string , int> capitals;
public:
    DummyDatabase(){
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }
};

struct ConfigurableRecordFinder{
        Database& db;
        ConfigurableRecordFinder(Database& db) : db(db){}
        int total_population(vector<string> names){
        int result{0};
        for(auto& name : names){
            result += db.get_population(name);
        }
        return result;
    }

};

struct SingletonRecordFinder{
    int total_population(vector<string> names){
        int result{0};
        for(auto& name : names){
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};


int main(){
    string city = "Tokyo";
    cout << city << "Has Population\n" << SingletonDatabase::get().get_population(city) << endl;
    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Document{
  string id;
  string text;
  string pages;
  string filename;
};

//This is not a good approach because you are exposing too much to implement
//What if someone only wants to use print or scan or fax
//So the Interface Segregation principle states that segregating the functionality
//into smaller chunks so that person can implement desired functionalities on its own
struct IMachine{
  virtual void print(Document& doc) = 0;
  virtual void scan(Document& doc) = 0;
  virtual void fax(Document& doc) = 0;
};

//You can define three interface separately
struct IPrinter{
  virtual void print(Document& doc) = 0;
};

struct IScanner{
  virtual void scan(Document& doc) = 0;
};

struct IFax{
  virtual void scan(Document& doc) = 0;
};

//Now you can inherit them to create you Own interfaces or
//implement the specific functionalaties you want
//Example

struct Printer : IPrinter{
  void print(Document& doc){
    cout << doc.filename << endl;
    cout << doc.text << endl;
    cout << doc.pages << endl;
    cout << doc.id << endl;
  }
};

struct Scanner : IScanner{
  void scan(Document& doc){
    cout << doc.filename << endl;
    cout << doc.text << endl;
    cout << doc.pages << endl;
    cout << doc.id << endl;
  }
};

//Or You can create a Complex a interface which includes two functionalities
struct IMultiMachine : IPrinter , IScanner{};

//Now you can implement this interface
struct MultiMachine : IMultiMachine{
  IPrinter* printer;
  IScanner* scanner;
  MultiMachine(IPrinter* printer, IScanner* scanner) : printer(printer), scanner(scanner){}

  void print(Document& doc) override{
    printer->print(doc);
  }

  void scan(Document& doc) override{
    scanner->scan(doc);
  }
};

int main(){
  return 0;
 }
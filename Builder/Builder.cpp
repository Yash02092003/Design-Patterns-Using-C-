#include <sstream>
#include <memory>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct HtmlElement;
struct HtmlBuilder;

struct HtmlElement{
    string name , text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}

    HtmlElement(const string& name , const string& test) : name(name) , text(text) {}

    string str(int indent = 0) const{
        ostringstream oss;
        string i(indent_size * indent , ' ');
        oss << i << "<" << name << ">" << endl;
        if(text.size() > 0){
            oss << string(indent_size * (indent + 1) , ' ') << text << endl;
        }

        for(const auto& e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
};

//Html Builder allows you to build an object Steo by Step
struct HtmlBuilder{
    HtmlElement root;

    HtmlBuilder(string root_name){
        root.name = root_name;
    }

    HtmlBuilder& add_child(string child_name , string child_text){
        HtmlElement e(child_name , child_text);
        root.elements.emplace_back(e);
        return *this;
    }

    string str() const {
        return root.str();
    }

    static HtmlBuilder build(string root_name){
        return HtmlBuilder(root_name);
    }
};


//Whole HtmlElemnt Class 
int main(){
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";  
    cout << output << endl;

    string words[] = { "hello" , "World" };
    ostringstream oss;
    oss << "<ul>";
    for (auto w : words)
        oss << " <li>" << w << "</li>" << endl;
    oss << "</ul>";
    cout<<oss.str()<<endl;

    HtmlBuilder builder("p");
    builder.add_child("h1" , "Hello worlds");
    cout<<builder.str()<<endl;

    return 0;
}
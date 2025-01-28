#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>

using namespace std;

struct Tag {
    string name, text;
    vector<Tag> children;
    vector<pair<string, string > > attributes;

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag) {
        os << "<" << tag.name;
        for (const auto& att : tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children.empty() && tag.text.empty()) {
            os << "/>" << std::endl;
        }
        else {
            os << ">" << std::endl;

            if (!tag.text.empty())
                os << tag.text << std::endl;

            for (const auto& child : tag.children)
                os << child;

            os << "</" << tag.name << ">" << std::endl;
        }

        return os;
    }

public:
    Tag(const string& name, const string& text) : name(name), text(text) {}

    Tag(const string& name, const vector<Tag>& children) : name(name), children(children) {}
};

class P : public Tag {
public:
    P(const string& text) : Tag("p", text) {}
    P(const vector<Tag>& children) : Tag("p", children) {}
};

struct IMG : public Tag {
    explicit IMG(const string& url) : Tag("img", "") {
        attributes.emplace_back(make_pair("src", url));
    }
};

int main() {
    // Correct creation of P with IMG inside it
    vector<Tag> children;
    children.push_back(IMG("http://pokemon.com/pikachu.png"));
    P p(children);

    cout << p << endl;
    return 0;
}

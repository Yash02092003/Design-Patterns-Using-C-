#include <map>
#include <memory>
#include <iostream>
using namespace std;

enum class Importance{
    primary ,
    secondary ,
    tertiary
};

template<typename T , typename Key = std::string> class Multiton{
    public:
        static shared_ptr<T> get(const Key& key){
            if(const auto it = instances.find(key);
                it != instances.end()){
                    return it->second;
                }
            auto instance = make_shared<T>();
            instances[key] = instance;
            return instance;
        }
    
    protected:
        Multiton() = default;
        ~Multiton() = default;

    private:
        static map<Key , shared_ptr<T> > instances; 

};

class Printer{

    public:
        Printer(){
            ++Printer::totalInstancesCount;
            cout << "A total of " << Printer::totalInstancesCount << " Instances created so far \n";
        }

    private:

    static int totalInstancesCount;

};


int Printer::totalInstancesCount = 0;

int main(){

    typedef Multiton<Printer , Importance> mt;

    auto main = mt::get(Importance::primary);
    auto aux = mt::get(Importance::secondary);
    auto aux2 = mt::get(Importance::tertiary);

    return 0;
}


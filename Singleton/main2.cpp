class Printer{
    static int id;
public:
    int get_id() const { return id; }
    void set_id(int value) { id = value; }
};

int Printer::id = 0;

int main(){
    Printer p;
    int id = p.get_id();
    Printer p2;
}
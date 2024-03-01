#include <iostream>

class Gate {
public:
    bool A, B,C;
    Gate(bool aIn, bool bIn) : A(aIn), B(bIn){}
    virtual bool getOutput(){
        return C;
    }
};

class XOR : public Gate {
    bool getOutput() override{
      C = A ^ B;
      return C;
    }
};

class AND : public Gate {
    bool getOutput() override{
        C = A & B;
        return C;
    }
};

class OR : public Gate {
    bool getOutput() override{
        C = A | B;
        return C;
    }
};
class NOT : public Gate {
    bool getOutput() override{
        //Assume B is inexistent
        C = !A;
        return C;
    }
};



int main() {}

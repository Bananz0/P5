#include <iostream>

//Gates as classes
class Gate {
public:
    bool A, B,C{};
    Gate() : A(false) , B(false){};
    ~Gate()= default;
    virtual void setInputs(bool aIn, bool bIn){
        A = aIn;
        B = bIn;
    }
    virtual bool getOutput(){
        return C;
    }

};
class XOR : public Gate {
public:
    bool getOutput() override{
      C = A ^ B;
      return C;
    }
};
class AND : public Gate {
public:
    bool getOutput() override{
        C = A & B;
        return C;
    }
};
class OR : public Gate {
public:
    bool getOutput() override{
        C = A | B;
        return C;
    }
};
class NOT : public Gate {
public:
    void setInputs(bool a)  {  // Override to accept only one input
        A = a;
    }
    bool getOutput() override{
        //Assume B is nonexistent
        C = !A;
        return C;
    }
};

class halfAdder {
private:
    bool sum, carry;
public:
    bool A, B, cIn;
    halfAdder() : A(false), B(false), cIn(false) , sum(false), carry(false){};
    void setInputs(bool aIn, bool bIn , bool cInIn){
        A = aIn;
        B = bIn;
        cIn = cInIn;
    }
    void calculate(){
        //Sum
        XOR* xorG = new XOR;
        xorG->setInputs(A,B);
        sum = xorG->getOutput();
        delete xorG;
        //Carry
        AND* andG = new AND;
        andG->setInputs(A,B);
        carry = andG->getOutput();
        delete andG;
    }
    bool getSum(){
        return sum;
    }
    bool getCarry(){
        return carry;
    }

};

int main() {
    auto* halfAdd = new halfAdder();
    //halfAdder* halfAdd = new halfAdder();

    halfAdd->setInputs(false, true,true);
    halfAdd->calculate();
    bool sum = halfAdd->getSum();
    bool carry = halfAdd->getCarry();
    delete halfAdd;

    std::cout << "Sum: " << sum << " Carry: "<< carry;





}

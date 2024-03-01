#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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
class fullAdder{
private:
    bool fSum, fCarry, f_cIn;
public:
    halfAdder* halfy = new halfAdder;
    fullAdder() : fCarry(false), fSum(false), f_cIn(false){};
    void setInputs(bool fSumIn, bool fCarryIn,bool f_cInIn){
        fSum = fSumIn;
        fCarry = fCarryIn;
        f_cIn = f_cInIn;
    }

};

//Convert numer to binary
std::vector<bool>convertToBinary(int numIn){
    std::vector<bool> binArray;
    bool isNegative = false;
    if (numIn < 0) {isNegative = true;numIn = -numIn;}
    for (int i = 0; numIn != 0; i++){
        binArray.push_back(numIn%2);
        numIn /= 2;
    }
    std::cout << "Bin Array zise "<<binArray.size() << "\n";
    //Padding
    for (int i = 0; binArray.size() < 8; i++) {
        binArray.push_back(false);
    }
    //Sign Bit
    if (isNegative) binArray.push_back(true);
    std::reverse(binArray.begin(), binArray.end());
    return binArray;
}
int convertBinaryToInt(std::vector<bool> binArray) {
    int out = 0;
    for (int a = 1; a < binArray.size(); a++) {
        out += binArray[a] * pow(2,binArray.size()-1-a);
    }
    binArray[0]?out = -out:out = out;
    return out;
}
void printBinaryArray(std::vector<bool> binArray){
    std::cout << "Binary Array: ";
    for (int i = 0; i < binArray.size(); i++)
        std::cout << binArray[i];

    std::cout << "\n";
}
std::vector<bool> twosComplement(std::vector<bool> binaryArray) {
    std::vector<bool> binArrayComplement(binaryArray.size(), false);
    //One's Complement
    for (int i = binaryArray.size() - 1; i >= 0; i--) {
        binArrayComplement[i] = !binaryArray[i];
    }
    //Two's Complement
    for (int i = binArrayComplement.size() - 1; i >= 0; i--) {
        if (binArrayComplement[i] == 0) {binArrayComplement[i] = 1; break;}
        else binArrayComplement[i] = 0;
    }
    return binArrayComplement;
}



int main() {
    auto* halfAdd = new halfAdder();
    //halfAdder* halfAdd = new halfAdder();

    halfAdd->setInputs(false, true,true);
    halfAdd->calculate();
    bool sum = halfAdd->getSum();
    bool carry = halfAdd->getCarry();
    delete halfAdd;

    std::cout << "Sum: " << sum << " Carry: " << carry << "\n";

    std::vector<bool> testArray = convertToBinary(-20);
    printBinaryArray(testArray);
    printBinaryArray(twosComplement((testArray)));
    int outer = convertBinaryToInt((testArray));
    std::cout << outer ;

}

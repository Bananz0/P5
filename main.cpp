#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Creature.h"



bool overflow = false;

void printBinaryArray(const std::vector<bool>& binArray);
int convertBinaryToInt(std::vector<bool> binArray);
std::vector<bool>convertToBinary(int numIn);
std::vector<bool> twosComplement(std::vector<bool> binaryArray);

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
    bool temp_s=false;
    bool temp_c1=false;
    bool temp_c2=false;

    XOR* xorG = new XOR;
    AND* andG = new AND;
    OR* orG = new OR;
public:
    bool A, B, cIn;
    halfAdder() : A(false), B(false), cIn(false) , sum(false), carry(false){};
    ~halfAdder(){
        delete andG;
        delete xorG;
        delete orG;
    }
    void setInputs(bool aIn, bool bIn , bool cInIn){
        A = aIn;
        B = bIn;
        cIn = cInIn;
    }
    void calculate(){
        //Sum
        xorG->setInputs(A,B);
        temp_s = xorG->getOutput();

        xorG->setInputs(temp_s,cIn);
        sum = xorG->getOutput();

        //Carry
        //A*B
        andG->setInputs(A,B);
        temp_c1  = andG->getOutput();


        andG->setInputs(temp_s,cIn);
        temp_c2 = andG->getOutput();

        orG->setInputs(temp_c1,temp_c2);
        carry = orG->getOutput();
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
    std::vector<bool> binarySum {};
public:
    halfAdder* halfy = new halfAdder;
    fullAdder() : fCarry(false), fSum(false), f_cIn(false){};
    ~fullAdder(){
        delete halfy;
    }
    void setInputs(bool fSumIn, bool fCarryIn,bool f_cInIn){
        fSum = fSumIn;
        fCarry = fCarryIn;
        f_cIn = f_cInIn;
    }
    void calculateSum(std::vector<bool> binaryArrayUno,std::vector<bool> binaryArrayDos){
        size_t maxArraySize = 0;
        maxArraySize = std::max(binaryArrayUno.size(),binaryArrayDos.size());
        fCarry = f_cIn;
        for (int i = maxArraySize - 1; i >= 0 ; i--) {
        //    bool bitUno = i < binaryArrayUno.size() && binaryArrayUno[i]; // Get bit from binaryArrayUno
        //    bool bitDos = i < binaryArrayDos.size() && binaryArrayDos[i]; // Get bit from binaryArrayDos
            halfy->setInputs(binaryArrayUno[i], binaryArrayDos[i], fCarry);
            halfy->calculate();
            fCarry = halfy->getCarry();
            fSum = halfy->getSum();
            binarySum.push_back(fSum);
        }
        if (fCarry) {binarySum.push_back(fCarry); overflow = true;}
        std::reverse(binarySum.begin(),binarySum.end());
    }
    std::vector<bool> getOutput(){
        return binarySum;
    }
};

int main() {
    std::vector<bool> numeroUno, numeroDos,result;
    int numeroOne, numeroTwo;
    bool cIn_custom;
    char operatorType;
//    auto* halfAdd = new halfAdder();
//    //halfAdder* halfAdd = new halfAdder();
//
//    halfAdd->setInputs(false, true,true);
//    halfAdd->calculate();
//    bool sum = halfAdd->getSum();
//    bool carry = halfAdd->getCarry();
//    delete halfAdd;
//
//    std::cout << "Sum: " << sum << " Carry: " << carry << "\n";
//
//    numeroUno = convertToBinary(-60);
//    numeroDos = convertToBinary(03);
//    printBinaryArray(numeroUno);
//    printBinaryArray(numeroDos);
//


//    //ACTUAL LAB
//    std::cout << "Input your first number (A):";
//    std::cin >> numeroOne;
//    std::cout << "Input your first number (B):";
//    std::cin >> numeroTwo;
//    std::cout << "Select your operation (+ / -):";
//    std::cin >> operatorType;
//    std::cout << std::endl;
//
//    numeroUno = convertToBinary(numeroOne);
//    numeroDos = convertToBinary(numeroTwo);
//
//
//    std::cout <<"Corresponding value of A in binary: ";
//    printBinaryArray(numeroUno);
//    std::cout <<"Corresponding value of B in binary: ";
//    printBinaryArray(numeroDos);
//
//    std::cout << numeroOne <<  operatorType << numeroTwo << std::endl;
//    if (operatorType == '-') numeroDos = twosComplement(numeroDos);
//
//    std::cout << "cIn value is:";
//    std::cin >> cIn_custom;
//
//    auto* fully = new fullAdder;
//    fully->setInputs(false, false,cIn_custom);
//    fully->calculateSum(numeroUno, numeroDos);
//    result =  fully->getOutput();
//    printBinaryArray(result);
//
//    std::cout << "\nDecimal Equivalent (Sum) : " << convertBinaryToInt(result) << "\n";
//    std::cout << "Sum: " << "0" << " Carry: " << overflow << "\n";
//
//    delete fully;

    auto* James = new Human;
    std::cout << James->getSpecies() << std::endl;
    James->getDamage();
    delete James;


    auto* Tonal = new Balrog;
    std::cout << James->getSpecies() << std::endl;
    James->getDamage();
    delete James;



}

//Convert numero to binary
std::vector<bool>convertToBinary(int numIn){
    std::vector<bool> binArray;
    bool isNegative = false;
    if (numIn < 0) {isNegative = true;numIn = -numIn;}
    for (int i = 0; numIn != 0; i++){
        binArray.push_back(numIn%2);
        numIn /= 2;
    }
    //std::cout << "Bin Array zise "<<binArray.size() << "\n";
    //Padding
    for (int i = 0; binArray.size() < 8; i++) {
        binArray.push_back(false);
    }
    //Sign Bit
    //isNegative? binArray.push_back(true):binArray.push_back(false);
    std::reverse(binArray.begin(), binArray.end());
    if (isNegative){binArray = twosComplement(binArray);}

    return binArray;
}
std::vector<bool> twosComplement(std::vector<bool> binaryArray) {
    std::vector<bool> binArrayComplement(binaryArray.size(), false);  // Initialize with all 0s
    // One's complement operation
    for (int i = binaryArray.size() - 1; i >= 0; i--) {
        binArrayComplement[i] = !binaryArray[i];
    }
    // Add 1 to the one's complement
    bool carry = true;
    for (int i = binaryArray.size() - 1; i >= 0; i--) {
        if (binArrayComplement[i] == 0) {
            binArrayComplement[i] = carry;
            carry = false;
        } else {
            binArrayComplement[i] = !carry;
        }
    }
    return binArrayComplement;
}
int convertBinaryToInt(std::vector<bool> binArray) {
    int out = 0;
    int a;

    // Check if the number is negative
    bool isNegative = binArray[0]; // MSB indicates sign

    // If the number is negative, calculate two's complement
    if (isNegative) {
        binArray = twosComplement(binArray);
    }

    // Convert binary to decimal
    for (overflow ? a = 1 : a = 0; a < binArray.size(); a++) {
        out += binArray[a] * pow(2, binArray.size() - 1 - a);
    }

    // Apply negative sign if necessary
    if (isNegative) {
        out = -out;
    }

    return out;
}
void printBinaryArray(const std::vector<bool>& binArray) {
    for (auto &&i: binArray) {
        std::cout << i;
    }
    std::cout << std::endl;
}

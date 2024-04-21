#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Creature.h"
#include <thread>
#include <chrono>

bool overflow = false;
int bitCount = 8;
void printBinaryArray(const std::vector<bool>& binArray);
int convertBinaryToInt(std::vector<bool> binVector);
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
    srand(time(nullptr));
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


    //ACTUAL LAB
    std::cout << "Input your first number (A):";
    std::cin >> numeroOne;
    std::cout << "Input your first number (B):";
    std::cin >> numeroTwo;
    std::cout << "Select your operation (+ / -):";
    std::cin >> operatorType;
    std::cout << std::endl;

    numeroUno = convertToBinary(numeroOne);
    numeroDos = convertToBinary(numeroTwo);


    std::cout <<"Corresponding value of A in binary: ";
    printBinaryArray(numeroUno);
    std::cout <<"Corresponding value of B in binary: ";
    printBinaryArray(numeroDos);

    std::cout << numeroOne <<  operatorType << numeroTwo << std::endl;
    if (operatorType == '-') numeroDos = twosComplement(numeroDos);

    std::cout << "cIn value is:";
    std::cin >> cIn_custom;

    auto* fully = new fullAdder;
    fully->setInputs(false, false,cIn_custom);
    fully->calculateSum(numeroUno, numeroDos);
    result =  fully->getOutput();
    printBinaryArray(result);

    std::cout << "\nDecimal Equivalent (Sum) : " << convertBinaryToInt(result) << "\n";
    std::cout << "Sum: " << "0" << " Carry: " << overflow << std::endl ;

    delete fully;
    std::this_thread::sleep_for(std::chrono::seconds(3));


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Stack OVerflow




    //OPTIONAL
    int turnCount;
    int totalDamage;
    int bigBoiHealth= 90;

    auto* James = new Human;
    auto* Tonal = new Balrog;
    auto* Gandalf = new Elf;
    auto* Nigga = new Cyberdemon;

    std::cout << "\nWelcome to Magic the Gathering (southampton edition)";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "\nPress any key to continue:";
    std::cin.get();

    std::cout << "\nEnter number of truns:";
    std::cin >> turnCount;

    std::cout << "\nEnter boss health:";
    std::cin >> bigBoiHealth;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout <<"\nOh? monster appeared with " <<
            bigBoiHealth << " damage...\n" << "Will you be able to defeat it? (Intense Music starts playing)";

    std::cout << "3..";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "2..";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "1.." ;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "FIGHT!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));



    for (int turn = 1; turn < turnCount; turn++) {
        std::cout << "--------------Turn " << turn << "---------------"<< std::endl;
        totalDamage = James->getDamage() + Gandalf->getDamage() + Tonal->getDamage() + Nigga->getDamage();
        bigBoiHealth -=totalDamage;
        std::cout << "----------------Total Damage: " << totalDamage
        << "--------------\n"<< "----------------Remaining Health "<< bigBoiHealth <<
        "--------------------\n" <<"Press enter to atttack" << std::endl;
        std::cin.get();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    if (bigBoiHealth > 0){
        std::cout<< "YOU HAVE FAILED!\n\n" << "Remaining health: "
        << bigBoiHealth << "\nBetter Luck Next Time" ;
    } else if (bigBoiHealth < 0){
        std::cout<< "Congratulations! You have beaten the monster! Go get yourself a burger man!";\
    }






    delete Tonal;
    delete James;
    delete Nigga;
    delete Gandalf;



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
int convertBinaryToInt(std::vector<bool> binVector) {
    int decNum = 0;
    int n = binVector.size();
    if (binVector.size() == bitCount) {
        std::cout << binVector.size() << bitCount << std::endl;
    }
    //std::cout << "The size of the binary array is: " << n << std::endl;


    for (int j = 1; j < n; j++) {
        decNum = decNum + binVector[j] * pow(2, n - j - 1);
    }

    std::cout << "The decNum of the binary array is: " << decNum << std::endl;

    if (binVector[0] == 1 && decNum != 0) {
        decNum = decNum - pow(2, binVector.size() - 1);
    }

    std::cout << "The decimal equivalent is: " << decNum << std::endl;
    return decNum;
}
void printBinaryArray(const std::vector<bool>& binArray) {
    for (auto &&i: binArray) {
        std::cout << i;
    }
    std::cout << std::endl;
}

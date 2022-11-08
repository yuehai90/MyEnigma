#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <fstream>
#include <cctype>
#include <string>

#include "MyEnigma.h"

int main() {

    int enigmaSet1 {3};
    int enigmaSet2 {4};
    int enigmaSet3 {5};

    MyEnigma enigma1 {enigmaSet1, enigmaSet2, enigmaSet3};

    std::ifstream inputFile {};
    std::ofstream outputFile {};
    outputFile.open("enciphered.txt");
    inputFile.open("data.txt");
    if (!inputFile.is_open() || !outputFile.is_open()) std::cout << "data open faild" << std::endl;
    else {
        while (!inputFile.eof()) {
            std::string line {};
            std::string newLine {};
            std::getline(inputFile, line);
            std::transform(line.begin(), line.end(), line.begin(), toupper);
            for (const char ch:line) {
                if (isalpha(ch)) {
                    char temp {};
                    temp = enigma1.encode(ch);
                    enigma1.counterPlus();
                    newLine = newLine + temp;
                } else {
                    newLine = newLine + ch;
                }
            }
            outputFile << newLine << std::endl;
        }
    }
    inputFile.close();
    outputFile.close();
    std::cout << "========Encode Finished=================" << std::endl;

    MyEnigma enigma2 {enigmaSet1, enigmaSet2, enigmaSet3};

    std::ifstream newInputFile {};
    std::ofstream newOutputFile {};
    newInputFile.open("enciphered.txt");
    newOutputFile.open("decodeText.txt");
    if (!newInputFile.is_open() || !newOutputFile.is_open()) std::cout << "data open faild" << std::endl;
    else {
        while (!newInputFile.eof()) {
            std::string line {};
            std::string newLine {};
            std::getline(newInputFile, line);
            for (const char ch:line) {
                if (isalpha(ch)) {
                    char temp {};
                    temp = enigma2.decode(ch);
                    enigma2.counterPlus();
                    newLine = newLine + temp;
                } else {
                    newLine = newLine + ch;
                }
            }
            newOutputFile << newLine << std::endl;
        }
    }
    newInputFile.close();
    newOutputFile.close();
    std::cout << "========Decode Finished=================" << std::endl;

    return 0;
}
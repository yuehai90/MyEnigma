//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// This class refers to the simplified version of the Enigma cipher machine 
// and its principle, and can realize the encryption and decryption system 
// composed of 3 rotors and 1 reflector.
//
// Author: Yuehai Sun
// Data: 08.11.2022
// Version: 1.0
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "MyEnigma.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>

// Constructor, 3 counts which allow Initialization with 1-26
MyEnigma::MyEnigma(int CountRoter1, int CountRoter2, int CountRoter3) {
    // Set roter 1 and reference 
    for (int i {1}; i < CountRoter1; i++) {
        roter1.push_back(roter1.at(0));
        roter1.erase(roter1.begin());
        referenceRoter1.push_back(referenceRoter1.at(0));
        referenceRoter1.erase(referenceRoter1.begin());
    }

    // Set roter 2 and reference
    for (int j {1}; j < CountRoter2; j++) {
        roter2.push_back(roter2.at(0));
        roter2.erase(roter2.begin());
        referenceRoter2.push_back(referenceRoter2.at(0));
        referenceRoter2.erase(referenceRoter2.begin());
    }

    // Set roter 3 and reference
    for (int k {1}; k < CountRoter3; k++) {
         roter3.push_back(roter3.at(0));
        roter3.erase(roter3.begin());
        referenceRoter3.push_back(referenceRoter3.at(0));
        referenceRoter3.erase(referenceRoter3.begin());
    }

    // Set counter
    counter.at(0) = CountRoter1;
    counter.at(1) = CountRoter2;
    counter.at(2) = CountRoter3;
}

// Function counter plus
void MyEnigma::counterPlus() {
    // roter1 plus 1
    roter1.push_back(roter1.at(0));
    roter1.erase(roter1.begin());
    referenceRoter1.push_back(referenceRoter1.at(0));
    referenceRoter1.erase(referenceRoter1.begin());

    if (counter.at(0) + 1 > 26) {
        // counter1 reset to 1
        counter.at(0) = counter.at(0) + 1 - 26;
        // roter2 plus 1
        roter2.push_back(roter2.at(0));
        roter2.erase(roter2.begin());
        referenceRoter2.push_back(referenceRoter2.at(0));
        referenceRoter2.erase(referenceRoter2.begin());

        if (counter.at(1) + 1 > 26) {
            // counter2 reset to 1
            counter.at(1) = counter.at(1) + 1 - 26;
            // roter3 plus 1
            roter3.push_back(roter3.at(0));
            roter3.erase(roter3.begin());
            referenceRoter3.push_back(referenceRoter3.at(0));
            referenceRoter3.erase(referenceRoter3.begin());

            if (counter.at(2) + 1 > 26) {
                counter.at(2) = counter.at(2) + 1 - 26;
            } else {
                counter.at(2) += 1;
            }
        } else {
            counter.at(1) += 1;
        }
    } else {
        counter.at(0) += 1;
    }
}

// Function encode
char MyEnigma::encode(const char x) {
    // roter 1 - 2
    int pos12 = forward(x, roter1, referenceRoter1);
    char pos1_2 = (roter2.at(pos12)).first;

    // roter 2 - 3
    int pos23 = forward(pos1_2, roter2, referenceRoter2);
    char pos2_3 = (roter3.at(pos23)).first;

    // roter 3 - reflector
    int pos3r = forward(pos2_3, roter3, referenceRoter3);
    int positionReflector {};
    std::vector<char>::iterator pos = 
        std::find(referenceReflector.begin(), referenceReflector.end(), (reflector.at(pos3r)).second);
    if (pos != referenceReflector.end()) {
        positionReflector = std::distance(referenceReflector.begin(), pos);
    } else positionReflector = 100;

    // roter reflector - 3
    int pos32 = backwards(positionReflector, roter3, referenceRoter3);

    // roter 3 - 2
    int pos21 = backwards(pos32, roter2, referenceRoter2);

    // roter 2 - 1
    int posFinal = backwards(pos21, roter1, referenceRoter1);

    return referenceRoter1.at(posFinal);
}

// Function decode
char MyEnigma::decode(const char x) {
    // roter 1 - 2
    int pos12 = forward(x, roter1, referenceRoter1);
    char pos1_2 = (roter2.at(pos12)).first;

    // roter 2 - 3
    int pos23 = forward(pos1_2, roter2, referenceRoter2);
    char pos2_3 = (roter3.at(pos23)).first;

    // roter 3 - reflector
    int pos3r = forward(pos2_3, roter3, referenceRoter3);
    int positionReflector {};
    char tempReflector = referenceReflector.at(pos3r);
    std::vector<std::pair<char,char>>::iterator pos = std::find_if(reflector.begin(), reflector.end(), 
        [tempReflector](std::pair<char,char> &pairRoter) {
            return tempReflector == pairRoter.second;});
    if (pos != reflector.end()) {
        positionReflector = std::distance(reflector.begin(), pos);
    } else positionReflector = 100;
    
    // roter reflector - 3
    int pos32 = backwards(positionReflector, roter3, referenceRoter3);

    // roter 3 - 2
    int pos21 = backwards(pos32, roter2, referenceRoter2);

    //roter 2 - 1
    int posFinal = backwards(pos21, roter1, referenceRoter1);

    return referenceRoter1.at(posFinal); 
}

// Function forward
int MyEnigma::forward(const char ch, std::vector<std::pair<char,char>> &vec1, std::vector<char> &vec2) {
    std::vector<std::pair<char,char>>::iterator eleRoter =
        std::find_if(vec1.begin(), vec1.end(), [ch](std::pair<char,char> &pairRoter) {
            return ch == pairRoter.first;});
    if (eleRoter != vec1.end()) {
        std::vector<char>::iterator positionRoter = std::find(vec2.begin(), vec2.end(), (*eleRoter).second);
        if (positionRoter != vec2.end()) {
            int posRoter {};
            posRoter = std::distance(vec2.begin(), positionRoter);
            return posRoter;
        } else return 100;
    } else return 100; 
}

// Function backwards
int MyEnigma::backwards(const int pos, std::vector<std::pair<char,char>> &vec1, std::vector<char> &vec2) {
    char temp = vec2.at(pos);
    std::vector<std::pair<char,char>>::iterator positionRoter = 
        std::find_if(vec1.begin(), vec1.end(), [temp](std::pair<char,char> &pairRoter) {
            return temp == pairRoter.second;});
    if (positionRoter != vec1.end()) {
        int posRoter {};
        posRoter = std::distance(vec1.begin(), positionRoter);
        return posRoter;
    } else return 100;
}

// reset Enigma
void MyEnigma::reset() {
    // reset all roters
    roter1 = {{'A','F'},{'B','L'},{'C','U'},{'D','N'},{'E','Q'},{'F','I'},{'G','E'},{'H','J'},{'I','X'},{'J','B'},{'K','Y'},{'L','C'},{'M','G'},{'N','O'},{'O','W'},{'P','M'},{'Q','Z'},{'R','S'},{'S','R'},{'T','P'},{'U','A'},{'V','H'},{'W','V'},{'X','D'},{'Y','K'},{'Z','T'}};
    roter2 = {{'A','M'},{'B','Z'},{'C','Q'},{'D','U'},{'E','H'},{'F','V'},{'G','W'},{'H','P'},{'I','K'},{'J','X'},{'K','B'},{'L','C'},{'M','D'},{'N','F'},{'O','S'},{'P','Y'},{'Q','L'},{'R','J'},{'S','O'},{'T','N'},{'U','T'},{'V','G'},{'W','R'},{'X','A'},{'Y','E'},{'Z','I'}};
    roter3 = {{'A','D'},{'B','H'},{'C','A'},{'D','N'},{'E','T'},{'F','Z'},{'G','R'},{'H','W'},{'I','E'},{'J','K'},{'K','F'},{'L','X'},{'M','Y'},{'N','B'},{'O','M'},{'P','I'},{'Q','O'},{'R','L'},{'S','C'},{'T','Q'},{'U','U'},{'V','P'},{'W','S'},{'X','J'},{'Y','G'},{'Z','V'}};
    
    // reset all reference to roters
    referenceRoter1 = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    referenceRoter2 = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    referenceRoter3 = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    // reset counter for 3 roters, roter1 roter2 roter3
    counter = {1,1,1};
}

// display 3 roters
void MyEnigma::displayRoters() {
    std::cout << "roter1 --->>>  ";
    for (const auto &item:roter1) std::cout << item.first << ":" << item.second << " ";
    std::cout << std::endl;

    std::cout << "roter2 --->>>  ";
    for (const auto &item:roter2) std::cout << item.first << ":" << item.second << " ";
    std::cout << std::endl;

    std::cout << "roter3 --->>>  ";
    for (const auto &item:roter3) std::cout << item.first << ":" << item.second << " ";
    std::cout << std::endl;
}

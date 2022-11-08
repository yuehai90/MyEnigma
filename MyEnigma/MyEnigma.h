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

#ifndef _MYENIGMA_
#define _MYENIGMA_

#include <iostream>
#include <vector>

class MyEnigma 
{
private:
    // Initialization reflector and reference with random pair
    std::vector<std::pair<char,char>> reflector {{'A','B'},{'B','A'},{'C','D'},{'D','C'},{'E','F'},{'F','E'},{'G','H'},{'H','G'},{'I','J'},{'J','I'},{'K','L'},{'L','K'},{'M','N'},{'N','M'},{'O','P'},{'P','O'},{'Q','R'},{'R','Q'},{'S','T'},{'T','S'},{'U','V'},{'V','U'},{'W','X'},{'X','W'},{'Y','Z'},{'Z','Y'}};
    std::vector<char> referenceReflector {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

public:
    // Initialization 3 roters with random pair
    std::vector<std::pair<char,char>> roter1 {{'A','F'},{'B','L'},{'C','U'},{'D','N'},{'E','Q'},{'F','I'},{'G','E'},{'H','J'},{'I','X'},{'J','B'},{'K','Y'},{'L','C'},{'M','G'},{'N','O'},{'O','W'},{'P','M'},{'Q','Z'},{'R','S'},{'S','R'},{'T','P'},{'U','A'},{'V','H'},{'W','V'},{'X','D'},{'Y','K'},{'Z','T'}};
    std::vector<std::pair<char,char>> roter2 {{'A','M'},{'B','Z'},{'C','Q'},{'D','U'},{'E','H'},{'F','V'},{'G','W'},{'H','P'},{'I','K'},{'J','X'},{'K','B'},{'L','C'},{'M','D'},{'N','F'},{'O','S'},{'P','Y'},{'Q','L'},{'R','J'},{'S','O'},{'T','N'},{'U','T'},{'V','G'},{'W','R'},{'X','A'},{'Y','E'},{'Z','I'}};
    std::vector<std::pair<char,char>> roter3 {{'A','D'},{'B','H'},{'C','A'},{'D','N'},{'E','T'},{'F','Z'},{'G','R'},{'H','W'},{'I','E'},{'J','K'},{'K','F'},{'L','X'},{'M','Y'},{'N','B'},{'O','M'},{'P','I'},{'Q','O'},{'R','L'},{'S','C'},{'T','Q'},{'U','U'},{'V','P'},{'W','S'},{'X','J'},{'Y','G'},{'Z','V'}}; 
    // Initialization 3 reference to roters
    std::vector<char> referenceRoter1 {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    std::vector<char> referenceRoter2 {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    std::vector<char> referenceRoter3 {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    // Initialization counter for 3 roters, roter1 roter2 roter3
    std::vector<int> counter {1,1,1};

    // Constructor, 3 counts which allow Initialization with 1-26
    MyEnigma(int CountRoter1, int CountRoter2, int CountRoter3);

    // Function counter plus
    void counterPlus();

    // Function encode and decode
    char encode(const char x);
    char decode(const char x);

    // Function forward and backwards in encode() and decode()
    int forward(const char ch, std::vector<std::pair<char,char>> &vec1, std::vector<char> &vec2);
    int backwards(const int pos, std::vector<std::pair<char,char>> &vec1, std::vector<char> &vec2);

    // reset Enigma
    void reset();

    // display 3 roters
    void displayRoters();
};

#endif
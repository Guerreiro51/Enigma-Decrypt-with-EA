#ifndef PLUGBOARD_H
#define PLUGBOARD_H

using namespace std;
#include <unordered_map>
#include <iostream>
#include <vector>

class PlugBoard{

    private:
    unordered_map<int,int> connections;
    
    public:

    PlugBoard(vector<string> plugconnecetions);
    void AddConnection(int input, int output);
    int ReturnLetter(int input);
       
};
#endif
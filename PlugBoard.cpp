#include "PlugBoard.h"

PlugBoard::PlugBoard(vector<string> plugconnecetions)
{
    int i;
    for(i=0;i<plugconnecetions.size();i++)
    this->AddConnection(((int)(plugconnecetions[i][0]))-65,((int)(plugconnecetions[i][1]))-65);
}

void PlugBoard::AddConnection(int input, int output)
{
    //Caso ja tenha alguma letra conectada apenas retorna
    if(this->connections.count(input) || this->connections.count(output))
    {
        cout << "Connection " << (char)(input+65) <<  (char)(output+65) << " not established" << endl;
        cout << "At least one of the keys is already connected" << endl;
        return;
    }    

    this->connections[input] = output;
    this->connections[output] = input;
}

int PlugBoard::ReturnLetter(int input)
{
    if(this->connections.count(input))
        return this->connections[input];
    else
        return input;
}


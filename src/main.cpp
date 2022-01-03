#include <fstream>
#include <iostream>
#include <random>

#include "Population.h"

int main() {
    Enigma bob;
    std::cout << bob << '\n';

    std::string input = "I propose to consider the question, ‘Can machines think?’ This should begin with definitions of the meaning of the terms ‘machine’ and ‘think’. The definitions might be framed so as to reflect so far as possible the normal use of the words, but this attitude is dangerous. If the meaning of the words ‘machine’ and ‘think’ are to be found by examining how they are commonly used it is difficult to escape the conclusion that the meaning and the answer to the question, ‘Can machines think?’ is to be sought in a statistical survey such as a Gallup poll. But this is absurd. Instead of attempting such a definition I shall replace the question by another, which is closely related to it and is expressed in relatively unambiguous words.";
    std::string cipher = bob.Encipher(input);

    std::cout << "PlainText: " << input << "\n\n";
    std::cout << "Cipher: " << cipher << "\n\n";

    Population pop(cipher);
    for (size_t i = 0; i < NUMBER_OF_ITERATIONS; i++)
        if (pop.NextGeneration())
            break;
    pop.PlotDataGnuplot();

    if (OUTPUT_DATA_FILES) {
        std::ofstream maxFit(MAXFIT_PATH), avgFit(AVGFIT_PATH), mutState(MUTSTATE_PATH);
        pop.OutputData(maxFit, avgFit, mutState);
        pop.DumpData(maxFit, avgFit, mutState);
    }

    std::string output = pop.Citizens()[0].Gene().Decipher(cipher);
    std::cout << "Decrypted: " << output << "\n\n";
    std::cout << pop.Citizens()[0].Gene() << '\n';
}

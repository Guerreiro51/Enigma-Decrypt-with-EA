# Enigma-Decrypt-with-EA

## Project members
Alessandro de Freitas Guerreiro - 11233891

Bruno Alvarenga Colturato - 11200251

Eduardo Cavalari Valença - 11234381

## Presentation link
You can access a short video made by us explaining the project [here](https://drive.google.com/file/d/1njUnaXKbUvw8z0Yc7uBOcd2nimkpdFGH/view?usp=sharing).

## Description
Our project aims to break the Enigma Machine using Evolutionary Algorithm (EA).

The enigma machine was a cipher device developed and used in the 20th century to protect commercial, diplomatic, and military communication. It was employed extensively by Nazi Germany during World War II, in all branches of the German military. The Enigma machine was considered so secure that it was used to encipher the most top-secret messages. [[1]](https://en.wikipedia.org/wiki/Enigma_machine). 

The enigma was an electrical machine basically composed of three main parts: rotors, reflector and plugboard. Each of these parts was important in making the enigma a really hard encryption device to crack. Despite these difficulties, Alan Turing, considered the 'father' of computer science, and his team managed to break the enigma, making it possible to intercept all the messages exchanged between the Nazis and know what their next moves would be. This, of course, shortened World War II and helped the Allies win the war.

For our project we reacreate the enigma machine in C++. Our code was based on the code of Make Poud, who reacreated the machine in Java. His repository can be found [here](https://github.com/mikepound/enigma).

If you want to know in more details how the enigma works you can watch [this video](https://youtu.be/G2_Q9FoD-oQ).

## Fitness function

In order for our EA to break the enigma, we decided to use as a fitness function the technique called [Index of Coincidence](https://en.wikipedia.org/wiki/Index_of_coincidence) or IOC, for short. This technique consists of counting the number of times that identical letters appear in the same position in a text and its formula is given by:

![index of coincidence](https://github.com/Guerreiro51/Enigma-Decrypt-with-EA/blob/main/images/ioc.png)

Where N is the length of the text and n_1 through n_26 are the frequencies (as integers) of the 26 letters of the alphabet.

Each language has an expect value for the IOC. In this project we considered texts in English, whose expected value is 1.73. It is important to mention that the index of coincidence is a good technique for analyzing long texts and may fail with short texts.

We defined our fitness function as the difference between the IOC calculated by one of our enigmas with random rotors and reflector and the expected IOC for the English language. Note that in this way the best individual is the one with the closest fitness value to zero, so we look for global minima instead of the traditional global maxima of a regular evolutionary algorithm.

## Results

In this project we used: crossover, mutation, adaptative mutation, tournament selection, random predation and genocide. The following images represent an example of a successfull execution of the code.

![fitness](https://github.com/Guerreiro51/Enigma-Decrypt-with-EA/blob/main/images/fitness.png)
![mutation state](https://github.com/Guerreiro51/Enigma-Decrypt-with-EA/blob/main/images/mutState.png)

## How to build and run

    mkdir build && cd build
    cmake .. && make
    ./Enigma

## Dependencies:

You need to have python3 with numpy and matplotlib libraries installed. On debian based systems:

    sudo apt update
    sudo apt install python3 python3-pip
    pip install matplotlib numpy


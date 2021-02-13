
#include <iostream>
#include <fstream>
#include <cstdint>

const int cellSize = 8;
const int zeroByte = 18;
const int width = 64;
const int height = 96;
const int numCharacters = 96;

bool getNum(char* memblock, int x, int y) {
    return memblock[zeroByte + y * 64 + x] >= 0;
}

uint64_t getVal(char* memblock, int x, int y) {
    uint64_t val = 0;

    for (int i = 0; i < 64; i++) 
        val |= ((uint64_t)getNum(memblock, 7 - i % 8 + x * 8, 7 - i / 8 + y * 8) << i);

    return val;
}

void drawChar(char* memblock, int x, int y) {

    for (int j = cellSize * y; j < (cellSize * y + cellSize); j++) {
        for (int i = cellSize * x; i < (cellSize * x + cellSize); i++) {
            std::cout << (getNum(memblock, i, j) ? "#": " ");
        }
        std::cout << std::endl;
    }
}

void drawChar(uint64_t character) {
    uint8_t chr[8];

    for (int i = 0; i < cellSize; i++) {
        chr[i] = (character & (((uint64_t)0xFF) << i * cellSize)) >> (i * cellSize);
    }

    for (int i = cellSize - 1; i >= 0; i--) {
        for (int j = cellSize - 1; j >= 0; j--) {
            std::cout << (((chr[i] & (0x01 << j)) >> j) ? "#" : " ");
        }
        std::cout << std::endl;
    }
}

int main()
{


    uint64_t characters [numCharacters];


    std::streampos size;
    char* memblock;

    std::ifstream file("font.tga", std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open())
    {

        size = file.tellg();
        memblock = new char[size];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);
        file.close();

        /*
        * here is where you could get the image size from
        width = (memblock[13] << 8) | memblock[12];
        height = (memblock[15] << 8) | memblock[14];
        std::cout << std::endl << width << " x " << height <<std::endl;
        */

        //image starts at byte 18

        int index = 0;

        for (int j = 0; j < 12; j++) {
            for (int i = 0; i < 8; i++) {

                characters[index] = getVal(memblock, i, j);
                drawChar(characters[index]);
                std::cout << std::endl << (uint64_t)characters[index];

                index++;
            }
        }


        delete[] memblock;
    }
    else std::cout << "Unable to open file";

    

    std::ofstream characterFile;
    characterFile.open("characters.txt");
    for (int i = 0; i < 96; i++) {
        //std::cout << characters[i] << std::endl;
        characterFile << characters[i];
        if (i < 95) characterFile << std::endl;
    }
    characterFile.close();
    
}
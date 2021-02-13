
#include <iostream>
#include <fstream>
#include <cstdint>

bool getNum(char* memblock, int x, int y) {
    return memblock[18 + y * 64 + x] >= 0;
}

uint64_t getVal(char* memblock, int x, int y) {
    uint64_t val = 0;

    for (int i = 0; i < 64; i++) 
        val |= ((uint64_t)getNum(memblock, 7 - i % 8 + x * 8, 7 - i / 8 + y * 8) << i);

    return val;
}

void drawChar(char* memblock, int x, int y) {

    for (int j = 8*y; j < (8*y + 8); j++) {
        for (int i = 8*x; i < (8*x +8); i++) {
            std::cout << (getNum(memblock, i, j) ? "#": " ");
        }
        std::cout << std::endl;
    }
}

void drawChar(uint64_t character) {
    uint8_t chr[8];

    for (int i = 0; i < 8; i++) {
        uint64_t mask = (((uint64_t)0xFF) << i * 8);
        chr[i] = (character & mask) >> (i * 8);
    }

    for (int i = 7; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            uint8_t mask = (0x01 << j);
            std::cout << (((chr[i] & mask) >> j) ? "#" : " ");
        }
        std::cout << std::endl;
    }
}

int main()
{
    const int cellSize = 8;
    const int zeroByte = 18;
    const int width = 64;
    const int height = 96;

    uint64_t characters [96];


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
        //std::cout << "the entire file content is in memory\n";



        /*
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
        std::cout << characters[i] << std::endl;
        characterFile << characters[i];
        if (i < 95) characterFile << std::endl;
    }
    characterFile.close();
    
}
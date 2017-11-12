#include "symbol_matrix_interface.hpp"
#include <iostream>
#include <cassert>
#include <string.h>

namespace smi
{
    struct symbolMatrixInterface
    {
        std::size_t width, height;
        char* p;

    };

    symbolMatrix init(const char* string){
        symbolMatrix a = new symbolMatrixInterface;
        a->p = new char[strlen(string)];
        a->width = 0;
        a->height = 0;
        std::size_t i = 0;
        std::size_t j = 0;
        while (string[i] != '\0') {
            if(string[i] == '\n') {
                if(a->width == 0)
                    a->width = j;
                else
                    assert(j - a->width * a->height == a->width);
                ++ a->height;
            } else {
                a->p[j] = string[i];
                ++j;
            }
            ++i;
        }
        return a;
    }

    std::size_t getWidth(constSymbolMatrix a) {
        return a->width;
    }

    std::size_t getHeight(constSymbolMatrix a) {
        return a->height;
    }

    void writeSymbol(symbolMatrix a, char symbol, std::size_t x, std::size_t y) {
        assert(x <= a->width && y <= a->height);
        a->p[y + a->width * x] = symbol;
    }

    char readSymbol(constSymbolMatrix a, std::size_t x, std::size_t y) {
        assert(x <= a->width && y <= a->height);
        return a->p[y + a->width * x];
    }

    void insertSpace(symbolMatrix a, char side, std::size_t howMuch, char symbol) {
        assert(a->width != 0 && a->height != 0);
        assert(side == 'W' || side == 'E' || side == 'S' || side == 'N');
        if(!howMuch)
            return;
        std::size_t newHeight,newWidth;
        if(side == 'W' || side == 'E') {
            newHeight = a->height;
            newWidth = a->width + howMuch;
        }
        else {
            newHeight = a->height + howMuch;
            newWidth = a->width;
        }

        char* pNew = new char[newHeight * newWidth];

        switch (side) {

        case 'N':
            memset(pNew, symbol, howMuch * a->width);
            memcpy(pNew + howMuch * a->width, a->p, a->width * a->height);
            break;

        case 'S':
            memcpy(pNew, a->p, a->width * a->height);
            memset(pNew + a->width * a->height, symbol, howMuch * a->width);
            break;

        case 'W':                       
            for(std::size_t i = 0; i < a->height; ++i)
                for(std::size_t j = 0; j < howMuch; ++j)
                    pNew[j + newWidth * i] = symbol;

            for(std::size_t i = 0; i < a->height; ++i)
                for(std::size_t j = howMuch; j < newWidth; ++j)
                    pNew[j + newWidth * i] = (a->p)[j-howMuch + a->width * i];            
            break;

        case 'E':
            for(std::size_t i = 0; i < a->height; ++i) {
                for(std::size_t j = 0; j < a->width; ++j)
                    pNew[j + newWidth * i] = (a->p)[j + a->width * i];
            }
            for(std::size_t i = 0; i < a->height; ++i)
                for(std::size_t j = a->width; j < newWidth; ++j)
                    pNew[j + newWidth * i] = symbol;
            break;

        default:
            break;
        }

        delete[] a->p;
        a->p = pNew;
        a->height = newHeight;
        a->width = newWidth;


    }


    void printSymbolMatrix(constSymbolMatrix a) {
        for(std::size_t i = 0; i < a->height; ++i) {
            for(std::size_t j = 0; j < a->width; ++j)
                std::cout << a->p[j + a->width * i];
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void destroy(symbolMatrix a) {
        delete[] a->p;
        delete a;
    }

    bool compareSymbolMatrix(constSymbolMatrix a, constSymbolMatrix b) {
        if(a->width != b->width || a->height != b->height)
            return false;
        return (memcmp(a,b,a->height * a->width) == 0);
    }

}

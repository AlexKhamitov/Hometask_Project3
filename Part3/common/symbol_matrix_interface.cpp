#include "symbol_matrix_interface.hpp"
#include <iostream>
#include <cassert>

namespace smi
{
    struct symbolMatrixInterface
    {
        std::size_t width, height;
        char* p;

    };

    symbolMatrix init(const char* string){
        symbolMatrix matrix = new symbolMatrixInterface;
        matrix->p = new char[strlen(string)];
        matrix->width = 0;
        matrix->height = 0;
        std::size_t i = 0;
        std::size_t j = 0;
        while (string[i] != '\0') {
            if(string[i] == '\n') {
                if(matrix->width == 0)
                    matrix->width = j;
                else
                    assert(j - matrix->width * matrix->height == matrix->width);
                ++ matrix->height;
            } else {
                matrix->p[j] = string[i];
                ++j;
            }
            ++i;
        }
        return matrix;
    }

    std::size_t getWidth(constSymbolMatrix matrix) {
        return matrix->width;
    }

    std::size_t getHeight(constSymbolMatrix matrix) {
        return matrix->height;
    }

    void writeSymbol(symbolMatrix matrix, char symbol, std::size_t x, std::size_t y) {
        assert(x <= matrix->width && y <= matrix->height);
        matrix->p[x + matrix->width * y] = symbol;
    }

    char readSymbol(constSymbolMatrix matrix, std::size_t x, std::size_t y) {
        assert(x <= matrix->width && y <= matrix->height);
        return matrix->p[x + matrix->width * y];
    }

    void insertSpace(symbolMatrix matrix, char direction, std::size_t n, char symbol) {
        assert(matrix->width != 0 && matrix->height != 0);
        assert(direction == 'W' || direction == 'E' || direction == 'S' || direction == 'N');
        if(!n)
            return;
        std::size_t newHeight,newWidth;
        if(direction == 'W' || direction == 'E') {
            newHeight = matrix->height;
            newWidth = matrix->width + n;
        }
        else {
            newHeight = matrix->height + n;
            newWidth = matrix->width;
        }

        char* pNew = new char[newHeight * newWidth];

        switch (direction) {

        case 'N':
            std::memset(pNew, symbol, n * matrix->width);
            std::memcpy(pNew + n * matrix->width, matrix->p, matrix->width * matrix->height);
            break;

        case 'S':
            std::memcpy(pNew, matrix->p, matrix->width * matrix->height);
            std::memset(pNew + matrix->width * matrix->height, symbol, n * matrix->width);
            break;

        case 'W':                       
            for(std::size_t i = 0; i < matrix->height; ++i) {
                std::memset(pNew + i*(matrix->width + n), symbol,  n);
                std::memcpy(pNew + i*(matrix->width + n) + n, matrix->p + i*matrix->width, matrix->width);
            }
            break;

        case 'E':
            for(std::size_t i = 0; i < matrix->height; ++i) {
                std::memcpy(pNew + i*(matrix->width + n), matrix->p + i*matrix->width, matrix->width);
                std::memset(pNew + i*(matrix->width + n) + matrix->width, symbol,  n);
            }
            break;
        }

        delete[] matrix->p;
        matrix->p = pNew;
        matrix->height = newHeight;
        matrix->width = newWidth;


    }


    void printSymbolMatrix(constSymbolMatrix matrix) {
        for(std::size_t i = 0; i < matrix->height; ++i) {
            for(std::size_t j = 0; j < matrix->width; ++j)
                std::cout << matrix->p[j + matrix->width * i];
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void destroy(symbolMatrix matrix) {
        delete[] matrix->p;
        delete matrix;
    }

    bool compareSymbolMatrix(constSymbolMatrix matrix1, constSymbolMatrix matrix2) {
        if(matrix1->width != matrix2->width || matrix1->height != matrix2->height)
            return false;
        return std::memcmp(matrix1,matrix2,matrix1->height * matrix1->width) == 0;
    }

}

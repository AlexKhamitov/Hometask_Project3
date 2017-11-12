#include "symbol_matrix_interface.hpp"
#include <iostream>
#include <cassert>

namespace smi
{
    SymbolMatrix::SymbolMatrix(const char *string)
        : width(0),
          height(0),
          p(nullptr)
    {
        p = new char[std::strlen(string)];
        size_t i = 0;
        size_t j = 0;
        while (string[i] != '\0')
        {
            if(string[i] == '\n')
            {
                if(width == 0)
                {
                    width = j;
                }
                else if(j - width * height == width)
                {
                    delete p[];
                    p = nullptr;
                }
                ++height;
            }
            else
            {
                p[j] = string[i];
                ++j;
            }
            ++i;
        }
    }

    SymbolMatrix::SymbolMatrix(const SymbolMatrix& matrix)
        : width(0),
          height(0),
          p(nullptr)
    {
        copy(matrix);
    }

    SymbolMatrix::SymbolMatrix(SymbolMatrix&& matrix)
        : width(matrix.width),
          height(matrix.height),
          p(matrix.p)
    {
        matrix.height = 0;
        matrix.width = 0;
        matrix.p = nullptr;
    }

    explicit operator bool() const
    {
        return p != nullptr;
    }

    SymbolMatrix& SymbolMatrix::operator = (const SymbolMatrix& matrix)
    {
        if(this != &matrix)
            copy(matrix);
        return *this;
    }

    SymbolMatrix& SymbolMatrix::operator = (SymbolMatrix&& matrix)
    {
        if(this != &matrix)
        {
            width = matrix.width;
            height = matrix.height;
            delete[] p;
            p = matrix.p;
        }
        return *this;
    }

    char SymbolMatrix::operator() (size_t x,size_t y) const
    {
        assert(x <= width && y <= height);
        return p[x + width*y];
    }

    char& SymbolMatrix::operator()(size_t x,size_t y)
    {
        assert(x <= width && y <= height);
        char& element = p[x + width*y];
        return element;
    }

    bool SymbolMatrix::operator == (const SymbolMatrix& right) const
    {
        if(width != right.width || height != right.height)
            return false;
        return std::memcmp(this, &right, height * width) == 0;
    }

    bool SymbolMatrix::operator !=(const SymbolMatrix& right) const
    {
        return !operator ==(right);
    }

    SymbolMatrix::~SymbolMatrix()
    {
        delete[] p;
    }

    std::ostream& operator << (std::ostream& os, const SymbolMatrix& matrix)
    {
        for(std::size_t i = 0; i < matrix.getHeight(); ++i)
        {
            for(std::size_t j = 0; j < matrix.getWidth(); ++j)
                os << matrix(j, i);
            os << '\n';
        }
        os << '\n';
        return os;
    }


    void SymbolMatrix::copy(const SymbolMatrix& matrix)
    {
        width = matrix.width;
        height = matrix.height;
        char* pNew = new char[width*height];
        std::memcpy(pNew, matrix.p, width*height);
        delete[] p;
        p = pNew;
    }

    inline size_t SymbolMatrix::getWidth() const
    {
        return width;
    }

    inline size_t SymbolMatrix::getHeight() const
    {
        return height;
    }

    void SymbolMatrix::insertSpace(char direction, size_t n, char symbol)
    {
        assert(width != 0 && height != 0);
        assert(direction == 'W' || direction == 'E' || direction == 'S' || direction == 'N');

        if(!n)
            return;
        std::size_t newHeight,newWidth;
        if(direction == 'W' || direction == 'E')
        {
            newHeight = height;
            newWidth = width + n;
        }
        else
        {
            newHeight = height + n;
            newWidth = width;
        }

        char* pNew = new char[newHeight * newWidth];

        switch (direction)
        {
        case 'N':
            std::memset(pNew, symbol, n * width);
            std::memcpy(pNew + n * width, p, width * height);
            break;

        case 'S':
            std::memcpy(pNew, p, width * height);
            std::memset(pNew + width * height, symbol, n * width);
            break;

        case 'W':
            for(std::size_t i = 0; i < height; ++i)
            {
                std::memset(pNew + i*(width + n), symbol,  n);
                std::memcpy(pNew + i*(width + n) + n, p + i*width, width);
            }
            break;

        case 'E':
            for(std::size_t i = 0; i < height; ++i)
            {
                std::memcpy(pNew + i*(width + n), p + i*width, width);
                std::memset(pNew + i*(width + n) + width, symbol,  n);
            }
            break;
        }

        delete[] p;
        p = pNew;
        height = newHeight;
        width = newWidth;
    }
}

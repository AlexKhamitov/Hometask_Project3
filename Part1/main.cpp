#include <iostream>
#include "symbol_matrix_interface.hpp"
#include <cassert>

int main()
{
    {
        const char* initialString = "123\n456\n789\n\0";
        const char* sampleString = "123456789";
        smi::symbolMatrix a = smi::init(initialString);
        assert(smi::getWidth(a) == 3 && smi::getHeight(a) == 3);
        for(int i = 0; i < 9; ++i) {
            assert(smi::readSymbol(a,i / smi::getHeight(a),i % smi::getHeight(a)) == sampleString[i]);
        }
    }

    {
        const char* initialString = "\0";
        smi::symbolMatrix a = smi::init(initialString);
        assert(smi::getWidth(a) == 0 && smi::getHeight(a) == 0);
        smi::destroy(a);
    }

    {
        const char* initialString = "7\n\0";
        const char* sampleInitialString = "7777\n7777\n\0";
        smi::symbolMatrix a = smi::init(initialString);
        smi::symbolMatrix b = smi::init(sampleInitialString);
        smi::insertSpace(a, 'N', 1, '7');
        smi::insertSpace(a,'W', 3, '7');
        assert(smi::compareSymbolMatrix(a, b));
        smi::destroy(a);
    }

    {
        const char* initialString = "3\n\0";
        const char* sampleInitialString = "3333\n3333\n\0";
        smi::symbolMatrix a = smi::init(initialString);
        smi::symbolMatrix b = smi::init(sampleInitialString);
        smi::insertSpace(a, 'S', 1, '3');
        smi::insertSpace(a,'E', 3, '3');
        assert(smi::compareSymbolMatrix(a,b));
        smi::destroy(a);
    }

    //main
    /**
    const char* initialString = "0\n\0";
    smi::symbolMatrix matrix;
    smi::init(&matrix, initialString);
    **/


}

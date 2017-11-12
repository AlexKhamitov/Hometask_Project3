#include <iostream>
#include "../common/symbol_matrix_interface.hpp"
#include <cassert>

int main()
{
    using namespace smi;

    {
        const char* initialString = "123\n456\n789\n\0";
        const char* sampleString = "123456789";
        SymbolMatrix a(initialString);
        assert(a.getWidth() == 3 && a.getHeight() == 3);
        for(int i = 0; i < 9; ++i) {
            assert(a(i % a.getHeight(),i / a.getHeight()) == sampleString[i]);
        }
    }

    {
        const char* initialString = "\0";
        SymbolMatrix a(initialString);
        assert(a.getWidth() == 0 && a.getHeight() == 0);
    }

    {
        const char* initialString = "7\n\0";
        const char* sampleInitialString = "7777\n7777\n\0";
        SymbolMatrix a(initialString);
        SymbolMatrix b(sampleInitialString);
        a.insertSpace('N', 1, '7');
        a.insertSpace('W', 3, '7');
        assert(a == b);
    }

    {
        const char* initialString = "3\n\0";
        const char* sampleInitialString = "3333\n3333\n\0";
        SymbolMatrix a(initialString);
        SymbolMatrix b(sampleInitialString);
        a.insertSpace('S', 1, '3');
        a.insertSpace('E', 3, '3');
        assert(a == b);
    }

    {
        const char* initialString = " ^ \n ^ \n 0 \n\0";
        SymbolMatrix a(initialString);
        SymbolMatrix b(a);
        assert(a == b);
    }

    {
        const char* initialString = " ^ \n ^ \n 0 \n\0";
        SymbolMatrix a(initialString);
        SymbolMatrix b(initialString);
        SymbolMatrix c(static_cast<SymbolMatrix &&>(a));
        assert(c == b);
    }

    {
        const char* initialString = " ^ \n ^ \n 0 \n\0";
        SymbolMatrix a(initialString);
        SymbolMatrix b = a;
        assert(a == b);
    }

    {
        const char* initialString = " ^ \n ^ \n 0 \n\0";
        SymbolMatrix a(initialString);
        SymbolMatrix b(initialString);
        SymbolMatrix c = static_cast<SymbolMatrix &&>(a);
        assert(c == b);
    }

}

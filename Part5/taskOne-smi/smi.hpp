#ifndef SYMBOL_MATRIX_INTERFACE
#define SYMBOL_MATRIX_INTERFACE

#include <cstddef>
#include <ostream>

namespace smi
{

    using std::size_t;

    class SymbolMatrix
    {
        size_t width, height;
        char* p;

    public:

        SymbolMatrix();
        SymbolMatrix(const char* string);

        SymbolMatrix(const SymbolMatrix& matrix);
        SymbolMatrix(SymbolMatrix&& matrix);

        explicit operator bool() const;

        SymbolMatrix& operator = (const SymbolMatrix& matrix);
        SymbolMatrix& operator = (SymbolMatrix&& matrix);

        char operator () (size_t x, size_t y) const;
        char& operator () (size_t x, size_t y);

        bool operator == (const SymbolMatrix& right) const;
        bool operator != (const SymbolMatrix& right) const;

        ~SymbolMatrix();

        friend std::ostream& operator << (std::ostream& os, const SymbolMatrix& matrix);

        size_t getWidth() const;
        size_t getHeight() const;

        void insertSpace(char direction, size_t n, char symbol);

    private:

        void copy(const SymbolMatrix& matrix);

    };
}

#endif // SYMBOL_MATRIX_INTERFACE

#include <iostream>
#include <cassert>
#include "../common/symbol_matrix_interface.hpp"

int main()
{
    const char* string = "0\n\0";
    smi::symbolMatrix matrix = smi::init(string);
    std::size_t x = 0;
    std::size_t y = 0;
    char direction;
    std::size_t n;

    while (std::cin >> direction) {
        if(direction == '!')
            smi::printSymbolMatrix(matrix);
        else {
            if(!(std::cin >> n))
                break;
            else {
                assert(direction == 'W' || direction == 'E' || direction == 'S' || direction == 'N');
                switch (direction) {
                case 'N':
                    if(n > y) {
                        smi::insertSpace(matrix, direction, n - y, ' ');
                        y = n;
                    }
                    for(std::size_t i = 1; i <= n; ++i)
                        smi::writeSymbol(matrix, '^', x, y - i);
                    y -= n;
                    break;

                case 'S':
                    if(y + n >= smi::getHeight(matrix))
                        smi::insertSpace(matrix, direction,n + y + 1 - smi::getHeight(matrix), ' ');
                    for(std::size_t i = 1; i <= n; ++i)
                        smi::writeSymbol(matrix, 'v', x, y + i);
                    y += n;
                    break;

                case 'W':
                    if(n > x) {
                        smi::insertSpace(matrix, direction, n - x, ' ');
                        x = n;
                    }
                    for(std::size_t i = 1; i <= n; ++i)
                        smi::writeSymbol(matrix, '<', x - i, y);
                    x -= n;
                    break;

                case 'E':
                    if(x + n >= smi::getWidth(matrix))
                        smi::insertSpace(matrix, direction,n + x + 1 - smi::getWidth(matrix), ' ');
                    for(std::size_t i = 1; i <= n; ++i)
                        smi::writeSymbol(matrix, '>', x + i, y);
                    x += n;
                    break;
                }

            }
        }
    }
    smi::destroy(matrix);
}

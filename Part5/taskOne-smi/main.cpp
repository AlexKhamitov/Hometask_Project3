#include <iostream>
#include <cassert>
#include "smi.hpp"

int main()
{
    using std::size_t;
    using namespace smi;

    const char* string = "0\n\0";
    SymbolMatrix matrix(string);
    size_t x = 0;
    size_t y = 0;
    char direction;
    size_t n;

    while (std::cin >> direction) {
        if(direction == '!')
            std::cout << matrix;
        else {
            if(!(std::cin >> n))
                break;
            else {
                assert(direction == 'W' || direction == 'E' || direction == 'S' || direction == 'N');
                switch (direction) {
                case 'N':
                    if(n > y) {
                        matrix.insertSpace(direction, n - y, ' ');
                        y = n;
                    }
                    for(std::size_t i = 1; i <= n; ++i)
                        matrix(x, y - i) = '^';
                    y -= n;
                    break;

                case 'S':
                    if(y + n >= matrix.getHeight())
                        matrix.insertSpace(direction,n + y + 1 - matrix.getHeight(), ' ');
                    for(std::size_t i = 1; i <= n; ++i)
                        matrix(x, y + i) = 'v';
                    y += n;
                    break;

                case 'W':
                    if(n > x) {
                        matrix.insertSpace(direction, n - x, ' ');
                        x = n;
                    }
                    for(std::size_t i = 1; i <= n; ++i)
                        matrix(x - i, y) = '<';
                    x -= n;
                    break;

                case 'E':
                    if(x + n >= matrix.getWidth())
                        matrix.insertSpace(direction,n + x + 1 - matrix.getWidth(), ' ');
                    for(std::size_t i = 1; i <= n; ++i)
                        matrix(x + i, y) = '>';
                    x += n;
                    break;
                }

            }
        }
    }
}

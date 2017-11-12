// Khamitov Alexander Project3 Task1 Part1
#ifndef SYMBOL_MATRIX_INTERFACE
#define SYMBOL_MATRIX_INTERFACE

#include <cstddef>
namespace smi
{
    using symbolMatrix = struct symbolMatrixInterface*;
    using constSymbolMatrix = const symbolMatrix;

    // Задание начального состояния
    symbolMatrix init(const char* string);

    // Возвращение ширины матрицы
    std::size_t getWidth(constSymbolMatrix a);

    // Возвращение высоты матрицы
    std::size_t getHeight(constSymbolMatrix a);

    // Запись данного символа по указанным координатам
    void writeSymbol(symbolMatrix a, char symbol, std::size_t x, std::size_t y);

    // Чтение символа по указанным координатам
    char readSymbol(constSymbolMatrix a, std::size_t x, std::size_t y);

    // Раширение матрицы на указанное число строк
    // или столбцов в указанном направлении
    // с заполнением указанным символом
    void insertSpace(symbolMatrix a,char side, std::size_t howMuch, char symbol);

    // Вывод матрицы на экран
    void printSymbolMatrix(constSymbolMatrix a);

    // Освобождение динамической памяти
    void destroy(symbolMatrix a);

    //Сравнение двух матриц на идентичность
    bool compareSymbolMatrix(constSymbolMatrix a, constSymbolMatrix b);

}

#endif // SYMBOL_MATRIX_INTERFACE

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
    std::size_t getWidth(constSymbolMatrix matrix);

    // Возвращение высоты матрицы
    std::size_t getHeight(constSymbolMatrix matrix);

    // Запись данного символа по указанным координатам
    void writeSymbol(symbolMatrix matrix, char symbol, std::size_t x, std::size_t y);

    // Чтение символа по указанным координатам
    char readSymbol(constSymbolMatrix matrix, std::size_t x, std::size_t y);

    // Раширение матрицы на указанное число строк
    // или столбцов в указанном направлении
    // с заполнением указанным символом
    void insertSpace(symbolMatrix matrix,char direction, std::size_t n, char symbol);

    // Вывод матрицы на экран
    void printSymbolMatrix(constSymbolMatrix matrix);

    // Освобождение динамической памяти
    void destroy(symbolMatrix matrix);

    //Сравнение двух матриц на идентичность
    bool compareSymbolMatrix(constSymbolMatrix matrix1, constSymbolMatrix matrix2);

}

#endif // SYMBOL_MATRIX_INTERFACE

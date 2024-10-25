#pragma once
#include <vector>

class Grid {
public:
    // Construtor da classe Grid, que inicializa as variáveis e cria a matriz de células com o tamanho especificado.
    Grid(int width, int height, int cellSize)
        : rows(height / cellSize),                     // Calcula o número de linhas com base na altura e no tamanho das células
          columns(width / cellSize),                   // Calcula o número de colunas com base na largura e no tamanho das células
          cellSize(cellSize),                          // Armazena o tamanho de cada célula
          cells(rows, std::vector<int>(columns, 0)) {  // Cria uma matriz 2D de células com valores iniciais de 0
        grid.FillRandom();                             // Preenche o grid com valores aleatórios
    }

    void Draw();                    // Método para desenhar o grid
    void SetValue(int row, int column, int value);  // Define o valor de uma célula
    int GetValue(int row, int column);              // Obtém o valor de uma célula
    bool IsWithinBound(int row, int column);        // Verifica se a célula está dentro dos limites do grid
    int GetRows() { return rows; }                  // Retorna o número de linhas do grid
    int GetColumns() { return columns; }            // Retorna o número de colunas do grid
    void FillRandom();                              // Preenche o grid com valores aleatórios
    void Clear();                                   // Limpa o grid, definindo todas as células como inativas
    void ToggleCell(int row, int column);           // Alterna o estado de uma célula entre ativa e inativa

private:
    int rows;                                       // Número de linhas no grid
    int columns;                                    // Número de colunas no grid
    int cellSize;                                   // Tamanho de cada célula
    std::vector<std::vector<int>> cells;            // Matriz 2D que representa o grid, onde cada célula armazena um valor (ativo/inativo)
};

#include <raylib.h>
#include "grid.hpp"

// Método para desenhar o grid
void Grid::Draw() {
    for (int row = 0; row < rows; row++) {           // Itera sobre cada linha do grid
        for (int column = 0; column < columns; column++) { // Itera sobre cada coluna do grid
            // Define a cor da célula: verde se ativa (1) ou cinza se inativa (0)
            Color color = cells[row][column] ? Color{0, 255, 0, 255} : Color{55, 55, 55, 255};
            // Desenha um retângulo representando a célula na posição correspondente
            DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
        }
    }
}

// Define o valor de uma célula no grid (ativa ou inativa)
void Grid::SetValue(int row, int column, int value) {
    if (IsWithinBound(row, column)) { // Verifica se a posição está dentro dos limites do grid
        cells[row][column] = value;   // Define o valor da célula
    }
}

// Retorna o valor de uma célula específica
int Grid::GetValue(int row, int column) {
    if (IsWithinBound(row, column)) { // Verifica se a posição está dentro dos limites do grid
        return cells[row][column];    // Retorna o valor da célula
    }
    return 0; // Retorna 0 se a célula está fora dos limites
}

// Verifica se uma posição específica está dentro dos limites do grid
bool Grid::IsWithinBound(int row, int column) {
    if (row >= 0 && row < rows && column >= 0 && column < columns) { // Confere se linha e coluna estão no intervalo válido
        return true; // Retorna verdadeiro se estiver dentro dos limites
    }
    return false; // Retorna falso caso contrário
}

// Limpa o grid, tornando todas as células inativas (0)
void Grid::Clear() {
    for (int row = 0; row < rows; row++) {               // Itera sobre cada linha
        for (int column = 0; column < columns; column++) { // Itera sobre cada coluna
            cells[row][column] = 0; // Define o valor da célula como inativo
        }
    }
}

// Alterna o estado de uma célula entre ativa e inativa
void Grid::ToggleCell(int row, int column) {
    if (IsWithinBound(row, column)) {       // Verifica se a posição está dentro dos limites
        cells[row][column] = !cells[row][column]; // Inverte o estado da célula
    }
}

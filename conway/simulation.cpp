#include <raylib.h>
#include <vector>
#include <utility>
#include "simulation.hpp"

// Método para desenhar a simulação, chamando o método Draw() da classe Grid
void Simulation::Draw() {
    grid.Draw();
}

// Define o valor de uma célula específica no grid
void Simulation::SetCellValue(int row, int column, int value) {
    grid.SetValue(row, column, value);
}

// Conta o número de vizinhos vivos de uma célula, considerando posições ao redor
int Simulation::CountLiveNeighbours(int row, int column) {
    int liveNeighbours = 0;
    std::vector<std::pair<int, int>> neighbourOffsets = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},   // Vizinho acima, abaixo, à esquerda, à direita
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}  // Diagonais
    };

    // Percorre cada deslocamento de vizinho e soma os vizinhos vivos
    for (const auto& offset : neighbourOffsets) {
        int neighbourRow = (row + offset.first + grid.GetRows()) % grid.GetRows();   // Calcula a linha do vizinho, considerando bordas
        int neighbourColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns(); // Calcula a coluna do vizinho, considerando bordas
        liveNeighbours += grid.GetValue(neighbourRow, neighbourColumn);  // Adiciona o valor da célula vizinha (viva/inativa)
    }
    return liveNeighbours;
}

// Atualiza o estado do grid baseado nas regras do jogo da vida
void Simulation::Update() {
    if (IsRunning()) {    // Apenas atualiza se a simulação estiver em execução
        for (int row = 0; row < grid.GetRows(); row++) {               // Itera sobre cada linha
            for (int column = 0; column < grid.GetColumns(); column++) { // Itera sobre cada coluna
                int liveNeighbours = CountLiveNeighbours(row, column);   // Conta vizinhos vivos da célula
                int cellValue = grid.GetValue(row, column);              // Valor atual da célula (1 = viva, 0 = inativa)

                if (cellValue == 1) {    // Célula viva
                    if (liveNeighbours > 3 || liveNeighbours < 2) {      // Morre por superpopulação ou isolamento
                        tempGrid.SetValue(row, column, 0);               // Define como inativa
                    } else {
                        tempGrid.SetValue(row, column, 1);               // Continua viva
                    }
                } else {              // Célula inativa
                    if (liveNeighbours == 3) { // Revive se tem exatamente 3 vizinhos vivos
                        tempGrid.SetValue(row, column, 1);
                    } else {
                        tempGrid.SetValue(row, column, 0); // Permanece inativa
                    }
                }
            }
        }
        grid = tempGrid;  // Atualiza o grid com o novo estado
    }
}

// Método para preencher o grid com valores aleatórios (chamado para criar estado inicial aleatório)
void Grid::FillRandom() {
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            int randomValue = GetRandomValue(0, 4); // Gera valores entre 0 e 4
            cells[row][column] = (randomValue == 4) ? 1 : 0; // Define como viva (1) apenas se o valor for 4
        }
    }
}

// Limpa o grid, desde que a simulação esteja pausada
void Simulation::ClearGrid() {
    if (!isRunning()) {
        grid.Clear();
    }
}

// Cria um estado aleatório para o grid, desde que a simulação esteja pausada
void Simulation::CreateRandomState() {
    if (!isRunning()) {
        grid.FillRandom();
    }
}

// Alterna o estado de uma célula específica, desde que a simulação esteja pausada
void Simulation::ToggleCell(int row, int column) {
    if (!isRunning()) {
        grid.ToggleCell(row, column);
    }
}

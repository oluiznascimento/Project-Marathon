#pragma once
#include "grid.hpp"

class Simulation {
public:
    // Construtor da classe Simulation, inicializando grids e definindo o estado inicial como pausado
    Simulation(int width, int height, int cellSize)
        : grid(width, height, cellSize),                // Inicializa o grid principal
          tempGrid(width, height, cellSize),            // Inicializa o grid temporário para cálculos
          run(false) {                                  // Inicializa a simulação como pausada
        grid.FillRandom();                              // Preenche o grid principal com células aleatórias
    }

    void Draw();                                       // Desenha o grid na tela
    void SetCellValue(int row, int column, int value); // Define o valor de uma célula específica no grid
    int CountLiveNeighbours(int row, int column);      // Conta o número de vizinhos vivos ao redor de uma célula
    void Update();                                     // Atualiza o estado do grid segundo as regras do jogo
    bool isRunning() { return run; }                   // Verifica se a simulação está em execução
    void Start() { run = true; }                       // Inicia a simulação
    void Stop() { run = false; }                       // Pausa a simulação
    void ClearGrid();                                  // Limpa o grid, deixando todas as células inativas
    void CreateRandomState();                          // Cria um estado inicial aleatório no grid
    void ToggleCell(int row, int column);              // Alterna o estado de uma célula entre ativa e inativa

private:
    Grid grid;                                         // Grid principal que representa o estado atual da simulação
    Grid tempGrid;                                     // Grid temporário para calcular o próximo estado
    bool run;                                          // Indicador do estado da simulação (em execução ou pausada)
};

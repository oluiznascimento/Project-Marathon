#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

int main(){
    Color GREY = {29, 29, 29, 255}; // Define a cor cinza para o fundo
    const int WINDOW_WIDTH = 1200;  // Largura da janela
    const int WINDOW_HEIGHT = 800;  // Altura da janela
    const int CELL_SIZE = 4;        // Tamanho das células da simulação
    int FPS = 12;                   // Taxa de quadros por segundo

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "La Simulaccione"); // Inicializa a janela com título
    SetTargetFPS(FPS);              // Define a taxa de quadros por segundo
    Simulation simulation{WINDOW_HEIGHT, WINDOW_WIDTH, CELL_SIZE}; // Cria uma instância de "Simulation"

    // Loop principal do programa
    while(WindowShouldClose() == false){ // Continua enquanto a janela não for fechada

       //1. Detecta o clique do mouse para alterar o estado de uma célula
       if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
           Vector2 mousePosition = GetMousePosition();  // Pega a posição do mouse
           int row = mousePosition.y / CELL_SIZE;       // Calcula a linha da célula
           int column = mousePosition.x / CELL_SIZE;    // Calcula a coluna da célula
           simulation.ToggleCell(row, column);          // Alterna o estado da célula
       }
       if(IsKeyPressed(KEY_ENTER)){    // Inicia a simulação quando ENTER é pressionado
           simulation.Start();
       }
       else if(IsKeyPressed(KEY_SPACE)){ // Pausa a simulação quando ESPAÇO é pressionado
           simulation.Stop();
       }
       else if(IsKeyPressed(KEY_R)){     // Gera um estado aleatório quando 'R' é pressionado
           simulation.CreateRandomState();
       }
       else if(IsKeyPressed(KEY_C)){     // Limpa a grade quando 'C' é pressionado
           simulation.ClearGrid();
       }

       //2. Atualiza o estado da simulação
       simulation.Update();

       //3. Renderiza o desenho da simulação na tela
        BeginDrawing();
        ClearBackground(GREY);    // Limpa o fundo da janela com a cor cinza
        simulation.Draw();        // Desenha o estado atual da simulação
        EndDrawing();
    }

   CloseWindow(); // Fecha a janela ao final do programa
}

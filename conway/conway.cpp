#include <raylib.h>
#include "simulation.hpp"

int main(){
    Color GREY = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    int FPS = 12;
    const int CELL_SIZE = 25;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "La Simulaccione");
    SetTargetFPS(FPS);
    Simulation simulation{WINDOW_HEIGHT, WINDOW_WIDTH, CELL_SIZE};

    //loop
    while(WindowShouldClose() == false){
       //1.


       //2.


       //3.
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
    }

   CloseWindow();
}

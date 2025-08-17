# SDL2 Cheat Sheet

```C++
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {

    // Initializing video subsystem
    // Loads the drivers
    SDL_Init(SDL_INIT_VIDEO);

    // Creates a window structure
    SDL_Window* window = SDL_CreateWindow("Forage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_MAXIMIZED);

    // Creates an object that renders in the window
    // Creates a memory zone named "Back Buffer",
    // where stuff is draw before display
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    
    // Sets the color for the renderer
    SDL_SetRenderDrawColor(renderer, 200, 50, 100, 255);
    
    // Clears the old buffer and replaces it with
    // the new color
    SDL_RenderClear(renderer);
    
    // Swaps the "Back Buffer" with the "Front Buffer"
    SDL_RenderPresent(renderer);

    // Blocks the execution of the program in ms
    SDL_Delay(5000);

    // Cleanup the memory
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```
#include "Core/Game.h"

int main() {
    auto game = std::make_unique<Core::Game>();
    game->Run();
    return 0;
}
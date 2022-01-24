#include "game.hpp"

using namespace game;

Game::Game()
{
    deltaTime = 0.0;
}
Game::~Game()
{
}

void Game::update(double deltaTime)
{
    this->deltaTime = deltaTime;
}

void Game::render()
{
}
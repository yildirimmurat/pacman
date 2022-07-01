#include "Game.hpp"

Game::Game(): m_window("pacman", sf::Vector2u(800, 600))
{
    RestartClock();
    srand(time(nullptr));
    
    m_texture.loadFromFile("sample/sprites/pacman/0.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
    m_sprite.setPosition(m_texture.getSize().x/2, m_texture.getSize().y/2);

    m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);
}
Game::~Game(){}

void Game::Update()
{
    m_window.Update();
}
void Game::Render()
{
    m_window.BeginDraw();
    m_window.GetRenderWindow()->draw(m_sprite);
    m_window.EndDraw();
}

sf::Time Game::GetElapsed()
{
    return Clock.getElapsedTime();
}
void Game::RestartClock()
{
    Clock.restart();
}

void Game::MoveSprite(EventDetails* l_details)
{
    // todo move to far right horizontal for start
    // m_sprite.SetDirection(Direction::Right);
    std::cout << "going to right now..";

}

Window* Game::GetWindow()
{
    return &m_window;
}
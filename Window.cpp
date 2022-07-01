#include "Window.hpp"

Window::Window() {
    Setup("Window", sf::Vector2u(640, 480));
}
Window::Window(const std::string& title, const sf::Vector2u& size)
{
    Setup(title, size);
}
Window::~Window()
{
    Destroy();
}

void Window::BeginDraw()
{
    m_window.clear(sf::Color::Black);
}
void Window::EndDraw()
{
    m_window.display();
}

void Window::Update()
{
    sf::Event event;

    while(m_window.pollEvent(event)) {
        if (event.type == sf::Event::LostFocus) {
            m_isFocused = false;
            m_eventManager.SetFocus(false);
        } else if (event.type == sf::Event::GainedFocus) {
            m_isFocused = true;
            m_eventManager.SetFocus(true);
        }
        m_eventManager.HandleEvent(event);
    }

    m_eventManager.Update();
}

bool Window::IsDone() { return m_isDone; }
bool Window::IsFullscreen() { return m_isFullscreen; }
bool Window::IsFocused() { return m_isFocused; }

void Window::ToggleFullscreen(EventDetails* l_details)
{
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}
void Window::Close(EventDetails* l_details) {
    m_isDone = true;
}

sf::RenderWindow* Window::GetRenderWindow() { return &m_window; }
EventManager* Window::GetEventManager() { return &m_eventManager; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

void Window::Setup(const std::string title, const sf::Vector2u& size)
{
    m_windowTitle = title;
    m_windowSize = size;
    m_isFullscreen = false;
    m_isDone = false;
    m_isFocused = false;

    m_window.setFramerateLimit(60);

    m_eventManager.AddCallback(
        "Fullscreen_toggle",
        &Window::ToggleFullscreen,
        this
    );
    m_eventManager.AddCallback(
        "Window_close",
        &Window::Close,
        this
    );

    Create();
}
void Window::Create()
{
    sf::Uint32 style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);

    m_window.create(
        sf::VideoMode(m_windowSize.x,m_windowSize.y,32), 
        m_windowTitle, 
        style
    );
}
void Window::Destroy()
{
    m_window.close();
}
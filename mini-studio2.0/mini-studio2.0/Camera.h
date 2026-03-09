#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
private:
    float m_screenWidth, m_screenHeight;
    float m_x, m_y;

public:
    Camera(float screenWidth, float screenHeight)
        : m_screenWidth(screenWidth), m_screenHeight(screenHeight),
        m_x(0.0f), m_y(0.0f) {}

    void update(float playerX, float playerY) 
    {
        m_x = playerX - m_screenWidth * 0.5f;
        m_y = playerY - m_screenHeight * 0.5f;
    }

    float getX() const { return m_x; }
    float getY() const { return m_y; }

  
    sf::View getView() const
    {
        sf::View view;
        view.setSize(m_screenWidth, m_screenHeight);
        view.setCenter(m_x + m_screenWidth * 0.5f, m_y + m_screenHeight * 0.5f);
        return view;
    }
};
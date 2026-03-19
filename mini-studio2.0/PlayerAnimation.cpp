#include "playerAnimation.h"
#include <iostream>

// ============================================================
//  Ctor
// ============================================================
PlayerAnimation::PlayerAnimation() = default;

// ============================================================
//  loadAnimation
// ============================================================
bool PlayerAnimation::loadAnimation(AnimationState     state,
    const std::string& path,
    int   frameCount,
    int   frameWidth,
    int   frameHeight,
    float frameDuration,
    bool  loop)
{
    AnimationClip clip;

    if (!clip.texture.loadFromFile(path))
    {
        std::cerr << "[PlayerAnimation] Impossible de charger : " << path << "\n";
        return false;
    }

    clip.frameCount = frameCount;
    clip.frameWidth = frameWidth;
    clip.frameHeight = frameHeight;
    clip.frameDuration = frameDuration;
    clip.loop = loop;

    m_clips[state] = std::move(clip);
    return true;
}

// ============================================================
//  setState
// ============================================================
void PlayerAnimation::setState(AnimationState state)
{
    if (state == m_currentState)
        return;

    m_currentState = state;
    m_currentFrame = 0;
    m_timer = 0.f;
    m_finished = false;
}

// ============================================================
//  update
// ============================================================
void PlayerAnimation::update(float dt)
{
    const AnimationClip* clip = currentClip();
    if (!clip || m_finished)
        return;

    m_timer += dt;

    if (m_timer >= clip->frameDuration)
    {
        m_timer -= clip->frameDuration;
        m_currentFrame++;

        if (m_currentFrame >= clip->frameCount)
        {
            if (clip->loop)
                m_currentFrame = 0;
            else
            {
                m_currentFrame = clip->frameCount - 1; // reste sur la dernière frame
                m_finished = true;
            }
        }
    }
}

// ============================================================
//  applyTo  — applique texture + rect au RectangleShape
// ============================================================
void PlayerAnimation::applyTo(sf::RectangleShape& shape) const
{
    const AnimationClip* clip = currentClip();
    if (!clip)
        return;

    // Texture
    shape.setTexture(&clip->texture);

    // Calcul du rect de la frame courante (spritesheet horizontale)
    int x = m_currentFrame * clip->frameWidth;
    int y = 0;

    if (m_facingRight)
    {
        // Lecture normale gauche ? droite
        shape.setTextureRect(sf::Rect<int>(
            { x, y },
            { clip->frameWidth, clip->frameHeight }
        ));
    }
    else
    {
        // Flip horizontal : on part du bord droit de la frame et on va vers la gauche
        shape.setTextureRect(sf::Rect<int>(
            { x + clip->frameWidth, y },
            { -clip->frameWidth, clip->frameHeight }
        ));
    }
}

// ============================================================
//  setFacingRight
// ============================================================
void PlayerAnimation::setFacingRight(bool right)
{
    m_facingRight = right;
}

// ============================================================
//  currentClip  (helper privé)
// ============================================================
const AnimationClip* PlayerAnimation::currentClip() const
{
    auto it = m_clips.find(m_currentState);
    if (it == m_clips.end())
        return nullptr;
    return &it->second;
}
#ifndef SHOOTER_EXPLOSION_H
#define SHOOTER_EXPLOSION_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Explosion {
private:
    bool isFinished;
    int explosionType;
    int numFrames;
    int currentFrame;
    int dimension;
    int framesAcross;

    float animationSpeed;

    Vector2f position;
    Sprite m_sprite;
    IntRect spriteRect;

    Time timeSinceLastFrame;

public:
    enum types {EXPLOSION1=1, EXPLOSION2};

    Explosion(Vector2f explosionPosition, int explosionType);

    bool getFinished();

    Time getTimeSinceLastFrame();

    void update(Time dt);

    Sprite getSprite();

};


#endif //SHOOTER_EXPLOSION_H

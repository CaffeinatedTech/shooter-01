#ifndef SHOOTER_BULLET_H
#define SHOOTER_BULLET_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
private:
    bool isPlayerBullet;
    int bulletType;

    Sprite m_sprite;
    Vector2f position;
    float speed;

public:
    enum types {LASER1=1, LASER2};

    Bullet(bool playerFired, Vector2f bulletPosition, int bulletType);

    bool getIsPlayerBullet();
    int getBulletType();
    Vector2f getPosition();
    void setPosition(Vector2f newPosition);
    float getSpeed();

    void update(Time dt, Vector2f resolution, int levelHeight);

    Sprite getSprite();

};

#endif //SHOOTER_BULLET_H

#ifndef SHOOTER_ENEMY_H
#define SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy {
private:
    int enemyType;
    int health;
    float speed;
    unsigned long long int scorePerHit;
    unsigned long long int scorePerKill;

    Sprite m_sprite;
    Vector2f position;

    bool canShoot;

    bool isShooting;
    bool isDead;


public:
    enum types {ENEMY1=1, ENEMY2};
    const static int enemyTypeCount = 2;

    Enemy(int type, Vector2f startPosition);

    Sprite getSprite();

    int getEnemyType();
    Vector2f getPosition();
    void setPosition(Vector2f newPosition);
    Vector2f getCenter();
    float getSpeed();
    void setSpeed(float newSpeed);
    bool decrementHealth(int amount);
    int getHealth();
    unsigned long long int getScorePerHit();
    unsigned long long int getScorePerKill();
    bool getShooting();
    void setShooting();

    bool getDead();
    void setDead();

    // Do damage to the enemy and return the amount of points earned.
    unsigned long long int takeDamage(int damage);

    void kill();

    void update(Time dt, Vector2f resolution);


};


#endif //SHOOTER_ENEMY_H

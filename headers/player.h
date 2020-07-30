#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>

using namespace sf;


class Player {
private:
    int lives;
    int health;
    int maxHealth;
    int shield;
    int maxShield;
    unsigned long long int score;

    Sprite m_sprite;

    Vector2f position;

    float speed = 10.0f;
    int shootSpeed = 100; // Milliseconds between shots

    bool leftPressed;
    bool rightPressed;
    bool upPressed;
    bool downPressed;

    bool isShooting;

    Vector2f gunPositions [3];
    int lastGun;

    Clock shootClock;

public:
    enum DIRECTION { LEFT, RIGHT, UP, DOWN };
    enum SIDES {SHIPLEFT, SHIPMIDDLE, SHIPRIGHT};
    Player();
    int getLives();
    void setLives(int newLives);
    int getHealth();
    void setHealth(int newHealth);
    int getMaxHealth();
    void setMaxHealth(int newMaxHealth);
    int getShield();
    void setShield(int newShield);
    int getMaxShield();
    void setMaxShield(int newMaxShield);
    unsigned long long int getScore();
    void setScore(unsigned long long int newScore);
    void increaseScore(unsigned long long int scoreIncrement);
    Vector2f getPosition();
    void setPosition(Vector2f newPosition);

    void setDirectionPressed(DIRECTION dir, bool pressed);

    void setShooting(bool isShooting);
    bool getShooting();
    void setShootSpeed(int newShootSpeed);
    int getShootSpeed();
    Time getShootClock();
    void restartShootClock();

    Vector2f getShootPosition();

    bool takeDamage(int damage);

    void update(Time dt, Vector2f resolution, int levelWidth);

    Sprite getSprite();

};


#endif //SHOOTER_PLAYER_H

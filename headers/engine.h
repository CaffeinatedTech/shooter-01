#ifndef SHOOTER_ENGINE_H
#define SHOOTER_ENGINE_H

#include "player.h"
#include "textureholder.h"
#include "bullet.h"
#include "Enemy.h"
#include "Explosion.h"
#include "enemyspawner.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;


class Engine {
private:
    TextureHolder th;

    Player player;

    Vector2f resolution;
    int levelWidth;

    const unsigned int FPS = 60;
    static const Time TimePerFrame;
    Time runningTime;
    Time waveTime;
    int intermissionTime; // Number of seconds between waves.
    Time intermissionRunningTime;
    bool waveRunning;
    int waveNumber;

    RenderWindow window;

    View mainView;

    Sprite backgroundSprite;
    Texture backgroundTexture;
    int backgroundY;
    float backgroundSpeed;
    Sprite playerShipSprite;
    Texture playerShipTexture;
    RectangleShape playerHealthBarFrame;
    RectangleShape playerHealthBar;

    vector<EnemySpawner> enemyList;

    Font scoreFont;
    Text scoreText;
    unsigned long long int displayedScore;


public:
    Engine();

    vector<Bullet> bullets;
    vector<Enemy> enemies;
    vector<Explosion> explosions;

    void input();
    void update(Time dt);
    void draw();

    // The main loop will be in the run function
    void run();

    vector<EnemySpawner> generateNextWave(int waveNumber);

};


#endif //SHOOTER_ENGINE_H

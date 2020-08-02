//
// Created by adam on 10/5/20.
//

#include "engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
  // Set up all of the window, textures, sprites, sounds etc.


  resolution.x = 1920;
  resolution.y = 1080;

  levelWidth = 2500;


  window.create(VideoMode(resolution.x, resolution.y), "Shooter", Style::Default);
  window.setFramerateLimit(FPS);

  mainView.setSize(resolution);


  backgroundTexture = TextureHolder::GetTexture("graphics/stars.png");
  backgroundTexture.setRepeated(true);
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setPosition(0,0);
  backgroundY = 0;
  backgroundSprite.setTextureRect(sf::IntRect(0, backgroundY, levelWidth, 1080));
  backgroundSpeed = 0.5f;

  playerHealthBarFrame.setSize(Vector2f(305, 35));
  playerHealthBarFrame.setOutlineColor(Color::Blue);
  playerHealthBarFrame.setOutlineThickness(2.5f);
  playerHealthBarFrame.setFillColor(Color::Transparent);
  playerHealthBarFrame.setPosition(Vector2f(97.5f, 17.5f));

  playerHealthBar.setSize(Vector2f(300, 30));
  playerHealthBar.setFillColor(Color::Green);
  playerHealthBar.setPosition(Vector2f(100, 20));


  displayedScore = 0;

  scoreFont.loadFromFile("graphics/slant_regular.ttf");
  scoreText.setFont(scoreFont);
  scoreText.setString(to_string(displayedScore));
  scoreText.setCharacterSize(72);
  scoreText.setFillColor(Color::Green);
  FloatRect scoreTextBounds = scoreText.getLocalBounds();
  scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 20, 0));


  intermissionTime = 10; // Number of seconds between waves
  runningTime = Time::Zero;
  waveTime = Time::Zero;
  intermissionRunningTime = Time::Zero;
  waveRunning = true;
  waveNumber = 1;

  // Generate the first enemy wave
  enemyList = generateNextWave(waveNumber);
}

void Engine::run() {
  // timing
  Clock clock;
  Time timeSinceLastUpdate = Time::Zero;

  while(window.isOpen()) {
    Time dt = clock.restart();
    timeSinceLastUpdate += dt;
    runningTime += dt;
    if (waveRunning) {
      waveTime += dt;
    }
    else {
      intermissionRunningTime += dt;
    }

    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      input();
      update(TimePerFrame);
    }


    draw();

  }

}

/**
 * Generate Next Enemy Wave
 * This will return a vector of enemies to spawn.
 * Using the waveNumber we can increase the difficulty
 * @param newWaveNumber
 * @return vector<EnemySpawner> - A vector of enemies to spawn
 */
vector<EnemySpawner> Engine::generateNextWave(int newWaveNumber) {
  vector<EnemySpawner> newEnemyList;
  // TODO - Increase difficulty based on wave number
  // Generate an enemy list
  srand ((unsigned) time(nullptr));
  int randomXPos;
  int spawnTime = 0;
  for (int i = 0; i < 12; i ++) {
    randomXPos = rand() % (levelWidth - 200) + 100;
    spawnTime += rand() % (3000) + 1;
    newEnemyList.emplace_back(Enemy::ENEMY1, randomXPos, spawnTime);
  }
  return newEnemyList;
}

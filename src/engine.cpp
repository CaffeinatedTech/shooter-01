//
// Created by adam on 10/5/20.
//

#include <random>
#include "engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
  // Set up all of the window, textures, sprites, sounds etc.


  resolution.x = 1920;
  resolution.y = 1080;

  levelWidth = 2500;

  // Add enemy weights
  enemyWeightsReset();


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

  // Intermission Text
  intermissionTimer.setFont(scoreFont);
  intermissionTimer.setCharacterSize(120);
  intermissionTimer.setFillColor(Color::Yellow);
  intermissionTimer.setString("Next Wave: 9");
  FloatRect intermissionTimerBounds = intermissionTimer.getLocalBounds();
  intermissionTimer.setPosition(Vector2f(resolution.x / 2 - intermissionTimerBounds.width / 2, 300));

  intermissionWaveLabel.setFont(scoreFont);
  intermissionWaveLabel.setCharacterSize(72);
  intermissionWaveLabel.setFillColor(Color::Blue);
  intermissionWaveLabel.setString("Waves Completed: ");
  FloatRect intermissionWaveLabelBounds = intermissionWaveLabel.getLocalBounds();
  intermissionWaveLabel.setPosition(Vector2f(
      (resolution.x / 2 - intermissionWaveLabelBounds.width) + 200,
      600
      ));

  intermissionWaveValue.setFont(scoreFont);
  intermissionWaveValue.setCharacterSize(72);
  intermissionWaveValue.setFillColor(Color::Green);
  intermissionWaveValue.setString("9");
  intermissionWaveValue.setPosition(Vector2f(
      resolution.x / 2 + 250,
      600
  ));

  intermissionWaveKillsLabel.setFont(scoreFont);
  intermissionWaveKillsLabel.setCharacterSize(72);
  intermissionWaveKillsLabel.setFillColor(Color::Blue);
  intermissionWaveKillsLabel.setString("Last Wave Kills: ");
  FloatRect intermissionWaveKillsLabelBounds = intermissionWaveKillsLabel.getLocalBounds();
  intermissionWaveKillsLabel.setPosition(Vector2f(
      (resolution.x / 2 - intermissionWaveKillsLabelBounds.width) + 200,
      680
  ));

  intermissionWaveKillsValue.setFont(scoreFont);
  intermissionWaveKillsValue.setCharacterSize(72);
  intermissionWaveKillsValue.setFillColor(Color::Green);
  intermissionWaveKillsValue.setString("9");
  intermissionWaveKillsValue.setPosition(Vector2f(
      resolution.x / 2 + 250,
      680
  ));

  intermissionWaveScoreLabel.setFont(scoreFont);
  intermissionWaveScoreLabel.setCharacterSize(72);
  intermissionWaveScoreLabel.setFillColor(Color::Blue);
  intermissionWaveScoreLabel.setString("Last Wave Score: ");
  FloatRect intermissionWaveScoreLabelBounds = intermissionWaveScoreLabel.getLocalBounds();
  intermissionWaveScoreLabel.setPosition(Vector2f(
      (resolution.x / 2 - intermissionWaveScoreLabelBounds.width) + 200,
      760
  ));

  intermissionWaveScoreValue.setFont(scoreFont);
  intermissionWaveScoreValue.setCharacterSize(72);
  intermissionWaveScoreValue.setFillColor(Color::Green);
  intermissionWaveScoreValue.setString("9");
  intermissionWaveScoreValue.setPosition(Vector2f(
      resolution.x / 2 + 250,
      760
  ));

  gameOverLabel.setFont(scoreFont);
  gameOverLabel.setCharacterSize(120);
  gameOverLabel.setFillColor(Color::Yellow);
  gameOverLabel.setString("GAME OVER");
  FloatRect gameOverLabelBounds = gameOverLabel.getLocalBounds();
  gameOverLabel.setPosition(Vector2f(resolution.x / 2 - gameOverLabelBounds.width / 2, 300));

  gameOverTotalScoreLabel.setFont(scoreFont);
  gameOverTotalScoreLabel.setCharacterSize(72);
  gameOverTotalScoreLabel.setFillColor(Color::Blue);
  gameOverTotalScoreLabel.setString("Total Score: ");
  FloatRect gameOverTotalScoreLabelBounds = gameOverTotalScoreLabel.getLocalBounds();
  gameOverTotalScoreLabel.setPosition(Vector2f(
      (resolution.x / 2 - gameOverTotalScoreLabelBounds.width),
      600
  ));

  gameOverTotalScoreValue.setFont(scoreFont);
  gameOverTotalScoreValue.setCharacterSize(72);
  gameOverTotalScoreValue.setFillColor(Color::Green);
  gameOverTotalScoreValue.setString("9");
  gameOverTotalScoreValue.setPosition(Vector2f(
      gameOverTotalScoreLabel.getPosition().x + gameOverTotalScoreLabelBounds.width + 50,
      600
  ));

  gameOverStartButtonLabel.setFont(scoreFont);
  gameOverStartButtonLabel.setCharacterSize(72);
  gameOverStartButtonLabel.setFillColor(Color::Blue);
  gameOverStartButtonLabel.setString("Press ENTER to try again");
  FloatRect gameOverStartButtonLabelBounds = gameOverStartButtonLabel.getLocalBounds();
  gameOverStartButtonLabel.setPosition(Vector2f(
      (resolution.x / 2 - gameOverStartButtonLabelBounds.width / 2),760));


  intermissionTime = 6; // Number of seconds between waves
  runningTime = Time::Zero;
  waveTime = Time::Zero;
  intermissionRunningTime = Time::Zero;
  waveRunning = true;
  waveNumber = 1;
  waveKills = 0;
  waveScore = 0;

  paused = false;
  gameOver = false;

  // Generate the first enemy wave
  enemyList = generateNextWave(waveNumber);
}

void Engine::run() {
  // timing
  Clock clock;
  Time timeSinceLastUpdate = Time::Zero;

  while(window.isOpen()) {
    Time dt = clock.restart();

    if (this->paused || this->gameOver) {
      // If we are paused, then check for input (so we can un-pause) and just go to the next loop
      input();

      if (this->gameOver) {
        draw();
      }

      sleep(milliseconds(5)); // Sleep so we don't peg the CPU
      continue;
    }

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

void Engine::newGameReset() {
  this->enemyWeightsReset();
  this->enemies.clear();
  this->enemyList.clear();
  this->waveKills = 0;
  this->waveNumber = 1;
  this->waveScore = 0;
  player.setScore(0);
  player.setHealth(player.getMaxHealth());
  this->enemyList.clear();
  this->enemyWeightsReset();
  this->runningTime = Time::Zero;
  this->waveTime = Time::Zero;
  this->enemyList = generateNextWave(this->waveNumber);
  this->bullets.clear();
  this->explosions.clear();
}

void Engine::updateGameOverScore() {
  gameOverTotalScoreValue.setString(to_string(player.getScore()));
}

void Engine::enemyWeightsReset() {
  this->enemyWeights.clear();
  int weightToDistribute = 100;
  for (int i = 0; i < Enemy::enemyTypeCount; i++) {
    this->enemyWeights.push_back(weightToDistribute);
    weightToDistribute = 0;
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

  // Update enemy weights
  if (newWaveNumber > 1) {
    for (int e = Enemy::enemyTypeCount - 1; e >= 0; e--) {
      if (e > 0) {
        if (enemyWeights[e - 1] >= 10 - (e+1)) {
          enemyWeights[e - 1] -= 10 - (e+1);
          enemyWeights[e] += 10 - (e+1);
        }
      }
    }
  }

  // Generate an enemy list
  srand ((unsigned) time(nullptr));
  int randomXPos;
  int spawnTime = 0;
  int enemyToSpawn = 1;
  random_device rd;
  mt19937 gen(rd());
  discrete_distribution<int> d (enemyWeights.begin(), enemyWeights.end());
  for (int i = 0; i < 12; i ++) {
    randomXPos = rand() % (levelWidth - 200) + 100;
    spawnTime += rand() % (3000) + 1;
    enemyToSpawn = d(gen)+1;
    newEnemyList.emplace_back(enemyToSpawn, randomXPos, spawnTime);
  }
  return newEnemyList;
}

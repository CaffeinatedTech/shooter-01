#include "engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cmath>


using namespace sf;

void Engine::update(Time dt) {
  stringstream ss;
  player.update(dt, resolution, levelWidth);

  // Scroll Background
  if (backgroundY < 1080) {
    backgroundY -= backgroundSpeed * dt.asMilliseconds();
  }
  else {
    backgroundY = 0;
  }
  backgroundSprite.setTextureRect(IntRect(0,backgroundY, levelWidth, 1080));

  // Set MainView position limiting it to size of the level
  Vector2f newMainViewPos;
  newMainViewPos.x = player.getPosition().x;
  if (newMainViewPos.x - resolution.x / 2 < 0) {
    newMainViewPos.x = resolution.x / 2;
  }
  if (newMainViewPos.x + (resolution.x / 2) > (float) levelWidth) {
    newMainViewPos.x = (float) levelWidth - resolution.x / 2;
  }
  newMainViewPos.y = mainView.getCenter().y;
  mainView.setCenter(newMainViewPos);

  // Player Shooting
  if (player.getShooting()) {
    // Don't shoot too often
    if (player.getShootClock().asMilliseconds() > player.getShootSpeed()) {
      bullets.push_back(Bullet(true, player.getShootPosition(), Bullet::LASER1, false, Vector2f(0.0f, 1.0f)));
      player.restartShootClock();
    }
  }
  else { // Not shooting, start repairing
    if (player.getHealth() < player.getMaxHealth()) {
      if (player.getRepairClock().asMilliseconds() > player.getRepairDelay()) {
        player.repair(player.getRepairAmount());
      }
    }
  }

  // Check for player ship colliding with enemy
  for (int e = 0; e < enemies.size(); e++) {
    if (player.getSprite().getGlobalBounds().intersects(enemies[e].getSprite().getGlobalBounds())) {
      // Player hit an enemy
      bool playerIsDead = player.takeDamage(20); // Magic number, some enemies should be big enough to kill the player outright.
      // TODO - Process player death.

      // Destroy the enemy and increment score - you did get a kill after all
      long long unsigned int thisCollisionScore = enemies[e].getScorePerKill();
      player.increaseScore(thisCollisionScore);
      waveScore += thisCollisionScore;
      waveKills++;
      enemies[e].kill();
      explosions.push_back(Explosion(enemies[e].getCenter(), Explosion::EXPLOSION1));
      enemies.erase(enemies.begin() + e);
      continue;
    }
  }

  // Process Bullets
  for (int i = 0; i < bullets.size(); i++) {
    // Check if bullet is outside screen and delete it
    if (bullets[i].getPosition().y < -150) {
      bullets.erase(bullets.begin() + i);
      continue;
    }
    else if (bullets[i].getPosition().y > resolution.y + 50) {
      bullets.erase(bullets.begin() + i);
      continue;
    }

    bullets[i].update(dt, resolution, resolution.y);

    // Check for collisions
    // Player Bullets
    if (bullets[i].getIsPlayerBullet()) {
      for (int e = 0; e < enemies.size(); e++) {
        if (bullets[i].getSprite().getGlobalBounds().intersects(enemies[e].getSprite().getGlobalBounds())) {
          // Bullet hit enemy
          cout << "enemy hit! ";
          long long unsigned int thisHitScore = enemies[e].takeDamage(5);
          player.increaseScore(thisHitScore);
          waveScore += thisHitScore;
          bullets.erase(bullets.begin() + i);
          if (enemies[e].getDead()) {
            waveKills++;
            enemies[e].kill();
            explosions.push_back(Explosion(enemies[e].getCenter(), Explosion::EXPLOSION1));
            enemies.erase(enemies.begin() + e);
            //continue;
          }
          continue;
        }
      }
    }

    // Enemy Bullets
    if (!bullets[i].getIsPlayerBullet()) {
      if (bullets[i].getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
        bool playerIsDead = player.takeDamage(20); // Magic number, some enemies should be big enough to kill the player outright.
        bullets.erase(bullets.begin() + i);
      }
    }
  }

  // Process Enemies
  for (int i = 0; i < enemies.size(); i++) {
    enemies[i].update(dt, resolution);
    // Enemy Shooting
    bool allowShot = false;
    if (enemies[i].getCanShoot()) {
      if (enemies[i].getFirstShotDelay() > 0) {
        if (enemies[i].getShootClock().asMilliseconds() > enemies[i].getFirstShotDelay()) {
          allowShot = true;
        }
      }
      if (enemies[i].getShootClock().asMilliseconds() > enemies[i].getShootSpeed()) {
        allowShot = true;
      }
    }
    if (allowShot) {
      bullets.push_back(Bullet(false, enemies[i].getShootPosition(), enemies[i].getBulletType(), enemies[i].getShootAtPlayer(), player.getCenterPosition()));
      enemies[i].restartShootClock();
    }


    // Check if enemy is below the screen, and delete it
    if (enemies[i].getPosition().y > resolution.y + 150) {
      enemies.erase(enemies.begin() + i);
    }
  }

  // Process Explosions
  for (int x = 0; x < explosions.size(); x++) {
    explosions[x].update(dt);
    if (explosions[x].getFinished()) {
      explosions.erase(explosions.begin() + x);
    }
  }

  // Update score text
  if (displayedScore != player.getScore()) {
    displayedScore = player.getScore();
    scoreText.setString(to_string(displayedScore));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 20, 0));
  }

  // Check if the Enemy Spawn list is empty - player has reached the end of the wave
  if (enemyList.empty() && enemies.empty()) {
    // Increment the wave number and fetch a new enemy spawn list.
    waveNumber ++;
    waveTime = Time::Zero;
    enemyList = generateNextWave(waveNumber);

    // Put us into intermission
    waveRunning = false;
    intermissionWaveKillsValue.setString(to_string(waveKills));
    intermissionWaveValue.setString(to_string(waveNumber - 1));
    intermissionWaveScoreValue.setString(to_string(waveScore));
  }

  // Check if intermission has ended
  if (!waveRunning && intermissionRunningTime.asSeconds() >= intermissionTime) {
    waveRunning = true;
    intermissionRunningTime = Time::Zero;
    waveKills = 0;
    waveScore = 0;
  }

  // Update intermission text
  if (!waveRunning) {
    stringstream ss;
    ss << ceil(intermissionTime - intermissionRunningTime.asSeconds());
    intermissionTimer.setString("Next Wave: " + ss.str());
  }

  // Process Enemy Spawn list
  if (waveRunning) {
    for (int i = 0; i < enemyList.size(); i++) {
      if (waveTime.asMilliseconds() >= enemyList[i].spawnTime) {
        enemies.emplace_back(enemyList[i].type, Vector2f(enemyList[i].positionX, -100));
        enemyList.erase(enemyList.begin() + i);
      } else {
        // There must not be any enemies with spawn times less than or equal to the running time.
        // So don't bother iterating the rest of the list.
        break;
      }
    }
  }

  // Update Player health Bar
  float newPlayerHealthbarWidth = (player.getHealth() / 100.0f) * 300.0f;
  if (newPlayerHealthbarWidth < 0) { newPlayerHealthbarWidth = 0.0f; }
  playerHealthBar.setSize(Vector2f(newPlayerHealthbarWidth, playerHealthBar.getSize().y));

  // DEBUG - Just printing the number of active bullets

  ss << "Enemy Weaights: " << enemyWeights[0] << "," << enemyWeights[1] << "," << enemyWeights[2] << " | ";
  ss << bullets.size();

  cout << ss.str() << " bullets | Explosions: " << explosions.size() << " | SCORE:  " << player.getScore() << " | HEALTH: " << player.getHealth() << " | ";

}

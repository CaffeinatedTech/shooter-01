#include "engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>


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
      bullets.push_back(Bullet(true, player.getPosition(), Bullet::LASER1));
      player.restartShootClock();
    }
  }

  // Check for player ship colliding with enemy
  for (int e = 0; e < enemies.size(); e++) {
    if (player.getSprite().getGlobalBounds().intersects(enemies[e].getSprite().getGlobalBounds())) {
      // Player hit an enemy
      bool playerIsDead = player.takeDamage(20); // Magic number, some enemies should be big enough to kill the player outright.
      // TODO - Process player death.

      // Destroy the enemy and increment score - you did get a kill after all
      player.increaseScore(enemies[e].getScorePerKill());
      enemies[e].kill();
      explosions.push_back(Explosion(enemies[e].getCenter(), Explosion::EXPLOSION1));
      enemies.erase(enemies.begin() + e);
      continue;
    }
  }

  // Process Bullets
  for (int i = 0; i < bullets.size(); i++) {
    // Check if bullet is outside screen and delete it
    if (bullets[i].getPosition().y < -50) {
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
          player.increaseScore(enemies[e].takeDamage(5));
          bullets.erase(bullets.begin() + i);
          if (enemies[e].getDead()) {
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
  }

  // Process Enemies
  for (int i = 0; i < enemies.size(); i++) {
    enemies[i].update(dt, resolution);
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

  // Process Enemy Spawn list
  for (int i = 0; i < enemyList.size(); i++) {
    if (runningTime.asSeconds() >= enemyList[i].spawnTime) {
      enemies.emplace_back(enemyList[i].type, Vector2f(enemyList[i].positionX, -100));
      enemyList.erase(enemyList.begin() + i);
    }
    else {
      // There must not be any enemies with spawn times less than or equal to the running time.
      // So don't bother iterating the rest of the list.
      break;
    }
  }

  // DEBUG - Just printing the number of active bullets

  ss << bullets.size();
  cout << ss.str() << " bullets | Explosions: " << explosions.size() << " | SCORE:  " << player.getScore() << " | HEALTH: " << player.getHealth() << " | ";

}

#include "engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>


using namespace sf;

void Engine::update(Time dt) {
  stringstream ss;
  player.update(dt, resolution, levelWidth);

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

  // DEBUG - Just printing the number of active bullets

  ss << bullets.size();
  cout << ss.str() << " bullets | SCORE:  " << player.getScore() << " | HEALTH: " << player.getHealth() << " | ";

}

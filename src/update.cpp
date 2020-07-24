#include "engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>


using namespace sf;

void Engine::update(Time dt) {

  player.update(dt, resolution, levelWidth);

  if (player.getShooting()) {
    // Don't shoot too often
    if (player.getShootClock().asMilliseconds() > player.getShootSpeed()) {
      bullets.push_back(Bullet(true, player.getPosition(), Bullet::LASER1));
      player.restartShootClock();
    }
  }

  // Process Bullets
  for (int i = 0; i < bullets.size(); i++) {
    // Check if bullet is above screen and delete it
    if (bullets[i].getPosition().y < -50) {
      bullets.erase(bullets.begin() + i);
      continue;
    }
    else if (bullets[i].getPosition().y > resolution.y + 50) {
      bullets.erase(bullets.begin() + i);
      continue;
    }

    // TODO - check for collisions
    bullets[i].update(dt, resolution, resolution.y);
  }

  // DEBUG - Just printing the number of active bullets
  stringstream ss;
  ss << bullets.size();
  cout << ss.str() << " bullets | ";

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
}

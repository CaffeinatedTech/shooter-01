#include "engine.h"

void Engine::input() {
  Event event;
  while (window.pollEvent(event)) {
    if (event.type == Event::Closed) {
      window.close();
    }

    if (event.type == Event::KeyPressed) {
      // Handle the player quitting
      if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
      }

      // Handle Shooting
      if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (!player.getShooting()) {
          player.setShooting(true);
        }
      }
    }

    if (event.type == Event::KeyReleased) {
      if (event.key.code == Keyboard::Space) {
        if (player.getShooting()) {
          player.setShooting(false);
        }
      }
    }

    player.setDirectionPressed(Player::DIRECTION::RIGHT, Keyboard::isKeyPressed(Keyboard::Right));
    player.setDirectionPressed(Player::DIRECTION::LEFT, Keyboard::isKeyPressed(Keyboard::Left));
    player.setDirectionPressed(Player::DIRECTION::UP, Keyboard::isKeyPressed(Keyboard::Up));
    player.setDirectionPressed(Player::DIRECTION::DOWN, Keyboard::isKeyPressed(Keyboard::Down));
  }
}
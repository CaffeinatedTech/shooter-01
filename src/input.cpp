#include "engine.h"

void Engine::input() {
  Event event;
  float moveX = 0.0f;
  float moveY = 0.0f;
  while (window.pollEvent(event)) {
    if (event.type == Event::Closed) {
      window.close();
    }

    // Handle keyboard input
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

      // Handle Pause
      if (Keyboard::isKeyPressed(Keyboard::Pause) || Keyboard::isKeyPressed(Keyboard::P)) {
        this->paused = !this->paused;
      }
    }

    if (event.type == Event::KeyReleased) {
      if (event.key.code == Keyboard::Space) {
        if (player.getShooting()) {
          player.setShooting(false);
        }
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
      moveX = 100.0f;
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) {
      moveY = 100.0f;
    }

    // Handle joystick 0 input
    if (event.type == Event::JoystickButtonPressed) {
      if (Joystick::isButtonPressed(0, 0)) {
        if (!player.getShooting()) {
          player.setShooting(true);
        }
      }
    }

    if (event.type == Event::JoystickButtonReleased) {
      if (event.joystickButton.button == 0) {
        if (player.getShooting()) {
          player.setShooting(false);
        }
      }
    }

    bool joystickRight = false;
    bool joystickLeft = false;
    bool joystickUp = false;
    bool joystickDown = false;

    if (Joystick::getAxisPosition(0, Joystick::X) > 0) { joystickRight = true; }
    else if (Joystick::getAxisPosition(0, Joystick::X) < 0) { joystickLeft = true; }
    if (Joystick::getAxisPosition(0, Joystick::Y) < 0) { joystickUp = true; }
    else if (Joystick::getAxisPosition(0, Joystick::Y) > 0) { joystickDown = true; }

    if (moveX == 0.0f) {
      moveX = Joystick::getAxisPosition(0, Joystick::X);
    }
    if (moveY == 0.0f) {
      moveY = Joystick::getAxisPosition(0, Joystick::Y);
    }

    player.setDirectionPressed(
        Player::DIRECTION::RIGHT,
        Keyboard::isKeyPressed(Keyboard::Right) || joystickRight,
        moveX);
    player.setDirectionPressed(
        Player::DIRECTION::LEFT,
        Keyboard::isKeyPressed(Keyboard::Left) || joystickLeft,
        moveX);
    player.setDirectionPressed(
        Player::DIRECTION::UP,
        Keyboard::isKeyPressed(Keyboard::Up) || joystickUp,
        moveY);
    player.setDirectionPressed(
        Player::DIRECTION::DOWN,
        Keyboard::isKeyPressed(Keyboard::Down) || joystickDown,
        moveY);
  }
}
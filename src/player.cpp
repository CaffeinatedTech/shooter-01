//
// Created by adam on 10/5/20.
//

#include "player.h"
#include "textureholder.h"
#include <sstream>
#include <iostream>
#include <bullet.h>

Player::Player() {
  lives = 3;
  health = 100;
  maxHealth = health;
  shield = 100;
  maxShield = shield;
  score = 0;

  position.x = 100;
  position.y = 900;

  isShooting = false;

  shootClock.restart();

  m_sprite.setTexture(TextureHolder::GetTexture("graphics/ship1.png"));
  m_sprite.setPosition(position);
}

int Player::getLives() {
  return this->lives;
}

void Player::setLives(int newLives) {
  this->lives = newLives;
}

int Player::getHealth() {
  return this->health;
}

void Player::setHealth(int newHealth) {
  this->health = newHealth;
}

int Player::getMaxHealth() {
  return this->maxHealth;
}

void Player::setMaxHealth(int newMaxHealth) {
  this->maxHealth = newMaxHealth;
}

int Player::getShield() {
  return this->shield;
}

void Player::setShield(int newShield) {
  this->shield = newShield;
}

int Player::getMaxShield() {
  return this->maxShield;
}

void Player::setMaxShield(int newMaxShield) {
  this->maxShield = newMaxShield;
}

unsigned long long int Player::getScore() {
  return this->score;
}

void Player::setScore(unsigned long long int newScore) {
  this->score = newScore;
}

void Player::increaseScore(unsigned long long int scoreIncrement) {
  this->score += scoreIncrement;
}

Sprite Player::getSprite() {
  return m_sprite;
}

Vector2f Player::getPosition() {
  return this->position;
}

void Player::setPosition(Vector2f newPosition) {
  this->position = newPosition;
  this->m_sprite.setPosition(newPosition);
}

void Player::setDirectionPressed(DIRECTION dir, bool pressed) {
  switch (dir) {
    case LEFT:
      leftPressed = pressed;
      break;
    case RIGHT:
      rightPressed = pressed;
      break;
    case UP:
      upPressed = pressed;
      break;
    case DOWN:
      downPressed = pressed;
      break;
  }
}

void Player::setShooting(bool isShooting) {
  this->isShooting = isShooting;
}

bool Player::getShooting() {
  return this->isShooting;
}

Time Player::getShootClock() {
  return shootClock.getElapsedTime();
}

void Player::restartShootClock() {
  shootClock.restart();
}

void Player::setShootSpeed(int newShootSpeed) {
  this->shootSpeed = newShootSpeed;
}

int Player::getShootSpeed() {
  return this->shootSpeed;
}

bool Player::takeDamage(int damage) {
  bool isPlayerDead;
  this->health -= damage;
  isPlayerDead = this->health <= 0;
  return isPlayerDead;
}

void Player::update(Time dt, Vector2f resolution, int levelWidth) {
  stringstream ss;
  ss << position.x;
  string playerIsShooting = "";
  if (getShooting()) {
    playerIsShooting = " Shooting";
    new Bullet(true, position, Bullet::LASER1);
  }
  cout << ss.str() << playerIsShooting << endl;
  if (rightPressed) {
    position.x += speed;
    if (position.x > levelWidth - m_sprite.getLocalBounds().width) {
      position.x = levelWidth - m_sprite.getLocalBounds().width;
    }
  }
  if (leftPressed) {
    position.x -= speed;
    if (position.x < 0) {
      position.x = 0;
    }
  }
  if (upPressed) {
    position.y -= speed;
    if (position.y < 0) {
      position.y = 0;
    }
  }
  if (downPressed) {
    position.y += speed;
    if (position.y > resolution.y - m_sprite.getLocalBounds().height) {
      position.y = resolution.y - m_sprite.getLocalBounds().height;
    }
  }

  setPosition(position);

}


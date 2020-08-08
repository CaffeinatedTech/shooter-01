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
  repairDelay = 1000; // Milliseconds before starting repair and between each repair tick.
  repairAmount = 5; // Amount repaired per tick.
  score = 0;

  position.x = 100;
  position.y = 900;

  isShooting = false;

  moveXAmout = 0.0f;
  moveYAmout = 0.0f;

  shootClock.restart();
  repairClock.restart();

  m_sprite.setTexture(TextureHolder::GetTexture("graphics/ship1.png"));
  m_sprite.setPosition(position);

  gunPositions[SHIPLEFT] = Vector2f(4,0);
  gunPositions[SHIPMIDDLE] = Vector2f(m_sprite.getLocalBounds().width / 2 - 7, 0);
  gunPositions[SHIPRIGHT] = Vector2f(m_sprite.getLocalBounds().width - 21, 0);

  lastGun = SHIPLEFT;
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

void Player::setDirectionPressed(DIRECTION dir, bool pressed, float amount) {
  switch (dir) {
    case LEFT:
      leftPressed = pressed;
      moveXAmout = abs(amount);
      break;
    case RIGHT:
      rightPressed = pressed;
      moveXAmout = abs(amount);
      break;
    case UP:
      upPressed = pressed;
      moveYAmout = abs(amount);
      break;
    case DOWN:
      downPressed = pressed;
      moveYAmout = abs(amount);
      break;
  }
}

void Player::setShooting(bool isShooting) {
  this->isShooting = isShooting;
  if (!isShooting) {
    this->repairClock.restart();
  }
}

bool Player::getShooting() {
  return this->isShooting;
}

Time Player::getShootClock() {
  return shootClock.getElapsedTime();
}

Time Player::getRepairClock() {
  return repairClock.getElapsedTime();
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

Vector2f Player::getShootPosition() {
  Vector2f newShootPosition = this->position;
  int randomGunPos = rand() % (3);
  newShootPosition.x += gunPositions[randomGunPos].x;
  newShootPosition.y += gunPositions[randomGunPos].y;
  return newShootPosition;
}

bool Player::takeDamage(int damage) {
  bool isPlayerDead;
  this->health -= damage;
  isPlayerDead = this->health <= 0;
  this->repairClock.restart();
  return isPlayerDead;
}

void Player::repair(int amount) {
  this->health += amount;
  if (this->health > this->maxHealth) {
    this->health = this->maxHealth;
  }
  this->repairClock.restart();
}

int Player::getRepairDelay() {
  return this->repairDelay;
}

int Player::getRepairAmount() {
  return this->repairAmount;
}

void Player::update(Time dt, Vector2f resolution, int levelWidth) {
  stringstream ss;
  ss << position.x;
  string playerIsShooting = "";
  if (getShooting()) {
    playerIsShooting = " Shooting";
    new Bullet(true, position, Bullet::LASER1);
  }
  else {

  }
  cout << ss.str() << playerIsShooting << endl;
  if (rightPressed) {
    position.x += speed * (moveXAmout / 100);
    if (position.x > levelWidth - m_sprite.getLocalBounds().width) {
      position.x = levelWidth - m_sprite.getLocalBounds().width;
    }
  }
  if (leftPressed) {
    position.x -= speed * (moveXAmout / 100);
    if (position.x < 0) {
      position.x = 0;
    }
  }
  if (upPressed) {
    position.y -= speed * (moveYAmout / 100);
    if (position.y < 0) {
      position.y = 0;
    }
  }
  if (downPressed) {
    position.y += speed * (moveYAmout / 100);
    if (position.y > resolution.y - m_sprite.getLocalBounds().height) {
      position.y = resolution.y - m_sprite.getLocalBounds().height;
    }
  }

  setPosition(position);

}


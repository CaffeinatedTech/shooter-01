//
// Created by adam on 25/7/20.
//

#include "Enemy.h"
#include "textureholder.h"

Enemy::Enemy(int type, Vector2f startPosition) {
  enemyType = type;
  position = startPosition;
  isShooting = false;

  switch (type) {
    case ENEMY1:
      m_sprite.setTexture(TextureHolder::GetTexture("graphics/enemy1.png"));
      m_sprite.rotate(180.f);
      m_sprite.setPosition(position);
      health = 10;
      speed = 5.0f;
      scorePerHit = 13;
      scorePerKill = 10000;
      canShoot = false;
      shootAtPlayer = false;
      gunPosition = Vector2f(m_sprite.getLocalBounds().width / 2 - 7, 0);
      break;
    case ENEMY2:
      m_sprite.setTexture(TextureHolder::GetTexture("graphics/enemy2.png"));
      m_sprite.rotate(180.f);
      m_sprite.setPosition(position);
      health = 15;
      speed = 5.0f;
      scorePerHit = 18;
      scorePerKill = 11000;
      canShoot = false;
      shootAtPlayer = false;
      gunPosition = Vector2f(m_sprite.getLocalBounds().width / 2 - 7, 0);
      break;
    case ENEMY3:
      m_sprite.setTexture(TextureHolder::GetTexture("graphics/enemy3.png"));
      m_sprite.rotate(180.f);
      m_sprite.setPosition(position);
      health = 15;
      speed = 5.0f;
      scorePerHit = 18;
      scorePerKill = 11000;
      canShoot = true;
      shootAtPlayer = false;
      shootSpeed = 2000;
      firstShotDelay = 500;
      gunPosition = Vector2f(m_sprite.getLocalBounds().width / 2 + 7, 0);
      break;
  }

}

Sprite Enemy::getSprite() {
  return this->m_sprite;
}

void Enemy::setPosition(Vector2f newPosition) {
  this->position = newPosition;
  this->m_sprite.setPosition(newPosition);
}

Vector2f Enemy::getPosition() {
  return this->position;
}

Vector2f Enemy::getCenter() {
  Rect<float> thisSpriteRect = this->m_sprite.getGlobalBounds();
  return Vector2f(thisSpriteRect.left + thisSpriteRect.width / 2,
                  thisSpriteRect.top + thisSpriteRect.height / 2);
  //return this->m_sprite.getPosition();
  //return this->m_sprite.getOrigin();
  //return Vector2f(0,0);
}

float Enemy::getSpeed() {
  return this->speed;
}

void Enemy::setSpeed(float newSpeed) {
  this->speed = newSpeed;
}

int Enemy::getEnemyType() {
  return this->enemyType;
}

unsigned long long Enemy::getScorePerHit() {
  return this->scorePerHit;
}

unsigned long long Enemy::getScorePerKill() {
  return this->scorePerKill;
}

void Enemy::setShooting(bool isShooting) {
  this->isShooting = isShooting;
}

bool Enemy::getShooting() {
  return this->isShooting;
}

int Enemy::getShootSpeed() {
  return this->shootSpeed;
}

void Enemy::setShootSpeed(int newShootSpeed) {
  this->shootSpeed = newShootSpeed;
}

int Enemy::getFirstShotDelay() {
  int shotDelay = this->firstShotDelay;
  this->firstShotDelay = 0;
  return shotDelay;
}

Time Enemy::getShootClock() {
  return shootClock.getElapsedTime();
}

void Enemy::restartShootClock() {
  this->shootClock.restart();
}

bool Enemy::getCanShoot() {
  return this->canShoot;
}

bool Enemy::getShootAtPlayer() {
  return this->shootAtPlayer;
}

Vector2f Enemy::getShootPosition() {
  Vector2f newShootPosition = this->position;
  newShootPosition.x -= gunPosition.x;
  newShootPosition.y -= gunPosition.y;
  return newShootPosition;
}

int Enemy::getHealth() {
  return this->health;
}

bool Enemy::decrementHealth(int amount) {
  this->health -= amount;
  isDead = this->health <= 0;
  return isDead;
}

/**
 * Apply `damage` points of damage to this enemy.
 * Calculate the amount of points to award for the damage done
 * If the enemy is killed (runs out of hitpoints) then add kill score and
 * delete the instance
 * @param damage - The amount of damage to apply
 * @return unsigned long long int score - The amount of points to award for this attack
 */
unsigned long long Enemy::takeDamage(int damage) {
  unsigned long long int score = 0;
  this->health -= damage;
  isDead = this->health <= 0;
  score += this->scorePerHit * damage;
  if (isDead) {
    score += this->scorePerKill;
  }
  return score;
}

bool Enemy::getDead() {
  return this->isDead;
}

void Enemy::setDead() {
  this->isDead = true;
}

/**
 * Spawn an instance of the death animation.
 * Call this just before destroying this enemy entity
 */
void Enemy::kill() {
  // Spawn instance of death animation
}

void Enemy::update(Time dt, Vector2f resolution) {
  // Work out movement pattern and set new position.
  Vector2f newPosition = this->position;
  newPosition.y += this->speed;
  this->setPosition(newPosition);
}


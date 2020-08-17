#include "bullet.h"
#include "textureholder.h"
#include "vec2.hpp"

Bullet::Bullet(
    bool playerFired,
    Vector2f bulletPosition,
    int newBulletType = LASER1,
    bool atPlayer = false,
    Vector2f target = Vec2(0.0f,0.0f)
        ) {
  isPlayerBullet = playerFired;
  bulletType = newBulletType;

  position.x = bulletPosition.x;
  position.y = bulletPosition.y;

  direction = Vector2f(0.0f, -1.0f);
  if (!playerFired) {
    if (atPlayer) {
      // Work out the vector to the player
      Vec2 newDirection = (target - position);
      normalize(newDirection);
      direction = newDirection;
    }
    else {
      // Just shoot down
      direction = Vector2f(0.0f, 1.0f);
    }
  }

  switch (bulletType) {
    case LASER1:
      m_sprite.setTexture(TextureHolder::GetTexture("graphics/laser_red01.png"));
      m_sprite.setPosition(position);
      speed = 10.0f;
      break;
    case LASER2:
      m_sprite.setTexture(TextureHolder::GetTexture("graphics/M484BulletCollection2.png"));
      m_sprite.setTextureRect({271,107, 11, 11});
      m_sprite.setPosition(position);
      speed = 10.0f;
      break;
    default:
      break;
  }
}

int Bullet::getBulletType() {
  return this->bulletType;
}

bool Bullet::getIsPlayerBullet() {
  return this->isPlayerBullet;
}

float Bullet::getSpeed() {
  return this->speed;
}

Vector2f Bullet::getPosition() {
  return this->position;
}

void Bullet::setPosition(Vector2f newPosition) {
  this->position = newPosition;
  this->m_sprite.setPosition(newPosition);
}

Vector2f Bullet::getDirection() {
  return this->direction;
}

Sprite Bullet::getSprite() {
  return this->m_sprite;
}

void Bullet::update(Time dt, Vector2f resolution, int levelHeight) {
  Vector2f newPosition = this->position;
  newPosition += this->getDirection() * this->getSpeed();

  this->setPosition(newPosition);
}

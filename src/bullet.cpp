#include "bullet.h"
#include "textureholder.h"

Bullet::Bullet(bool playerFired, Vector2f bulletPosition, int bulletType = LASER1) {
  isPlayerBullet = playerFired;
  bulletType = bulletType;

  position.x = bulletPosition.x;
  position.y = bulletPosition.y;

  switch (bulletType) {
    case LASER1:
      m_sprite.setTexture(TextureHolder::GetTexture("graphics/laser_red01.png"));
      m_sprite.setPosition(position);
      speed = 10.0f;
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

Sprite Bullet::getSprite() {
  return this->m_sprite;
}

void Bullet::update(Time dt, Vector2f resolution, int levelHeight) {
  Vector2f newPosition = this->position;
  if (this->isPlayerBullet) {
    newPosition.y -= this->speed;
    // Check if out of range
//    if (newPosition.y < 50) {
//      //delete this;
//      return;
//    }
  }
//  else {
//    position.y += speed;
//    // Check if out of range
//    if (position.y > levelHeight + 50) {
//      delete this;
//      return;
//    }
//  }

  this->setPosition(newPosition);
}

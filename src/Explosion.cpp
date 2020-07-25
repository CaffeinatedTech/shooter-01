#include "Explosion.h"
#include "textureholder.h"

Explosion::Explosion(Vector2f explosionPosition, int explosionType) {
  explosionType = explosionType;

  isFinished = false;
  timeSinceLastFrame = Time::Zero;

  switch (explosionType) {
    case EXPLOSION1:
      dimension = 64;
      numFrames = 16;
      currentFrame = 1;
      framesAcross = 4;
      animationSpeed = 100.f;
      m_sprite.setTexture(TextureHolder::GetTexture("graphics/explosion1.png"));
      spriteRect = IntRect(0,0,dimension,dimension);
      m_sprite.setTextureRect(spriteRect);
      position = Vector2f(explosionPosition.x - dimension / 2, explosionPosition.y - dimension / 2);
      m_sprite.setPosition(position);
      break;
  }
}

Sprite Explosion::getSprite() {
  return this->m_sprite;
}

bool Explosion::getFinished() {
  return this->isFinished;
}

Time Explosion::getTimeSinceLastFrame() {
  return this->timeSinceLastFrame;
}

void Explosion::update(Time dt) {
  // Check if enough time has passed
  timeSinceLastFrame += dt;
  if (timeSinceLastFrame.asMilliseconds() >= animationSpeed) {
    timeSinceLastFrame = Time::Zero;

    // Check if the last frame was played
    if (currentFrame == numFrames) {
      this->isFinished = true;
      return;
    }

    // Proceed to next frame
    if (spriteRect.left >= dimension * (framesAcross - 1)) {
      spriteRect.left = 0;
      spriteRect.top += dimension;
    }
    else {
      spriteRect.left += dimension;
    }
    m_sprite.setTextureRect(spriteRect);
    currentFrame++;

  }

}

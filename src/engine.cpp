//
// Created by adam on 10/5/20.
//

#include "engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() {
  // Set up all of the window, textures, sprites, sounds etc.


  resolution.x = 1920;
  resolution.y = 1080;

  levelWidth = 2500;


  window.create(VideoMode(resolution.x, resolution.y), "Shooter", Style::Default);
  window.setFramerateLimit(FPS);

  mainView.setSize(resolution);


  backgroundTexture = TextureHolder::GetTexture("graphics/stars.png");
  backgroundTexture.setRepeated(true);
  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setTextureRect(sf::IntRect(0, 0, levelWidth, 1080));


  // TODO - This is temporary to add an enemy at the start
  enemies.push_back(Enemy(Enemy::ENEMY1, Vector2f(resolution.x / 2, resolution.y / 2)));
  enemies.push_back(Enemy(Enemy::ENEMY1, Vector2f(resolution.x / 2 + 155, resolution.y / 2)));

}

void Engine::run() {
  // timing
  Clock clock;
  Time timeSinceLastUpdate = Time::Zero;

  while(window.isOpen()) {
    Time dt = clock.restart();
    timeSinceLastUpdate += dt;

    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;

      input();
      update(TimePerFrame);
    }


    draw();

  }

}

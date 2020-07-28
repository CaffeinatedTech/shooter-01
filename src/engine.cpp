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
  backgroundSprite.setPosition(0,0);
  backgroundY = 0;
  backgroundSprite.setTextureRect(sf::IntRect(0, backgroundY, levelWidth, 1080));
  backgroundSpeed = 0.5f;

  displayedScore = 0;

  scoreFont.loadFromFile("graphics/slant_regular.ttf");
  scoreText.setFont(scoreFont);
  scoreText.setString(to_string(displayedScore));
  scoreText.setCharacterSize(72);
  scoreText.setFillColor(Color::Green);
  FloatRect scoreTextBounds = scoreText.getLocalBounds();
  scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 20, 0));


  // TODO - This is temporary to add an enemy at the start
  enemies.push_back(Enemy(Enemy::ENEMY1, Vector2f(resolution.x / 2, resolution.y / 2)));
  enemies.push_back(Enemy(Enemy::ENEMY1, Vector2f(resolution.x / 2 + 155, resolution.y / 2)));

  //explosions.push_back(Explosion(enemies[0].getPosition(), Explosion::EXPLOSION1));

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

#include "engine.h"

void Engine::draw() {
  window.clear(Color::Black);

  window.setView(mainView);

  window.draw(backgroundSprite);
  window.draw(player.getSprite());
  // Draw Bullets
  for (int i = 0; i < bullets.size(); i++) {
    window.draw(bullets[i].getSprite());
  }

  // Draw Enemies
  for (int i = 0; i < enemies.size(); i++) {
    window.draw(enemies[i].getSprite());
  }

  // Draw Explosions
  for (int x = 0; x < explosions.size(); x++) {
    window.draw(explosions[x].getSprite());
  }

  // Draw Text
  window.setView(window.getDefaultView());
  window.draw(scoreText);
  window.draw(playerHealthBarFrame);
  window.draw(playerHealthBar);

  if (!waveRunning) {
    window.draw(intermissionTimer);
    window.draw(intermissionWaveLabel);
    window.draw(intermissionWaveValue);
    window.draw(intermissionWaveKillsLabel);
    window.draw(intermissionWaveKillsValue);
    window.draw(intermissionWaveScoreLabel);
    window.draw(intermissionWaveScoreValue);
  }

  if (gameOver) {
    window.draw(gameOverLabel);
    window.draw(gameOverTotalScoreLabel);
    window.draw(gameOverTotalScoreValue);
    window.draw(gameOverStartButtonLabel);
  }


  window.display();

}

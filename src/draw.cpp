#include "engine.h"

void Engine::draw() {
  window.clear(Color::Black);

  window.setView(mainView);

  window.draw(backgroundSprite);
  window.draw(player.getSprite());
  for (int i = 0; i < bullets.size(); i++) {
    window.draw(bullets[i].getSprite());
  }

  window.display();

}

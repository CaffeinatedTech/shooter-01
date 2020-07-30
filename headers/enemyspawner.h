#ifndef SHOOTER_ENEMYSPAWNER_H
#define SHOOTER_ENEMYSPAWNER_H

class EnemySpawner {
public:
    int type;
    int positionX;
    int spawnTime; // in Seconds

    EnemySpawner(int newType, int newPositionX, int newSpawnTime) {
      type = newType;
      positionX = newPositionX;
      spawnTime = newSpawnTime;
    }
};

#endif //SHOOTER_ENEMYSPAWNER_H

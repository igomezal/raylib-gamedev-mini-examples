#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) {
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    speed = 3.5f;
    
    width = (float) texture.width / maxFrames;
    height = (float) texture.height;
}

void Enemy::tick(float deltaTime) {
    if(!getAlive()) {
        return;
    }
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius) {
        velocity = Vector2{0, 0};
    }
    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec())) {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos() {
    return Vector2Subtract(worldPos, target->getWorldPos());
}
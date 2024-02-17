#include "Character.h"

#include "raymath.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth), windowHeight(winHeight) {
    width = (float) texture.width / maxFrames;
    height = (float) texture.height;
}

void Character::tick(float deltaTime) {
    if (!getAlive()) {
        return;
    }
    // movement
    if (IsKeyDown(KEY_A)) {
        velocity.x -= 1.0;
    }
    if (IsKeyDown(KEY_D)) {
        velocity.x += 1.0;
    }
    if (IsKeyDown(KEY_W)) {
        velocity.y -= 1.0;
    }
    if (IsKeyDown(KEY_S)) {
        velocity.y += 1.0;
    }
    BaseCharacter::tick(deltaTime);

    Vector2 origin = Vector2{0, 0};
    Vector2 offset = Vector2{0, 0};
    float rotation = 0.f;
    if(rightLeft > 0.f) {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollision = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    } else {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollision = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    Rectangle source = Rectangle{0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest = Rectangle{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    // DrawRectangleLines(weaponCollision.x, weaponCollision.y, weaponCollision.width, weaponCollision.height, RED);
}

Vector2 Character::getScreenPos() {
    return Vector2{
        static_cast<float>(windowWidth)/2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight)/2.0f - scale * (0.5f * height)
    };
}

void Character::takeDamage(float damage) {
    health -= damage;
    if (health <= 0.f) {
        setAlive(false);
    }
}
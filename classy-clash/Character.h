#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter {
  public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() {
      return weaponCollision;
    }
    float getHealth() {
      return health;
    }
    void takeDamage(float damage);
  private:
    int windowWidth = 0;
    int windowHeight = 0;
    Texture2D weapon = LoadTexture("./characters/weapon_sword.png");
    Rectangle weaponCollision = Rectangle{};
    float health = 100.f;
};

#endif
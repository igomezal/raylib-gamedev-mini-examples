#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter {
    public:
        BaseCharacter();
        Vector2 getWorldPos() {
            return worldPos;
        }
        virtual void tick(float deltatime);
        void undoMovement();
        Rectangle getCollisionRec();
        virtual Vector2 getScreenPos() = 0;
        bool getAlive() {
            return alive;
        }
        void setAlive(bool isAlive) {
            alive = isAlive;
        }
    protected:
        Texture2D texture = LoadTexture("./characters/knight_idle_spritesheet.png");
        Texture2D idle = LoadTexture("./characters/knight_idle_spritesheet.png");
        Texture2D run = LoadTexture("./characters/knight_run_spritesheet.png");;
        Vector2 worldPos = Vector2{0, 0};
        // 1: facing right, -1: facing left
        float rightLeft = 1.f;
        // animation
        float runningTime = 0.f;
        int frame = 0;
        int maxFrames = 6;
        float updateTime = 1.f/12.f;
        float speed = 4.f;
        float scale = 4.f;

        Vector2 worldPosLastFrame = Vector2{0,0};

        float width = 0;
        float height = 0;

        Vector2 velocity = Vector2{0,0};
    private:
        bool alive = true;
};

# endif
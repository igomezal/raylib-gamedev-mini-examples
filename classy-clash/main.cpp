#include <string>

#include "raylib.h"
#include "raymath.h"

#include "Character.h"
#include "Enemy.h"
#include "Prop.h"

const int windowHeight = 384;
const int windowWidth = 384;

int main() {
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("./nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = Vector2{0.0, 0.0};

    const float mapScale = 4.f;

    Character knight = Character{windowWidth, windowHeight};

    Enemy enemy0 = Enemy{
        Vector2{0,0},
        LoadTexture("./characters/goblin_idle_spritesheet.png"),
        LoadTexture("./characters/goblin_run_spritesheet.png")
    };
    Enemy enemy1 = Enemy{
        Vector2{530,660},
        LoadTexture("./characters/goblin_idle_spritesheet.png"),
        LoadTexture("./characters/goblin_run_spritesheet.png")
    };
    Enemy enemy2 = Enemy{
        Vector2{140,245},
        LoadTexture("./characters/slime_idle_spritesheet.png"),
        LoadTexture("./characters/slime_run_spritesheet.png")
    };
    Enemy enemy3 = Enemy{
        Vector2{0,660},
        LoadTexture("./characters/slime_idle_spritesheet.png"),
        LoadTexture("./characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[4] = {
        &enemy0,
        &enemy1,
        &enemy2,
        &enemy3
    };

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }
    
    Prop props[2] = {
        Prop{Vector2{600,300}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400,500}, LoadTexture("nature_tileset/Log.png")},
    };

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        // draw the props
        for (auto prop : props) {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive()) {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            
            EndDrawing();
            continue;
        } else {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);

            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(deltaTime);

        // Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale) {
            
            knight.undoMovement();
        }
        // check props collision
        for (auto prop : props) {
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos()))) {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(deltaTime);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(knight.getWeaponCollisionRec(), enemy->getCollisionRec())) {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}


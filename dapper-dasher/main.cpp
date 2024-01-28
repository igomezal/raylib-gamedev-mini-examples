#include "raylib.h"


struct AnimData {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight) {
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame) {
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime) {
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;

        data.frame++;
        if(data.frame > maxFrame) {
            data.frame = 0;
        }
    }

    return data;
}

int main() {
    const int windowWidth = 512;
    const int windowHeight = 380;

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    SetTargetFPS(60);

    const int gravity = 1000;

    // start - nebula
    Texture2D nebula = LoadTexture("./textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae = 6;
    AnimData nebulae[sizeOfNebulae] = {
        AnimData{
            Rectangle{0.0, 0.0, nebula.width/8, nebula.height/8},
            Vector2{windowWidth, windowHeight - nebula.height/8},
            0,
            1.0/16.0,
            0.0
        },
        AnimData{
            Rectangle{0.0, 0.0, nebula.width/8, nebula.height/8},
            Vector2{windowWidth + 300, windowHeight - nebula.height/8},
            0,
            1.0/16.0,
            0.0
        },
        AnimData{
            Rectangle{0.0, 0.0, nebula.width/8, nebula.height/8},
            Vector2{windowWidth + 600, windowHeight - nebula.height/8},
            0,
            1.0/16.0,
            0.0
        },
        AnimData{
            Rectangle{0.0, 0.0, nebula.width/8, nebula.height/8},
            Vector2{windowWidth + 900, windowHeight - nebula.height/8},
            0,
            1.0/16.0,
            0.0
        },
        AnimData{
            Rectangle{0.0, 0.0, nebula.width/8, nebula.height/8},
            Vector2{windowWidth + 1200, windowHeight - nebula.height/8},
            0,
            1.0/16.0,
            0.0
        },
        AnimData{
            Rectangle{0.0, 0.0, nebula.width/8, nebula.height/8},
            Vector2{windowWidth + 1500, windowHeight - nebula.height/8},
            0,
            1.0/16.0,
            0.0
        }
    };

    int nebulaVel = -200;
    // end - nebula

    float finishLine = nebulae[sizeOfNebulae - 1].pos.x;

    // start - scarfy
    Texture2D scarfy = LoadTexture("./textures/scarfy.png");
    AnimData scarfyData = AnimData{
        Rectangle{0, 0, scarfy.width/6, scarfy.height},
        Vector2{windowWidth/2 - scarfyData.rec.width/2, windowHeight - scarfyData.rec.height},
        0,
        // amount of time before we update the animation frame
        1.0/12.0,
        0.0
    };

    int velocity = 0;

    bool isInAir = false;

    const int jumpVelocity = -600;
    // end - scarfy

    Texture2D background = LoadTexture("./textures/far-buildings.png");
    float bgX = 0.0;

    Texture2D midground = LoadTexture("./textures/back-buildings.png");
    Texture2D foreground = LoadTexture("./textures/foreground.png");

    float mgX = 0.0;
    float fgX = 0.0;

    bool collision = false;

    while(!WindowShouldClose()) {
        // delta time (time since last frame)
        const float dT = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20 * dT;
        mgX -= 40 * dT;
        fgX -= 80 * dT;

        if(bgX <= -background.width * 2) {
            bgX = 0.0;
        }

        if(mgX <= -midground.width * 2) {
            mgX = 0.0;
        }

        if(fgX <= -foreground.width * 2) {
            fgX = 0.0;
        }

        Vector2 bg1Pos = Vector2{bgX, 0.0};
        Vector2 bg2Pos = Vector2{bgX+background.width*2, 0.0};

        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        Vector2 mg1Pos = Vector2{mgX, 0.0};
        Vector2 mg2Pos = Vector2{mgX+midground.width*2, 0.0};

        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        Vector2 fg1Pos = Vector2{fgX, 0.0};
        Vector2 fg2Pos = Vector2{fgX+foreground.width*2, 0.0};

        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        // Ground check
        if(isOnGround(scarfyData, windowHeight)) {
            velocity = 0;
            isInAir = false;
        } else {
            // apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // change velocity when jumping
        if(IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity = jumpVelocity;
        }

        for (int i = 0; i < sizeOfNebulae; i++) {
            nebulae[i].pos.x += nebulaVel * dT;
        }

        // update current position (jump)
        scarfyData.pos.y += velocity * dT;

        if(!isInAir) {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (AnimData nebula : nebulae)
        {
            float pad = 40;
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2 * pad,
                nebula.rec.height - 2 * pad
            };

            Rectangle scarfyRec {
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if(CheckCollisionRecs(nebRec, scarfyRec)) {
                collision = true;
            }
        }

        finishLine += nebulaVel * dT;

        if(collision) {
            DrawText("Game Over!", windowWidth/4, windowHeight/2, 40, WHITE);
        } else {
            // update running time
            for (int i = 0; i < sizeOfNebulae; i++)
            {
                nebulae[i] = updateAnimData(nebulae[i], dT, 7);

                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            } 

            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        if(!collision && scarfyData.pos.x >= finishLine) {
            DrawText("You Win!", windowWidth/4, windowHeight/2, 40, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(background);
    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    CloseWindow();

    return 0;
}
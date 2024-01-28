#include "raylib.h"

bool checkCollisionWithAxe(int b_axe_y, int u_circle_y, int u_axe_y, int b_circle_y, int l_axe_x, int r_circle_x, int r_axe_x, int l_circle_x) {
    return 
        (b_axe_y >= u_circle_y) &&
        (u_axe_y <= b_circle_y) &&
        (l_axe_x <= r_circle_x) &&
        (r_axe_x >= l_circle_x);
}

int main() {
    int width = 800;
    int height = 450;

    InitWindow(width, height, "Hello Window!");

    int circle_x = width/2;
    int circle_y = height/2;
    int circle_radius = 25;

    // circle edges
    int l_circle_x = circle_x - circle_radius;
    int r_circle_x = circle_x + circle_radius;
    int u_circle_y = circle_y - circle_radius;
    int b_circle_y = circle_y + circle_radius;

    int axe_x = 300;
    int axe_y = 0;
    int axe_length = 50;

    // axe edges
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;

    int direction = 10;

    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if(checkCollisionWithAxe(b_axe_y, u_circle_y, u_axe_y, b_circle_y, l_axe_x, r_circle_x, r_axe_x, l_circle_x)) {
            DrawText("Game Over!", width/2, height/2, 20, RED);
        } else {
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            l_axe_x = axe_x;
            r_axe_x = axe_x + axe_length;
            u_axe_y = axe_y;
            b_axe_y = axe_y + axe_length;

            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            axe_y += direction;
            if(axe_y+axe_length > height || axe_y < 0) {
                direction = -direction;
            }

            if(IsKeyDown(KEY_D) && circle_x < width-circle_radius) {
                circle_x += 10;
            }
            if(IsKeyDown(KEY_A) && circle_x > circle_radius) {
                circle_x -= 10;
            }
        }

        EndDrawing();
    }

    
    return 0;
}
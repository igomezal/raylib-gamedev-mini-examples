#include "raylib.h"

class Prop {
    public:
        Prop(Vector2 pos, Texture2D tex);
        void Render(Vector2 knightPos);
        Rectangle getCollisionRec(Vector2 knightPos);
    private:
        Texture2D texture = Texture2D{};
        Vector2 worldPos = Vector2{0, 0};
        float scale = 4.f;
};
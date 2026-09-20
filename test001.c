#include <raylib.h>

typedef struct
{
    const char *text;

    Vector2 position;
    Vector2 velocity;

    int fontSize;
    float hue;

    bool screaming;
} RainbowText;

int GetRainbowTextWidth(RainbowText *text)
{
    int width = 0;

    for (int i = 0; text->text[i] != '\0'; i++)
    {
        char letter[2] = { text->text[i], '\0' };
        width += MeasureText(letter, text->fontSize);
    }

    return width;
}

void UpdateRainbowText(RainbowText *text, Sound scream, Sound crash)
{
    float dt = GetFrameTime();
    int width = GetRainbowTextWidth(text);

    // Move
    text->position.x += text->velocity.x * dt;
    text->position.y += text->velocity.y * dt;

    // Shift rainbow
    text->hue += 60.0f * dt;

    if (text->hue >= 360.0f)
    {
        text->hue -= 360.0f;
    }

    // Figure out distance to the wall we're heading toward
    float distanceToWall;

    if (text->velocity.x > 0)
    {
        distanceToWall =
            GetScreenWidth() - (text->position.x + width);
    }
    else
    {
        distanceToWall = text->position.x;
    }

    // Scream when we're getting close
    if (distanceToWall < 100 && !text->screaming)
    {
        PlaySound(scream);
        text->screaming = true;
    }

    // Left/right collision
    if (text->position.x <= 0 ||
        text->position.x + width >= GetScreenWidth())
    {
        text->velocity.x *= -1;

        PlaySound(crash);
        text->screaming = false;
    }

    // Top/bottom collision
    if (text->position.y <= 0 ||
        text->position.y + text->fontSize >= GetScreenHeight())
    {
        text->velocity.y *= -1;

        PlaySound(crash);
        text->screaming = false;
    }
}

void DrawRainbowText(RainbowText *text)
{
    float x = text->position.x;

    for (int i = 0; text->text[i] != '\0'; i++)
    {
        float letterHue = text->hue + i * 20.0f;

        while (letterHue >= 360.0f)
        {
            letterHue -= 360.0f;
        }

        Color color = ColorFromHSV(letterHue, 1.0f, 1.0f);

        char letter[2] = { text->text[i], '\0' };

        DrawText(
            letter,
            x,
            text->position.y,
            text->fontSize,
            color
        );

        x += MeasureText(letter, text->fontSize);
    }
}

int main(void)
{
    InitWindow(800, 600, "Professional Software");
    InitAudioDevice();
    Image icon = LoadImage("icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    SetTargetFPS(60);

    Sound scream = LoadSound("sounds/scream.mp3");
    Sound crash = LoadSound("sounds/crash.mp3");

    RainbowText test = {
        "THIS IS A TEST",
        {100.0f, 100.0f},
        {150.0f, 100.0f},
        30,
        0.0f,
        false
    };

    while (!WindowShouldClose())
    {
        UpdateRainbowText(&test, scream, crash);

        BeginDrawing();

        ClearBackground(BLACK);
        DrawRainbowText(&test);

        EndDrawing();
    }

    UnloadSound(scream);
    UnloadSound(crash);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
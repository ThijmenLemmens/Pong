#include <iostream>
#include "random"
#include "raylib.h"

const int width {800};
const int height {600};

const int x_1 {20};
int y_1 {200};
const int width_1 {20};

const int x_2 {760};
int y_2 {200};
const int width_2 {20};

int y_3 {height / 2};
int x_3 {width / 2};
const int size_bal {10};
int speed {2};

bool won = false;
bool debug = false;
unsigned int points_1 {0};
unsigned int points_2 {0};

std::random_device random1;
std::mt19937 gen1(random1());
std::uniform_int_distribution<> random_number_1(-10, 10);
std::uniform_int_distribution<> random_number_2(-10, 10);

int vx = random_number_1(gen1);
int vy = random_number_2(gen1);

void check_border() {
    if (y_1 < 1) y_1 = 1;
    if (y_1 > 450) y_1 = 450;
    if (y_2 < 1) y_2 = 1;
    if (y_2 > 450) y_2 = 450;
}

void reset(bool points_reset) {
    std::random_device random;
    std::mt19937 gen(random());
    std::uniform_int_distribution<> random_number(0, 1);

    if (points_reset) {
        points_1 = 0;
        points_2 = 0;
    }
    if (random_number(gen) == 1) {
        speed -= 5;
    } else {
        speed += 5;
    }
    x_3 = width / 2;
    y_3 = height / 2;
}

void score() {
    if (x_3 < 0) {
        points_2++;
        reset(false);
    }
    if (x_3 > width) {
        points_1++;
        reset(false);
    }
}

void debug_menu() {
    if (debug) {
        DrawFPS(10, 10);
        DrawText(TextFormat("FrameTime %03i", GetFrameTime()), 100, 10, 20, LIGHTGRAY);
        DrawText(TextFormat("X: %03i", x_3), 350, 10, 20, LIGHTGRAY);
        DrawText(TextFormat("X: %03i", y_3), 400, 10, 20, LIGHTGRAY);
    }
}

void controls() {
    if (!won) {
        if (IsKeyDown(KEY_W)) y_1 -= 10;
        if (IsKeyDown(KEY_S)) y_1 += 10;
        if (IsKeyDown(KEY_UP)) y_2 -= 10;
        if (IsKeyDown(KEY_DOWN)) y_2 += 10;
    }
    if (IsKeyDown(KEY_R)) reset(true);
    if (IsKeyDown(KEY_F1)) {
        if (!debug) {
            debug = true;
        } else {
            debug = false;
        }
    }
}

void move_ball() {
    x_3 = x_3 + vx;
    y_3 = y_3 + vy;

    if (y_3 < 0 || y_3 > height) {
        vy=-vy;
        y_3=y_3+vy;
    }

    if (x_1 < x_3 + size_bal &&
        x_1 + width_1 > x_3 &&
        y_1 < y_3 + size_bal &&
        150 + y_1 > y_3) {
        vx=-vx;
        x_3 = x_3 + vx;
    }
    if (x_2 < x_3 + size_bal &&
        x_2 + width_2 > x_3 &&
        y_2 < y_3 + size_bal &&
        150 + y_2 > y_3) {
        vx=-vx;
        x_3 = x_3 + vx;
    }
}

void game_loop() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText(TextFormat("%03i", points_1), 200, 50, 50, LIGHTGRAY);
        DrawText(TextFormat("%03i", points_2), 500, 50, 50, LIGHTGRAY);

        debug_menu();
        score();
        check_border();
        controls();
        move_ball();
        DrawRectangle(x_1, y_1, 20, 150, BLACK);
        DrawRectangle(x_2, y_2, 20, 150, BLACK);
        DrawCircle(x_3, y_3, size_bal, BLACK);
        EndDrawing();
    }
}

int main() {

    SetTargetFPS(60);
    InitWindow(width, height, "Pong");

    game_loop();

    CloseWindow();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}


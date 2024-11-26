#ifndef SNAKE_H
#define SNAKE_H

#include <matrix.h>
#include <REG51.h>

sbit UE = P3^2;
sbit SHITA = P3^3;
sbit HIDARI = P3^0;
sbit MIGI = P3^1;

unsigned char snake[64];
unsigned char food;
unsigned char direction;
unsigned char snake_length;
unsigned char display_buffer[8];
unsigned char last_direction;
unsigned int Speed = 20;

void init_game()
{
    unsigned char i;
    for (i = 0; i < 64; i++)
    {
        snake[i] = 0;
    }
    snake[0] = 28;
    snake[1] = 27;
    food = 10;
    direction = 3;
    last_direction = 3;
    snake_length = 2;
}
void showGameOverScreen();
void check_direction()
{
    unsigned char new_direction = last_direction;

    if (UE == 0 && last_direction != 1) { new_direction = 0; }
    if (SHITA == 0 && last_direction != 0) { new_direction = 1; }
    if (HIDARI == 0 && last_direction != 3) { new_direction = 2; }
    if (MIGI == 0 && last_direction != 2) { new_direction = 3; }

    if (new_direction != last_direction)
    {
        direction = new_direction;
        last_direction = new_direction;
    }
}

void update_snake()
{
    unsigned char i;
    for (i = snake_length; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    switch (direction)
    {
        case 0: snake[0] = (snake[0] - 8 + 64) % 64; break;
        case 1: snake[0] = (snake[0] + 8) % 64; break;
        case 2: snake[0] = (snake[0] % 8 == 0) ? snake[0] + 7 : snake[0] - 1; break;
        case 3: snake[0] = (snake[0] % 8 == 7) ? snake[0] - 7 : snake[0] + 1; break;
    }
}

void generate_new_food()
{
    unsigned char i;
    unsigned char is_valid;
    do
    {
        is_valid = 1;
        food = (food + 17) % 64;
        for (i = 0; i < snake_length; i++)
        {
            if (food == snake[i]) { is_valid = 0; break; }
        }
    } while (!is_valid);
}

void check_collision() {
    unsigned char i;
    for (i = 1; i < snake_length; i++) {
        if (snake[0] == snake[i]) {
            showGameOverScreen();  // Game Over
            return;
        }
    }
    if (snake[0] == food) {
        if (snake_length < 63) {
            snake_length++;
        }
        generate_new_food();
    }
}

void update_display_buffer()
{
    unsigned char i, row, col;
    for (i = 0; i < 8; i++) { display_buffer[i] = 0x00; }

    for (i = 0; i < snake_length; i++)
    {
        row = snake[i] / 8;
        col = snake[i] % 8;
        display_buffer[row] |= (1 << col);
    }

    row = food / 8;
    col = food % 8;
    display_buffer[row] |= (1 << col);
}

void Running_Game()
{
    check_direction();
    update_snake();
    check_collision();
    update_display_buffer();
}

#endif

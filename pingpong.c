#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#define PADDLE_HEIGHT 4
#define BALL_SPEED 50000
#define PADDLE_SPEED 1

typedef struct {
    int x, y;
    int dx, dy;
} Ball;

typedef struct {
    int x, y;
    int height;
} Paddle;

void init_game(Ball *ball, Paddle *left_paddle, Paddle *right_paddle, int *score_left, int *score_right);
void draw_paddle(Paddle paddle);
void draw_ball(Ball ball);
void move_ball(Ball *ball, Paddle left_paddle, Paddle right_paddle, int *score_left, int *score_right);
void move_paddle(Paddle *paddle, int direction, int max_y);

int main() {
    Ball ball;
    Paddle left_paddle, right_paddle;
    int score_left = 0, score_right = 0;
    int ch;
    int max_y, max_x;
    
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    
    getmaxyx(stdscr, max_y, max_x);
    
    init_game(&ball, &left_paddle, &right_paddle, &score_left, &score_right);
    
    // Game loop
    while (1) {
        clear();
        
        // Draw game elements
        box(stdscr, 0, 0);
        mvprintw(1, max_x/2 - 10, "Score: %d - %d", score_left, score_right);
        mvprintw(max_y - 2, 2, "Controls: W/S (left) | Up/Down (right) | Q to quit");
        
        draw_paddle(left_paddle);
        draw_paddle(right_paddle);
        draw_ball(ball);
        
        refresh();
        
        // Handle input
        ch = getch();
        if (ch == 'q' || ch == 'Q') {
            break;
        } else if (ch == 'w' || ch == 'W') {
            move_paddle(&left_paddle, -PADDLE_SPEED, max_y);
        } else if (ch == 's' || ch == 'S') {
            move_paddle(&left_paddle, PADDLE_SPEED, max_y);
        } else if (ch == KEY_UP) {
            move_paddle(&right_paddle, -PADDLE_SPEED, max_y);
        } else if (ch == KEY_DOWN) {
            move_paddle(&right_paddle, PADDLE_SPEED, max_y);
        }
        
        // Move ball
        move_ball(&ball, left_paddle, right_paddle, &score_left, &score_right);
        
        usleep(BALL_SPEED);
    }
    
    // Clean up
    endwin();
    printf("Final Score: %d - %d\n", score_left, score_right);
    printf("Thanks for playing!\n");
    
    return 0;
}

void init_game(Ball *ball, Paddle *left_paddle, Paddle *right_paddle, int *score_left, int *score_right) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Initialize ball in center
    ball->x = max_x / 2;
    ball->y = max_y / 2;
    
    // Random initial direction
    srand(time(NULL));
    ball->dx = (rand() % 2 == 0) ? 1 : -1;
    ball->dy = (rand() % 2 == 0) ? 1 : -1;
    
    // Initialize paddles
    left_paddle->x = 2;
    left_paddle->y = max_y / 2 - PADDLE_HEIGHT / 2;
    left_paddle->height = PADDLE_HEIGHT;
    
    right_paddle->x = max_x - 3;
    right_paddle->y = max_y / 2 - PADDLE_HEIGHT / 2;
    right_paddle->height = PADDLE_HEIGHT;
    
    *score_left = 0;
    *score_right = 0;
}

void draw_paddle(Paddle paddle) {
    for (int i = 0; i < paddle.height; i++) {
        mvaddch(paddle.y + i, paddle.x, '|');
    }
}

void draw_ball(Ball ball) {
    mvaddch(ball.y, ball.x, 'O');
}

void move_ball(Ball *ball, Paddle left_paddle, Paddle right_paddle, int *score_left, int *score_right) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // Update ball position
    ball->x += ball->dx;
    ball->y += ball->dy;
    
    // Check collision with top and bottom walls
    if (ball->y <= 1 || ball->y >= max_y - 2) {
        ball->dy = -ball->dy;
    }
    
    // Check collision with left paddle
    if (ball->x == left_paddle.x + 1) {
        if (ball->y >= left_paddle.y && ball->y < left_paddle.y + left_paddle.height) {
            ball->dx = -ball->dx;
        }
    }
    
    // Check collision with right paddle
    if (ball->x == right_paddle.x - 1) {
        if (ball->y >= right_paddle.y && ball->y < right_paddle.y + right_paddle.height) {
            ball->dx = -ball->dx;
        }
    }
    
    // Check if ball went out of bounds (scoring)
    if (ball->x <= 1) {
        (*score_right)++;
        ball->x = max_x / 2;
        ball->y = max_y / 2;
        ball->dx = 1;
    } else if (ball->x >= max_x - 2) {
        (*score_left)++;
        ball->x = max_x / 2;
        ball->y = max_y / 2;
        ball->dx = -1;
    }
}

void move_paddle(Paddle *paddle, int direction, int max_y) {
    paddle->y += direction;
    
    // Keep paddle within bounds
    if (paddle->y < 2) {
        paddle->y = 2;
    }
    if (paddle->y + paddle->height > max_y - 2) {
        paddle->y = max_y - 2 - paddle->height;
    }
}

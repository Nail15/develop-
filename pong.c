#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define MOVERIGHTUP 0
#define MOVERIGHTDOWN 1
#define MOVELEFTDOWN 2
#define MOVELEFTUP 3

void game_loop(void);
void init (void);
void render_field(void);
void draw_racket(signed char, signed char);
void draw_ball(signed char);
void draw_scores(void);
void read_key(signed char);
void choose_dir(void);

signed char field[24][80],
raws, cols,
ball_x=40, ball_y=12,
racket1_posY=12, racket2_posY=12,
player1score=0, player2score=0,
direction=MOVELEFTDOWN,
key;

int main() {
    game_loop();
    return 0;
}

void game_loop() {
    while (TRUE) {
        init();
        draw_racket(racket1_posY, racket2_posY);
        choose_dir();
        draw_ball(direction);
        draw_scores();
        render_field();
        key=getchar();
        read_key(key);
    }
}
void render_field (void) {
    for (raws = 0; raws <= 23; raws++) {
        for (cols = 0; cols <= 79; cols++) {
            printf("%c", field[raws][cols]);
        }
        printf("\n");
    }
}
void draw_racket(signed char racket1_posY, signed char racket2_posY) {
    int count = 0;
    while (count < 3) {
        field[racket1_posY][0] = '|';
        field[racket2_posY][79] = '|';
        ++racket1_posY;
        ++racket2_posY;
        ++count;
    }
}
void draw_ball(signed char direction) {
    if (direction == MOVERIGHTUP) {
        ++ball_x;
        --ball_y;
    }
    if (direction == MOVERIGHTDOWN) {
        ++ball_x;
        ++ball_y;
    }
   if (direction == MOVELEFTUP) {
        --ball_x;
        --ball_y;
    }
   if (direction == MOVELEFTDOWN) {
        --ball_x;
        ++ball_y;
    }
    field[ball_y][ball_x]='*';
}
void choose_dir() {
    if (ball_x == 1 || ball_x == 78) {
        if (ball_x == 1) {
            if (racket1_posY == ball_y || racket1_posY + 1 == ball_y || racket1_posY + 2 == ball_y) {
                if (direction==MOVELEFTDOWN) {
                    direction=MOVERIGHTDOWN;
                }
                if (direction==MOVELEFTUP) {
                    direction=MOVERIGHTUP;
                }
            }
            else {
                if (player2score == 20) {
                    printf("                              PLAYER TWO WON!!!");
                    exit(0);
                }
                else {
                    player2score += 1;
                    ball_x = 40;
                    ball_y = 12;
                    direction=MOVELEFTDOWN;
                }
            }
        }
        else if (ball_x == 78) {
            if (racket2_posY == ball_y || racket2_posY + 1 == ball_y || racket2_posY + 2 == ball_y) {
                if (direction == MOVERIGHTDOWN) {
                    direction = MOVELEFTDOWN;
                }
                if (direction == MOVERIGHTUP) {
                    direction = MOVELEFTUP;
                }
            }
            else {
                if (player1score == 20) {
                    printf("                              PLAYER ONE WON!!!");
                    exit(0);
                }
                else {
                    player1score += 1;
                    ball_x = 40;
                    ball_y = 12;
                    direction=MOVERIGHTUP;
                }
            }
        }
    }
    else {
     if (direction == MOVERIGHTUP && ball_y == 0) {
         direction = MOVERIGHTDOWN;
     }
     if (direction == MOVERIGHTDOWN && ball_y == 23) {
         direction = MOVERIGHTUP;
     }
     if (direction == MOVELEFTUP && ball_y == 0) {
         direction = MOVELEFTDOWN;
     }
     if (direction == MOVELEFTDOWN && ball_y == 23) {
         direction = MOVELEFTUP;
     }
    }
}
void read_key(signed char key) {
    if (key == 'a' || key == 'A')
        if (racket1_posY - 2 != 0) {
            racket1_posY -= 1;
        }
    if (key == 'z' || key == 'Z')
        if (racket1_posY + 2 != 23) {
            racket1_posY += 1;
        }
    if (key == 'k' || key == 'K')
        if (racket2_posY - 2 != 0) {
            racket2_posY -= 1;
        }
    if (key=='m' || key=='M')
        if (racket2_posY + 2 != 23) {
            racket2_posY += 1;
        }
}
void init (void) {
    for (raws = 0; raws <= 23; raws ++) {
        for (cols = 0; cols <= 79; cols ++) {
            field[raws][cols]=' ';
        }
    }
}
void draw_scores() {
    printf("%25d               SCORES             %d", player1score, player2score);
}






 










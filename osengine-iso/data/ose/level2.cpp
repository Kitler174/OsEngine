#include "data/struct/enemies/enemy.h"
#include "data/struct/characters/hero.h"
#include "../../h/keys.h"
#include "../../h/draw.h"

func hero_move(h hero){
    if (key[A]){
        hero.x -= speed;
    }
    if (key[D]){
        hero.x += speed;
    }
    if (key[S]){
        hero.y += speed;
    }
    if (key[W]){
        hero.y -= speed;
    }
}
func enemy_ai(e enemy, h hero){
    int x_r = enemy.x - hero.x;
    int y_r = enemy.y - hero.y;
    if (x_r < 0){
        enemy.x += enemy.speed;
    }
    else{
        enemy.x -= enemy.speed;
    }
    if (y_r < 0){
        enemy.y += enemy.speed;
    }
    else{
        enemy.y -= enemy.speed;
    }
}

func draw_text(str text, int x, int y){
    draw_text_8x8(text,x,y);
}

int score = 0;
start_loop{
    drawSprite(h.Ragnar);
    hero_move(h.Ragnar);
    enemy_ai(e.slime, h.Ragnar);
    draw_text("Score"+str(score), 20, 20);

}

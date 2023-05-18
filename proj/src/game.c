#include "game.h"
#include "our_framework/framework_essencials.h"
#include "draw/draw.h"
#include "xpm/test.xpm"
#include "xpm/teapot.xpm"

int time_0;
bool menu_state = true;

int x = 10;
int y = 10;
int enemy_x = 10;
int enemy_y = 10;
position enemy_pos;
int i = 0;

position corners[13] = {{10, 60}, {710, 60}, {710, 210}, {360, 210}, {360, 360}, {210, 360}, {210, 210}, {60, 210}, {60, 510}, {510, 510}, {510, 360}, {660, 360}, {660, 510}};
char directions[13] = {'r', 'd', 'l', 'd', 'l', 'u', 'l', 'd', 'r', 'u', 'r', 'd', 'r'};
char direction = 'd';

bool game_clock = false;

int before(){
  turn_on_graphics();
  time_0 = get_time_counter();

  enemy_pos.x = enemy_x;
  enemy_pos.y = enemy_y;

  return 0;
}

void game(){
  clear_screen();
  verify_mouse_limits(0, 800-10, 0, 600-10);

  if(menu_state) {
    draw_rectangle(250, 190, 300, 50, 0x00e600);
    draw_rectangle(250, 290, 300, 50, 0x86592d);

    if(is_key_pressed(ESC, true)){
      quit();
    }

    if(is_key_pressed(ENTER, false)){
      menu_state = false;
    }

    if(get_mouse_position().x >= 250 && get_mouse_position().x <= 550 && get_mouse_position().y >= 190 && get_mouse_position().y <= 240 && is_lb_pressed()){
      menu_state = false;
    }

    //cursor
    draw_rectangle(get_mouse_position().x, get_mouse_position().y, 10, 10, 0xFF0000);
  } 

  else {

    if(is_key_pressed(ESC, true)){
      quit();
    }
    if(is_key_pressed(' ', false)){
      game_clock = true;
    }

    if(is_key_pressed('a', false)){
      x-=6;
    }
    if(is_key_pressed('d', false)){
      x+=6;
    }
    if(is_key_pressed('w', false)){
      y-=3;
    }
    if(is_key_pressed('s', false)){
      y+=3;
    }

    if (x > 800-30)
      x = 800-30; 
    if (x < 0)
      x = 0;
    if (y > 600-30)
      y = 600-30;
    if (y < 0)
      y = 0;

    if(game_clock) {

      if(direction == 'r') {
        enemy_pos.x += 2;
      }
      if(direction == 'l') {
        enemy_pos.x -= 2;
      }
      if(direction == 'u') {
        enemy_pos.y -= 2;
      }
      if(direction == 'd') {
        enemy_pos.y += 2;
      }
          
      if(enemy_pos.x == corners[i].x && enemy_pos.y == corners[i].y) {
          direction = directions[i];
          i++;
        }

    }

    /* Draw Background */
    draw_rectangle(0, 0, 800, 600, 0x86592d);

    char map[12][16] = {
      {' ','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
      {'#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#'},
      {'#','#','#','#','#','#','#','#','#','#','#','#','#','#',' ','#'},
      {'#',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
      {'#',' ','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#'},
      {'#',' ','#','#',' ','#','#',' ','#','#','#','#','#','#','#','#'},
      {'#',' ','#','#',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','#'},
      {'#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#'},
      {'#',' ','#','#','#','#','#','#','#','#',' ','#','#',' ','#','#'},
      {'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' '},
      {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    };

    draw_map(map);

    //Draw player
    draw_rectangle(x, y, 30, 30, 0xFFFF00);

    

    //Draw enemies
    draw_rectangle(enemy_pos.x, enemy_pos.y, 30, 30, 0x0000FF);
    draw_xpm(enemy_pos.x, enemy_pos.y, et_xpm, 0x000000);
  }
}

int after(){
  return 0;
}

/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : scene_dims {708, 708},
          row_dims {708, (scene_dims.height/12)},
          column_dims {(scene_dims.width/12), 708},
          river_rect {0, row_dims.height, scene_dims.width, row_dims.height * 4},
          road_rect {0, row_dims.height * 6, scene_dims.width, row_dims.height * 5},
          barrier_rect {0, row_dims.height * 5, scene_dims.width, row_dims.height},
          end_rect {0, 0, scene_dims.width, row_dims.height},
          start_rect {0, row_dims.height * 11, scene_dims.width, row_dims.height},
          car_dims {(int)(.85 * column_dims.width), (int)(.85 * row_dims.height)},
          log_dims {(int)(3 * column_dims.width), (int)(row_dims.height * .95)},
          frog_dims {(int)(column_dims.width * .75), (int)(row_dims.height * .75)},
          lily_pad_dims {(int)(column_dims.width * .8), (int)(row_dims.height * .8)}
{ }

// Computes how large each brick can be (in a given dimension), given the
// total number of pixels available in that dimension, the number of bricks
// in that dimensions, and the number of space pixels to leave in between.
//
// PRECONDITION: divisor > 0
/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct to hold configuration parameters. You should try different
// values to ensure that your model and UI adjust appropriately. You can do this
// by creating an instance and then assigning its parameters before constructing
// a `Model`:
//
//     Game_config config;
//     config.brick_cols = 15;
//     config.ball_radius *= 2;
//     Model model(config);
//

#pragma once

#include <ge211.hxx>


struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The dimensions of the whole window:
    ge211::Dims<int> scene_dims;

    ge211::Dims<int> row_dims;

    ge211::Dims<int> column_dims;

    ge211::Rect<int> river_rect;

    ge211::Rect<int> road_rect;

    ge211::Rect<int> barrier_rect;

    ge211::Rect<int> end_rect;

    ge211::Rect<int> start_rect;

    ge211::Dims<int> car_dims;

    ge211::Dims<int> log_dims;

    ge211::Dims<int> frog_dims;

    ge211::Dims<int> lily_pad_dims;

};


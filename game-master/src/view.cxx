#include "view.hxx"
#include "model.hxx"

using Sprite_set = ge211::Sprite_set;
using Color = ge211::Color;

static int const column_width = (int) (900 / 12);
static int const row_height = (int) (900 / 12);

View::View(Model const& model)
        : model_(model),
          frog_sprite_(model_.config_.frog_dims,
                       Color::medium_green()),
          car_sprite_(model_.config_.car_dims, Color::medium_yellow()),
          road_sprite_({(int)(column_width * 12), (int)(row_height * 4)},
                       Color::from_rgba(130, 130, 130, 1.0)),
          log_sprite_(model_.config_.log_dims,
                      Color::black()),
          river_sprite_({(int)(column_width * 12), (int)(row_height * 4)},
                        Color::medium_cyan()),
          barrier_sprite_({(int)(column_width * 12), (int)(row_height)},
                          Color::medium_yellow()),
          end_sprite_({(int)(column_width * 12), (int)(row_height)},
                      Color::medium_yellow())
{ }

/*
 * end zone
 * water
 * water
 * water
 * water
 * barrier
 * road
 * road
 * road
 * road
 * road
 * start
 */

void
View::draw(ge211::Sprite_set& sprites) {
    for (int i = 0; i < model_.config_.scene_dims.width; i += column_width) {
        if (i == 0) {
            sprites.add_sprite(end_sprite_, {0, i}, 1);
        } else if (i == column_width) {
            sprites.add_sprite(river_sprite_, {0, i}, 0);
        } else if (i == (5 * column_width)) {
            sprites.add_sprite(barrier_sprite_, {0, i}, 0);
        } else if (i == (6 * column_width)) {
            sprites.add_sprite(road_sprite_, {0, i}, 0);
        } else if (i == (11 * column_width)) {
            sprites.add_sprite(barrier_sprite_, {0, i}, 0);
        }
    }
    for (std::pair<Rectangle, Velocity > cars : model_.cars()){
        sprites.add_sprite(car_sprite_, {cars.first.x, cars.first.y}, 3);
    }
    for (std::pair<Rectangle, Velocity > logs: model_.logs()){
        sprites.add_sprite(log_sprite_, {logs.first.x, logs.first.y}, 3);
    }
    sprites.add_sprite(frog_sprite_, {(int)(model_.frog().top_left.x),(int)(model_.frog().top_left.y)}, 5);
}

View::Dimensions
View::initial_window_dimensions() const
{
    return {900, 900};
}

std::string
View::initial_window_title() const
{
    return "Frogger";
}

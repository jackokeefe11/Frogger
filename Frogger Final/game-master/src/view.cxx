#include "view.hxx"
#include "model.hxx"

using Sprite_set = ge211::Sprite_set;
using Color = ge211::Color;

static int const column_width = (int) (708 / 12);
static int const row_height = (int) (708 / 12);

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
                      Color::medium_yellow()),
          lives_left_text_("Lives", ge211::Font("sans.ttf", 30)),
          lives_left_indicators_({(int)(column_width * .1), (int)(column_width * .1)}, Color::medium_red()),
          end_zone_({(int)(120), (int)(row_height)},
                    Color::medium_cyan()),
          lily_pad_sprite_({(int)(model_.config_.lily_pad_dims.width), (int)(model_.config_.lily_pad_dims.height)}, Color::medium_green())
          //level_lost_sprite_({(int)(model_.config_.scene_dims.width), (int)(model_.config_.scene_dims.height)})
{ }

void
View::draw(ge211::Sprite_set& sprites) {
    for (int i = 0; i < model_.config_.scene_dims.width; i += column_width) {
        if (i == 0) {
            sprites.add_sprite(end_sprite_, {0, i}, 1);
            for(int j = 0; j < 3; j++) {
                sprites.add_sprite(end_zone_, {(int) ((.1555 * model_.config_.column_dims.height) + (((.133 * model_.config_.column_dims.height) * j) + ((.1555 * model_.config_.column_dims.height) * j))), 0}, 2);
            }
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
    sprites.add_sprite(frog_sprite_, {(int)(model_.frog().top_left.x),(int)(model_.frog().top_left.y)}, 4);
    sprites.add_sprite(lives_left_text_, {model_.config_.scene_dims.width - 75, 10}, 7);
    for (int i = 1; i <= model_.lives_left(); i++){
        sprites.add_sprite(lives_left_indicators_, {(model_.config_.scene_dims.width - 75) + (i * (int)(.2 * row_height)), 10}, 8);
    }
    for (bool den : model_.frog().dens_reached) {
        if (den) {
            sprites.add_sprite(frog_sprite_, {130,0}, 4);
        }
    }
    for (Rectangle lily_pads : model_.lily_pads()){
        sprites.add_sprite(lily_pad_sprite_, {lily_pads.x, lily_pads.y}, 2);
    }
}

View::Dimensions
View::initial_window_dimensions() const
{
    return {708, 708};
}

std::string
View::initial_window_title() const
{
    return "Frogger";
}

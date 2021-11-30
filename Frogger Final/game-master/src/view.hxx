#pragma once

#include <ge211.hxx>

class Model;

class View
{
public:
    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    Dimensions initial_window_dimensions() const;

    void draw(ge211::Sprite_set& set);

    std::string initial_window_title() const;

protected:
    Model const& model_;
    ge211::sprites::Rectangle_sprite const frog_sprite_;
    ge211::sprites::Rectangle_sprite const car_sprite_;
    ge211::sprites::Rectangle_sprite const road_sprite_;
    ge211::sprites::Rectangle_sprite const log_sprite_;
    ge211::sprites::Rectangle_sprite const river_sprite_;
    ge211::sprites::Rectangle_sprite const barrier_sprite_;
    ge211::sprites::Rectangle_sprite const end_sprite_;
    ge211::sprites::Text_sprite const lives_left_text_;
    ge211::sprites::Rectangle_sprite const lives_left_indicators_;
    ge211::sprites::Rectangle_sprite const end_zone_;
    ge211::sprites::Rectangle_sprite const lily_pad_sprite_;
};

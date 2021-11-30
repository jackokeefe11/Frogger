#pragma once

#include "view.hxx"

#include <ge211.hxx>

struct Controller : ge211::Abstract_game
{
    explicit Controller(Model&);

    void on_key(ge211::Key) override;

    void on_frame(double dt) override;

    ge211::Dims<int> initial_window_dimensions() const override;

    void draw(ge211::Sprite_set&) override;

    Model& model_;

    View view_;
};





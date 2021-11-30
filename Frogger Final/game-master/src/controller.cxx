#include "controller.hxx"
#include "model.hxx"

Controller::Controller(Model& model)
        : model_(model),
          view_(model)
{ }

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }

    else if (key == ge211::Key::code(' ')) {
        model_.launch();
    }

    else if (key == ge211::Key::up()) {
        model_.move_frog('u');
    }

    else if (key == ge211::Key::down()) {
        model_.move_frog('d');
    }

    else if (key == ge211::Key::left()) {
        model_.move_frog('l');
    }

    else if (key == ge211::Key::right()) {
        model_.move_frog('r');
    }
}

void
Controller::on_frame(double dt){
    model_.update(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

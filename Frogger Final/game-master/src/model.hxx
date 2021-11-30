#pragma once

#include "game_config.hxx"
#include "frog.hxx"

class Model
{
public:
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Rectangle = ge211::Rect<int>;

    using Velocity = ge211::Dims<float>;

    explicit Model(Game_config const& = Game_config());

    int lives_left() const{
        return lives_left_;
    }

    bool is_game_over() const
    {
        return lives_left() == 0;
    }

    Frog frog() const{
        return frog_;
    }

    std::vector<std::pair<Rectangle, Velocity>> cars() const{
        return cars_;
    }

    std::vector<std::pair<Rectangle, Velocity>> logs() const{
        return logs_;
    }

    std::vector<Rectangle> end_zone() const {
        return end_zone_;
    }

    std::vector<Rectangle> lily_pads() const{
        return lily_pads_;
    }

    void launch();

    Game_config const config_;

    void update(double dt);

    void move_frog(char);

    bool is_frog_alive();

protected:

    int lives_left_;

    std::vector<std::pair<Rectangle, Velocity>> cars_;

    Rectangle river_positions_;

    std::vector<std::pair<Rectangle, Velocity>> logs_;

    Frog frog_;

    int num_dens_reached;

    std::vector<Rectangle> end_zone_;

    std::vector<Rectangle> lily_pads_;

    double time_;

    void move_cars(std::vector<std::pair<Rectangle, Velocity>>& cars_, double dt);

    void move_logs(std::vector<std::pair<Rectangle, Velocity>>& logs_, double dt);

    void move_lily_pads(double, double);
};



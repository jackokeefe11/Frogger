#include "model.hxx"
#include <cstdlib>

Model::Model(Game_config const& config)
        : config_(config),
          frog_(config)
{
    num_dens_reached = 0;
    lives_left_ = 3;
    Rectangle car;
    Rectangle car_2;
    Velocity v = {100,0};
    double r1;
    double r2;
    for(int i = 6; i < 11; i++) {
        r1 = ((double) rand() / (RAND_MAX));
        r2 = ((double) rand() / (RAND_MAX));
        while (abs(r1 - r2) < .17) {
            r2 = ((double) rand() / (RAND_MAX));
        }
        car = {(int) (r1 * config_.scene_dims.width), (int) (config_.row_dims.height * (i + .08)), config_.car_dims.width, config_.car_dims.height};
        car_2 = {(int) (r2 * config_.scene_dims.width), (int) (config_.row_dims.height * (i + .08)), config_.car_dims.width, config_.car_dims.height};
        cars_.emplace_back(car, v);
        cars_.emplace_back(car_2, v);
        v.width *= -1;
    }

    Rectangle log;
    Rectangle log_2;
    for(int i = 1; i < 5; i++) {
        r1 = ((double) rand() / (RAND_MAX));
        r2 = ((double) rand() / (RAND_MAX));
        while (abs(r1 - r2) < .4) {
            r2 = ((double) rand() / (RAND_MAX));
        }
        log = {(int) (r1 * config_.scene_dims.width), (int) (config_.row_dims.height * (i + .05)), config_.log_dims.width, config_.log_dims.height};
        log_2 = {(int) (r2 * config_.scene_dims.width), (int) (config_.row_dims.height * (i + .05)), config_.log_dims.width, config_.log_dims.height};
        logs_.emplace_back(log, v);
        logs_.emplace_back(log_2, v);
        v.width *= -1;
    }

    Rectangle rec_end_zone;
    for(int i = 0; i < 3; i++) {
        //rec_end_zone = {(140 + ((120 * i) + (140 * i))), 0, (int)(120), (int)(config_.row_dims.height)};
        rec_end_zone = {(int) ((.1555 * config_.column_dims.height) + (((.133 * config_.column_dims.height) * i) + ((.1555 * config_.column_dims.height) * i))), 0, (int) ((.133 * config_.column_dims.height) * i), (int)(config_.row_dims.height)};
        end_zone_.push_back(rec_end_zone);
    }

    Rectangle lily_pad;
    for (int i = 1; i < 5; i++) {
        r1 = (int) (((double) rand() / (RAND_MAX)) * 12);
        lily_pad = {(int) (r1 * config_.column_dims.width), (int) (config_.row_dims.height * (i + .1)), config_.lily_pad_dims.width, config_.lily_pad_dims.height};
        lily_pads_.emplace_back(lily_pad);
    }
}

void
Model::launch() {
    frog_.live = true;
    time_ = 0;
}

void
Model::update(double dt){
    if(frog_.live) {
        time_ += dt;

        move_cars(cars_, dt);
        move_logs(logs_, dt);
        move_lily_pads(dt, time_);

        frog_ = frog_.next(dt);

        if (! is_frog_alive()) {
            if (! is_game_over()) {
                frog_ = Frog(config_);
            }
            else {
                frog_.live = false;
            }
        }
    }
}

void
Model::move_frog(char direction){
    frog_ = frog_.jump(direction);
}

bool
Model::is_frog_alive(){
    bool on_log = false;
    for(std::pair<Rectangle, Velocity> car : cars_) {
        if(frog_.touches_object(car.first, config_)){
                --lives_left_;
                return false;
            }
    }

    if (frog_.touches_object(config_.river_rect, config_)){
        for (std::pair<Rectangle, Velocity> log : logs_){
            if (frog_.touches_object(log.first, config_)){
                frog_.velocity.width = log.second.width;
                on_log = true;
                return true;
            }
        }
        for (Rectangle lily_pad : lily_pads_){
            if (frog_.touches_object(lily_pad, config_)){
                frog_.velocity.width = 0;
                return true;
            }
        }
        --lives_left_;
        return false;
    }
    if (!on_log) {
        frog_.velocity.width = 0;
    }

    if (frog_.top_left.x + config_.frog_dims.width < 0 ||
            frog_.top_left.x > config_.scene_dims.width) {
        --lives_left_;
        return false;
    }

    if(frog_.top_left.y < 75) {
        for(Rectangle rec : end_zone_) {
            if(frog_.touches_object(rec, config_)) {
                //FIX
                num_dens_reached++;
                //need to draw a frog here
                return false;
            }
        }
        --lives_left_;
        return false;
    }
    return true;
}

void
Model::move_logs(std::vector<std::pair<Rectangle, Velocity>>& logs, double dt){
    for (std::pair<Rectangle, Velocity> &logs : logs_){
        logs.first.x += (logs.second.width * dt);
        if (logs.first.x > config_.scene_dims.width){
            logs.first.x = (-1) * logs.first.width;
        } else if (logs.first.x + logs.first.width < 0) {
            logs.first.x = 1 + config_.scene_dims.width;
        }
    }
}

void
Model::move_cars(std::vector<std::pair<Rectangle, Velocity>>& cars, double dt){
    for (std::pair<Rectangle, Velocity> &cars : cars_){
        cars.first.x += (cars.second.width * dt);
        if (cars.first.x > config_.scene_dims.width){
            cars.first.x = (-1) * cars.first.width;
        } else if (cars.first.x + cars.first.width < 0) {
            cars.first.x = config_.scene_dims.width;
        }
    }
}

void
Model::move_lily_pads(double dt, double time) {
        if ((fmod(time, dt * 180) == 0) && (fmod(time, dt * 360) != 0)){
            lily_pads_.clear();
        }
        else if (fmod(time, dt * 360) == 0){
            double r1;
            std::vector<Rectangle> new_lily_pads;
            Rectangle new_lily_pad;
            for (Rectangle &lily_pads: lily_pads_) {
                r1 = ((double) rand() / (RAND_MAX));
                new_lily_pad = {(int) (r1 * config_.scene_dims.width), (int) (lily_pads.y),
                                config_.lily_pad_dims.width, config_.lily_pad_dims.height};
                new_lily_pads.emplace_back(new_lily_pad);
            }
            lily_pads_ = new_lily_pads;
        }
}

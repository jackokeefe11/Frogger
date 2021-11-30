#include "model.hxx"
#include <cstdlib>

Model::Model(Game_config const& config)
        : config_(config),
          frog_(config)
{
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
}

void
Model::launch() {
    frog_.live = true;
}

void
Model::update(double dt){
    if(frog_.live) {
        move_cars(cars_, dt);
        move_logs(logs_, dt);

        if (! is_frog_alive()) {
            if (! is_game_over()) {
                frog_ = Frog(config_);
            }
            else{
                frog_.live = false;
            }
        }
        frog_ = frog_.next(dt);
    }
}

void
Model::move_frog(char direction){
    frog_ = frog_.jump(direction);
}

bool
Model::is_frog_alive(){
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
                    return true;
            }
        }
        --lives_left_;
        return false;
    }

    /*//THIS DOESNT WORK AND I DON'T KNOW WHY
    if (frog_.hits_side(config_)){
        --lives_left_;
        return false;
    }*/
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



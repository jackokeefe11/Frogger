// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "frog.hxx"

// It won't compile without this, so you get it for free.
Frog::Frog(Game_config const& config)
        : top_left((int)(config.column_dims.width * 6.125), config.scene_dims.height - (int)(.875 * config.row_dims.height)),
          movement((int)(config.column_dims.width)),
          live(false),
          velocity(0, 0),
          dens_reached{false, false, false}

{ }


Frog
Frog::next(double dt) const
{
    Frog result(*this);
    Position temp = {top_left.x, top_left.y};

    Velocity v = velocity;

    //temp.right_by(dt * v.width);
    result.top_left.x += (dt * result.velocity.width);

    return result;
}

Frog
Frog::jump(char direction) const{
    Frog result(*this);
    Position temp = {top_left.x, top_left.y};

    if (direction == 'u') {
        if (!((temp.y - movement) <= 0)) {
            result.top_left = temp.up_by((movement));
        }
    }
    else if (direction == 'd') {
        if (!((temp.y + movement) > 708)){
            result.top_left = temp.up_by((-1) * movement);
        }
    }
    else if (direction == 'l') {
        result.top_left = temp.right_by((-1)*(movement));
    }
    else if (direction == 'r') {
        result.top_left = temp.right_by(movement);
    }

    return result;
}
// As with the edge collision functions, we want to use the ball's
// bounding box. That is, the box whose top is center.y - radius, whose
// left is center.x - radius, whose bottom is center.y + radius, and
// whose right is center.x + radius.
//
// That way, we are checking for the intersection of two rectangles.
//
// One way to think of that is that the rectangles *don't* intersect if
// either of these is true:
//
//  - The right side of one rectangle is to the left of the left side of
//  the other.
//
//  - The bottom of one rectangle is above the top of the other
//
// Otherwise, they do.
//
bool
Frog::touches_object(Block const& block, Game_config const& config) const
{
    int frog_top = top_left.y;
    int frog_left = top_left.x;
    int frog_bottom = top_left.y + config.frog_dims.height;
    int frog_right = top_left.x + config.frog_dims.width;
    int rec_bottom = block.y + block.height;
    int rec_right = block.x + block.width;

    return (!(frog_right < block.x
              || rec_right < frog_left
              || frog_bottom < block.y
              || rec_bottom < frog_top));
}



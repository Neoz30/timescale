#pragma once
#include <libmath/vec2.hpp>

struct Block {
    unsigned char id;
};

struct TileMap { 
    Block tiles[64][64];
    TileMap();
};

struct Hitbox {
    float w, h;
};

struct BlockEntity {
};

struct Entity {
    Hitbox hitbox;
    Vec2 position {0, 0};
    Vec2 velocity {0, 0};
    Vec2 acceleration {0, 0};

    // Entity touching block direction
    bool up_touch = false;
    bool right_touch = false;
    bool down_touch = false;
    bool left_touch = false;

    bool touchground(TileMap* map);
    bool will_collide(int blockX, int blockY);

    void edge_collision();
    void block_collision(TileMap* map);

    void physic(float dt, TileMap* map);
    virtual void update(float dt, TileMap* map);
};

struct Player: public Entity {
    bool controller[5] = {false};

    Player(float width, float height, Vec2 basepos);

    void control_movement(float dt);
    void update(float dt, TileMap* map);
};

struct AwayMob: public Entity {
    bool onground = false;

    AwayMob(Vec2 basepos);

    void update(float dt, Vec2 toplayer, TileMap* map);
};
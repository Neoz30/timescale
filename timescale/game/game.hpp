#pragma once
#include <libmath/vec2.hpp>

struct Hitbox {
    float w, h;
};

struct Entity {
    Hitbox hitbox;
    Vec2 position {0, 0};
    Vec2 velocity {0, 0};
    Vec2 acceleration {0, 0};

    bool frictionX = false, frictionY = false;

    Entity(float width, float height, Vec2 position);

    void physic(float dt, TileMap* map);
    void update(float dt, TileMap* map);
};

struct BlockEntity {
};

struct Block {
    unsigned char id;
};


struct TileMap {
    Block tiles[64][64];
    TileMap();
};

struct Player {
    Hitbox hitbox;
    Vec2 position;
    Vec2 velocity {0, 0};
    Vec2 acceleration {0, 0};
    
    bool onground = false;
    bool controller[5] = {false};

    Player(Vec2 basepos, float width, float height);

    bool touchground(TileMap* map);
    void control_movement(float dt);

    void edge_collision();
    bool will_collide(int blockX, int blockY);
    void block_collision(TileMap* map);

    void physic(float dt, TileMap* map);
    void update(float dt, TileMap* map);
};

struct AwayMob: public Entity {
    bool onground = false;

    AwayMob(Vec2 basepos);

    bool touchground(TileMap* map);
    void edge_collision();
    bool will_collide(int blockX, int blockY);
    void block_collision(TileMap* map);

    void physic(float dt, TileMap* map);
    void update(float dt, Vec2 toplayer, TileMap* map);
};
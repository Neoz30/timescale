#pragma once
#include <libmath/vec2.hpp>

struct Hitbox {
    float w, h;
};

class Entity {
};
class BlockEntity {
};
class Block {
    public:
        unsigned char id;
};

class TileMap {
    public:
        Block tiles[64][64];
        TileMap();
};

class Player {
    public:
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
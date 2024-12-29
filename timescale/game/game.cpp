#include <game/game.hpp>

TileMap::TileMap() {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
                tiles[i][j].id = 0;
        }
    }
}

Player::Player(Vec2 basepos, float width, float height) {
    position = basepos;
    hitbox.w = width;
    hitbox.h = height;
}

bool Player::touchground(TileMap* map) {
    int underblock[2] = {(int)position.x, (int)position.y-1};
    int offset = (position.x-underblock[0] < 0.5) ? -1 : 1;
    if (position.x-underblock[0] == 0.5) offset = 0;
    int underblock2[2] = {(int)position.x+offset, (int)position.y-1};

    Block groundcenter = map->tiles[underblock[0]][underblock[1]];
    Block groundside = map->tiles[underblock2[0]][underblock2[1]];
    if (groundcenter.id == 0 && groundside.id == 0) {
        return false;
    }

    float deltaY = (position.y-hitbox.h/2)-(underblock[1]+1);
    if (deltaY <= 0.05f && 0.f <= deltaY) {return true;}
    return false;
}

void Player::control_movement(float dt) {
    if (onground && controller[4]) acceleration.y += 1700;
    if (controller[1]) acceleration.x += 32;
    if (controller[3]) acceleration.x -= 32;
}

void Player::edge_collision() {
    if (position.y-hitbox.h/2 < 0) {position.y = hitbox.h/2; velocity.y = 0;}
    if (position.y+hitbox.h/2 > 64) {position.y = 64-hitbox.h/2; velocity.y = 0;}
    if (position.x-hitbox.w/2 < 0) {position.x = hitbox.w/2; velocity.x = 0;}
    if (position.x+hitbox.w/2 > 64) {position.x = 64-hitbox.w/2; velocity.x = 0;}
}

bool Player::will_collide(int blockX, int blockY) {
    Vec2 nextposition = position+velocity;
    return nextposition.x-hitbox.w/2 < blockX+1 && nextposition.x+hitbox.w/2 > blockX &&
    nextposition.y-hitbox.h/2 < blockY+1 && nextposition.y+hitbox.h/2 > blockY;
}

void Player::block_collision(TileMap* map) {
    int offset[9][2] = {
        {0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}
        };

    for (int i = 0; i < 9; i++) {
        Vec2 nextposition = position+velocity;

        int block[2] = {(int)nextposition.x+offset[i][0], (int)nextposition.y+offset[i][1]};
        if (block[0] < 0 || block[0] > 63 || block[1] < 0 || block[1] > 63) continue;

        unsigned char blockid = map->tiles[block[0]][block[1]].id;

        if (blockid > 0 && will_collide(block[0], block[1])) {
            Vec2 delta = {
                (float)block[0]-position.x+0.5f,
                (float)block[1]-position.y+0.5f
                };
            Vec2 delta2 = {
                (float)block[0]-nextposition.x+0.5f,
                (float)block[1]-nextposition.y+0.5f
                };
            
            if (delta.x > abs(delta.y)) {velocity.x -= hitbox.w/2+0.5 - delta2.x;}
            if (-delta.x > abs(delta.y)) {velocity.x += hitbox.w/2+0.5 + delta2.x;}
            if (delta.y > abs(delta.x)) {velocity.y -= hitbox.h/2+0.5 - delta2.y;}
            if (-delta.y > abs(delta.x)) {velocity.y += hitbox.w/2+0.5 + delta2.y;}
        }
    }
}

void Player::physic(float dt, TileMap* map) {
    // Gravity Force
    acceleration.y -= 64;

    //Update physic player
    Vec2 opposite_speed = -velocity;
    float speedfriction = 0.1f*pow(opposite_speed.length(), 2);
    opposite_speed.normalize();
    
    Vec2 kineticfriction = opposite_speed*speedfriction;
    acceleration += kineticfriction;

    if (onground && velocity.length() > 0.01f) {
        Vec2 staticfriction = opposite_speed*16;
        acceleration += staticfriction;
    } else acceleration = velocity*-1 + acceleration;

    velocity = (acceleration*dt + velocity)*dt;

    edge_collision();
    block_collision(map);

    position = velocity + position;
    velocity = velocity/dt;
}

void Player::update(float dt, TileMap* map) {
    acceleration = {0, 0};
    control_movement(dt);
    onground = touchground(map);
    physic(dt, map);
}
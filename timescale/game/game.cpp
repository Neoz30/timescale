#include <game/game.hpp>

TileMap::TileMap() {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
                tiles[i][j].id = 0;
        }
    }
}

bool Entity::touchground(TileMap* map) {
    int playerint[2] = {(int)position.x, (int)position.y};
    Block blockbelow = map->tiles[playerint[0]][playerint[1]-1];

    int offset = 0;
    if (playerint[0]+0.5f != position.x) offset = (playerint[0]+0.5f < position.x) ? 1 : -1;
    Block belowside = map->tiles[playerint[0]+offset][playerint[1]-1];

    if (blockbelow.id == 0 && belowside.id == 0) return false;

    float deltaY = (position.y-hitbox.h/2)-playerint[1];
    if (deltaY <= 0.02f && 0.f <= deltaY) return true;
    return false;
}

bool Entity::will_collide(int blockX, int blockY) {
    Vec2 nextposition = position+velocity;
    return nextposition.x-hitbox.w/2 < blockX+1 && nextposition.x+hitbox.w/2 > blockX &&
    nextposition.y-hitbox.h/2 < blockY+1 && nextposition.y+hitbox.h/2 > blockY;
}

void Entity::edge_collision() {
    if (position.y-hitbox.h/2 < 0) {position.y = hitbox.h/2; velocity.y = 0;}
    if (position.y+hitbox.h/2 > 64) {position.y = 64-hitbox.h/2; velocity.y = 0;}
    if (position.x-hitbox.w/2 < 0) {position.x = hitbox.w/2; velocity.x = 0;}
    if (position.x+hitbox.w/2 > 64) {position.x = 64-hitbox.w/2; velocity.x = 0;}
}

void Entity::block_collision(TileMap* map) {
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

void Entity::physic(float dt, TileMap* map) {
    // Gravity Force
    acceleration.y -= 64;

    //Update physic player
    Vec2 opposite_speed = -velocity;
    float speedfriction = 0.1f*pow(opposite_speed.length(), 2);
    opposite_speed.normalize();
    
    Vec2 kineticfriction = opposite_speed*speedfriction;
    acceleration += kineticfriction;

    Vec2 staticfriction = opposite_speed*16;
    if ((up_touch | down_touch) && velocity.length() > staticfriction.length()*dt) {
        acceleration += staticfriction;
    } else acceleration = velocity*-1 + acceleration;

    velocity = (acceleration*dt + velocity)*dt;

    edge_collision();
    block_collision(map);

    position = velocity + position;
    velocity = velocity/dt;
}

void Entity::update(float dt, TileMap* map) {
    acceleration = {0, 0};
    down_touch = touchground(map);
    physic(dt, map);
}

Player::Player(float width, float height, Vec2 basepos) {
    position = basepos;
    hitbox.w = width;
    hitbox.h = height;
}

void Player::control_movement(float dt) {
    if (down_touch && controller[4]) acceleration.y += 1700;
    if (controller[1]) acceleration.x += 32;
    if (controller[3]) acceleration.x -= 32;
}

void Player::update(float dt, TileMap* map) {
    acceleration = {0, 0};
    control_movement(dt);
    down_touch = touchground(map);
    physic(dt, map);
}

AwayMob::AwayMob(Vec2 basepos) {
    position = basepos;
    hitbox.w = 0.85;
    hitbox.h = 0.85;
}

void AwayMob::update(float dt, Vec2 toplayer, TileMap* map) {
    acceleration = {0, 0};

    float distplayer = toplayer.length();
    float desire = distplayer - 10.f;
    acceleration.x += (toplayer.normalize()*desire).x*27;

    onground = touchground(map);
    physic(dt, map);
}
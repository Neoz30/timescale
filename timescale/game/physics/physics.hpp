#pragma once
#include <libmath/vec2.hpp>

#define uchar unsigned char

struct BoundBox {
    Vec2 points[64];
    uchar count;

    BoundBox(uchar count);
    Vec2& findFurthestPoint(Vec2 dir);
};

struct Simplex {
    Vec2 points[64];
    uchar count;

    Simplex();
    Simplex& operator=(Simplex& other);
};


Vec2 supportFunction(BoundBox* bbA, BoundBox* bbB, Vec2 dir);

bool nextSimplex(Simplex& points, Vec2& dir);

bool detectionGJK(BoundBox* bbA, BoundBox* bbB);

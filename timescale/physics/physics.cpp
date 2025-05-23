#include <physics/physics.hpp>
#include <iostream>
using namespace std;

bool SameDirection(Vec2& dir, Vec2& AO) {
    return dir.dot(AO);
}

bool Line(Simplex& points, Vec2& dir) {
    Vec2 a = points.points[0], b = points.points[1];
    Vec2 ab = b - a, ao = -a;

    if (SameDirection(ab, ao)) {
        dir = ab;
    }
    else {
        points.points[0] = a;
        points.count = 1;

        dir = ao;
    }

    return true;
}

bool Triangle(Simplex& points, Vec2& dir) {
    Vec2 a = points.points[0], b = points.points[1], c = points.points[2];
    Vec2 ab = b-a, ac = c-a, ao = -a;
    Vec2 ab_perp = ab.cross(), ac_perp = ac.cross();

    if (SameDirection(ac_perp, ao)) {
        if (SameDirection(ac, ao)) {
            points.points[0] = a;
            points.points[1] = c;
            points.count = 2;

            dir = ac;
        }
        else {
            points.points[0] = a;
            points.points[1] = b;
            points.count = 2;

            return Line(points, dir);
        }
    }
    else {
        if (SameDirection(ab_perp, ao)) {
            points.points[0] = a;
            points.points[1] = b;
            points.count = 2;
            return Line(points, dir);
        }
    }
    
    return false;
}

BoundBox::BoundBox(uchar c) {
    count = (c > 64) ? 64 : c;
}

Vec2 BoundBox::findFurthestPoint(Vec2 dir) {
    Vec2 max_point;
    float max_dist = -__FLT_MAX__;

    for (uchar i = 0; i < count; i++) {
        float dist = points[i].dot(dir);
        if (dist <= max_dist) continue;

        max_dist = dist;
        max_point = points[i];
    }

    return max_point;
}

Simplex::Simplex() {
    count = 0;
}

Simplex& Simplex::operator=(Simplex& other) {
    count = other.count;
    for (int i = 0; i < other.count; i++) {
        points[i] = other.points[i];
    }
    return *this;
}

Vec2 supportFunction(BoundBox& bbA, BoundBox& bbB, Vec2 dir) {
    return bbA.findFurthestPoint(dir) - bbB.findFurthestPoint(-dir);
}

bool nextSimplex(Simplex& points, Vec2& dir) {
    switch (points.count) {
        case 2: return Line(points, dir);
        case 3: return Triangle(points, dir);
    }

    return false;
}

bool detectionGJK(BoundBox& bbA, BoundBox& bbB) {
    Vec2 support = supportFunction(bbA, bbB, Vec2(0.f, 1.f));

    Simplex simplex;
    simplex.points[0] = support;
    simplex.count = 1;

    Vec2 dir = -support;

    while (true) {
        support = supportFunction(bbA, bbB, dir);
        if (support.dot(dir) <= 0) return false;

        simplex.count++;
        simplex.points[simplex.count] = support;
        if (nextSimplex(simplex, dir)) return true;
    }
}
#ifndef __VEC2_HPP__
#define __VEC2_HPP__

#include <cmath>

class ivec2 {
public:
	int x, y;
	
	ivec2() :x(0), y(0) {}
	ivec2(int x, int y) : x(x), y(y) {}
	ivec2(const ivec2& v) : x(v.x), y(v.y) {}
	
	ivec2& operator=(const ivec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	
	ivec2 operator+(ivec2& v) {
		return ivec2(x + v.x, y + v.y);
	}
	ivec2 operator-(ivec2& v) {
		return ivec2(x - v.x, y - v.y);
	}
	
	ivec2& operator+=(ivec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	ivec2& operator-=(ivec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	
	ivec2 operator+(int s) {
		return ivec2(x + s, y + s);
	}
	ivec2 operator-(int s) {
		return ivec2(x - s, y - s);
	}
	ivec2 operator*(int s) {
		return ivec2(x * s, y * s);
	}
	ivec2 operator/(int s) {
		return ivec2(x / s, y / s);
	}
	
	
	ivec2& operator+=(int s) {
		x += s;
		y += s;
		return *this;
	}
	ivec2& operator-=(int s) {
		x -= s;
		y -= s;
		return *this;
	}
	ivec2& operator*=(int s) {
		x *= s;
		y *= s;
		return *this;
	}
	ivec2& operator/=(int s) {
		x /= s;
		y /= s;
		return *this;
	}

	
	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}
	
	ivec2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}
	
	float dist(ivec2 v) const {
		ivec2 d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}
	
	ivec2 ortho() const {
		return ivec2(y, -x);
	}
	
	static float dot(ivec2 v1, ivec2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(ivec2 v1, ivec2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
	
};

class fvec2 {
public:
	float x, y;
	
	fvec2() :x(0), y(0) {}
	fvec2(float x, float y) : x(x), y(y) {}
	fvec2(const fvec2& v) : x(v.x), y(v.y) {}
	
	fvec2& operator=(const fvec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	
	fvec2 operator+(fvec2& v) {
		return fvec2(x + v.x, y + v.y);
	}
	fvec2 operator-(fvec2& v) {
		return fvec2(x - v.x, y - v.y);
	}
	
	fvec2& operator+=(fvec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	fvec2& operator-=(fvec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	
	fvec2 operator+(float s) {
		return fvec2(x + s, y + s);
	}
	fvec2 operator-(float s) {
		return fvec2(x - s, y - s);
	}
	fvec2 operator*(float s) {
		return fvec2(x * s, y * s);
	}
	fvec2 operator/(float s) {
		return fvec2(x / s, y / s);
	}
	
	
	fvec2& operator+=(float s) {
		x += s;
		y += s;
		return *this;
	}
	fvec2& operator-=(float s) {
		x -= s;
		y -= s;
		return *this;
	}
	fvec2& operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}
	fvec2& operator/=(float s) {
		x /= s;
		y /= s;
		return *this;
	}

	
	void rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}
	
	fvec2& normalize() {
		if (length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}
	
	float dist(fvec2 v) const {
		fvec2 d(v.x - x, v.y - y);
		return d.length();
	}
	float length() const {
		return std::sqrt(x * x + y * y);
	}
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}
	
	fvec2 ortho() const {
		return fvec2(y, -x);
	}
	
	static float dot(fvec2 v1, fvec2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	static float cross(fvec2 v1, fvec2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
};

#endif

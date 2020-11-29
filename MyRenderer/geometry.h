#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T> struct Vector2 {
	union {
		struct {T u, v;};
		struct {T x, y;};
		T raw[2];
	};
	Vector2() : u(0), v(0) {}
	Vector2(T _u, T _v) : u(_u),v(_v) {}
	inline Vector2<T> operator +(const Vector2<T> &V) const { return Vector2<T>(u+V.u, v+V.v); }
	inline Vector2<T> operator -(const Vector2<T> &V) const { return Vector2<T>(u-V.u, v-V.v); }
	inline Vector2<T> operator *(float f)          const { return Vector2<T>(u*f, v*f); }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vector2<T>& v);
};

template <class T> struct Vector3 {
	union {
		struct {T x, y, z;};
		struct { T ivert, iuv, inorm; };
		T raw[3];
	};
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T _x, T _y, T _z) : x(_x),y(_y),z(_z) {}
	inline Vector3<T> operator ^(const Vector3<T> &v) const { return Vector3<T>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	inline Vector3<T> operator +(const Vector3<T> &v) const { return Vector3<T>(x+v.x, y+v.y, z+v.z); }
	inline Vector3<T> operator -(const Vector3<T> &v) const { return Vector3<T>(x-v.x, y-v.y, z-v.z); }
	inline Vector3<T> operator *(float f)          const { return Vector3<T>(x*f, y*f, z*f); }
	inline T       operator *(const Vector3<T> &v) const { return x*v.x + y*v.y + z*v.z; }
	float norm () const { return std::sqrt(x*x+y*y+z*z); }
	Vector3<T> & normalize(T l=1) { *this = (*this)*(l/norm()); return *this; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vector3<T>& v);
};

typedef Vector2<float> Vector2f;
typedef Vector2<int>   Vector2i;
typedef Vector3<float> Vector3f;
typedef Vector3<int>   Vector3i;

template <class T> std::ostream& operator<<(std::ostream& s, Vector2<T>& v) {
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}

template <class T> std::ostream& operator<<(std::ostream& s, Vector3<T>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}

#endif //__GEOMETRY_H__

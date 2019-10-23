#ifndef _RTVECTOR_HPP_
#define _RTVECTOR_HPP_

#include <iostream>  // for the ostream class
#include <cmath>

#define TEMPLATE_DEF template<class T> inline

#define LERP_DELTA 1e-6

namespace RTVector {

// -------------------- vectors -----------------------------------------------

template<class T> class _vec3;
template<class T> class _vec2;


/* ----------------------------------------------------------------------------
 * _vec4
 * ----------------------------------------------------------------------------
 * Description :
 *    Defines a 4 components vector.
 * ----------------------------------------------------------------------------
 */
template<class T> class _vec4 {
public:
  union {
    struct {
      T x, y, z, w;
    };
    struct {
      T r, g, b, a;
    };
  };

  _vec4();
  _vec4(const T& f);
  _vec4(const T& x, const T& y, const T& z, const T& w);
  _vec4(const T *v);
  _vec4(const _vec4<T>& v);
  _vec4(const _vec3<T>& v);
  _vec4(const _vec3<T>& v, const T& f);
  _vec4(const _vec2<T>& v1, const _vec2<T>& v2);
  _vec4(const _vec2<T>& v, const T& f);
  _vec4(const _vec2<T>& v, const T& f1, const T& f2);
  _vec4(const _vec2<T>& v);

  bool operator==(const _vec4<T>& v);
  bool operator!=(const _vec4<T>& v);

  _vec4<T>& operator=(const _vec4<T>& v);
  const _vec4<T> operator-() const;

  const T operator[](int index) const;
  T& operator[](int index);

  const _vec4<T> operator+(const _vec4<T>& v) const;
  const _vec4<T> operator-(const _vec4<T>& v) const;
  const _vec4<T> operator*(const _vec4<T>& v) const;
  const _vec4<T> operator*(const T& f) const;
  const _vec4<T> operator/(const _vec4<T>& v) const;

  _vec4<T>& operator+=(const _vec4<T>& v);
  _vec4<T>& operator-=(const _vec4<T>& v);
  _vec4<T>& operator*=(const _vec4<T>& v);
  _vec4<T>& operator/=(const _vec4<T>& v);
  _vec4<T>& operator/=(const T& f);

  operator T*();
  operator const T*() const;

  operator _vec3<T>();
  operator const _vec3<T>() const;

  operator _vec2<T>();
  operator const _vec2<T>() const;

  bool equal(const _vec3<T>& v, const T e) const;
  void zero();
  void set(const T& _x, const T& _y, const T& _z, const T& _w);
  void clamp(const _vec4<T>& min, const _vec4<T>& max);
  void clamp(const T& f);
  void lerp(const _vec4<T>& v1, const _vec4<T>& v2, const T& t);
  T norm() const;
  T normSqr() const;
  void normalize();
  void normalize2();
};

// friend functions with template are not supported in VC7.1, so they are
// declared outside the class
template<class T> const _vec4<T> operator*(const T& f, const _vec4<T>& v);
template<class T> std::ostream& operator<<(std::ostream& out, const _vec4<T>& v);


TEMPLATE_DEF _vec4<T>::_vec4() {}

TEMPLATE_DEF _vec4<T>::_vec4(const T& f)
  : x(f), y(f), z(f), w(f) {}

TEMPLATE_DEF _vec4<T>::_vec4(const T& x, const T& y, const T& z, const T& w)
  : x(x), y(y), z(z), w(w) {}

TEMPLATE_DEF _vec4<T>::_vec4(const T *v)
  : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}

TEMPLATE_DEF _vec4<T>::_vec4(const _vec4<T>& v)
  : x(v.x), y(v.y), z(v.z), w(v.w) {}

TEMPLATE_DEF _vec4<T>::_vec4(const _vec3<T>& v)
  : x(v.x), y(v.y), z(v.z), w() {}

TEMPLATE_DEF _vec4<T>::_vec4(const _vec3<T>& v, const T& f)
  : x(v.x), y(v.y), z(v.z), w(f) {}

TEMPLATE_DEF _vec4<T>::_vec4(const _vec2<T>& v1, const _vec2<T>& v2)
  : x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}

TEMPLATE_DEF _vec4<T>::_vec4(const _vec2<T>& v, const T& f)
  : x(v.x), y(v.y), z(f), w(0.0f) {}

TEMPLATE_DEF _vec4<T>::_vec4(const _vec2<T>& v, const T& f1, const T& f2)
  : x(v.x), y(v.y), z(f1), w(f2) {}

TEMPLATE_DEF _vec4<T>::_vec4(const _vec2<T>& v)
  : x(v.x), y(v.y), z(0.0f), w(0.0f) {}

TEMPLATE_DEF _vec4<T>& _vec4<T>::operator=(const _vec4<T>& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
    
  return *this;
}

TEMPLATE_DEF const _vec4<T> _vec4<T>::operator-() const {
  return _vec4<T>(-x, -y, -z, -w);
}

TEMPLATE_DEF const T _vec4<T>::operator[](int index) const {
  return (&x)[index];
}

TEMPLATE_DEF T& _vec4<T>::operator[](int index) {
  return (&x)[index];
}

TEMPLATE_DEF bool _vec4<T>::operator==(const _vec4<T>& v) {
  return x == v.x &&
    y == v.y &&
    z == v.z &&
    w == v.w;
}
TEMPLATE_DEF bool _vec4<T>::operator!=(const _vec4<T>& v) {
  return x != v.x ||
    y != v.y ||
    z != v.z ||
    w != v.w;
}

TEMPLATE_DEF const _vec4<T> _vec4<T>::operator+(const _vec4<T>& v) const {
  return _vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
}

TEMPLATE_DEF const _vec4<T> _vec4<T>::operator-(const _vec4<T>& v) const {
  return _vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
}

TEMPLATE_DEF const _vec4<T> _vec4<T>::operator*(const _vec4<T>& v) const {
  return _vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
}

TEMPLATE_DEF const _vec4<T> _vec4<T>::operator*(const T& f) const {
  return _vec4<T>(x * f, y * f, z * f, w * f);
}

TEMPLATE_DEF const _vec4<T> operator*(const T& f, const _vec4<T>& v) {
  return _vec4<T>(v.x * f, v.y * f, v.z * f, v.w * f);
}

TEMPLATE_DEF const _vec4<T> _vec4<T>::operator/(const _vec4<T>& v) const {
  return _vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
}

TEMPLATE_DEF _vec4<T>& _vec4<T>::operator+=(const _vec4<T>& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
    
  return *this;
}

TEMPLATE_DEF _vec4<T>& _vec4<T>::operator-=(const _vec4<T>& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;

  return *this;
}

TEMPLATE_DEF _vec4<T>& _vec4<T>::operator*=(const _vec4<T>& v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
  w *= v.w;
    
  return *this;
}

TEMPLATE_DEF _vec4<T>& _vec4<T>::operator/=(const _vec4<T>& v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;
  w /= v.w;

  return *this;
}

TEMPLATE_DEF _vec4<T>& _vec4<T>::operator/=(const T& f) {
  x /= f;
  y /= f;
  z /= f;
  w /= f;
    
  return *this;
}

TEMPLATE_DEF _vec4<T>::operator T*() {
  return (T*)& x;
}

TEMPLATE_DEF _vec4<T>::operator const T*() const {
  return (T*)& x;
}

TEMPLATE_DEF _vec4<T>::operator _vec3<T>() {
  return *reinterpret_cast<_vec3<T> >(this);
}

TEMPLATE_DEF _vec4<T>::operator const _vec3<T>() const {
  return *reinterpret_cast<const _vec3<T> >(this);
}

TEMPLATE_DEF _vec4<T>::operator _vec2<T>() {
  return *reinterpret_cast<_vec2<T> >(this);
}

TEMPLATE_DEF _vec4<T>::operator const _vec2<T>() const {
  return *reinterpret_cast<const _vec2<T> >(this);
}

TEMPLATE_DEF bool _vec4<T>::equal(const _vec3<T>& v, const T e) const {
  return fabs(x - v.x) < e &&
    fabs(y - v.y) < e &&
    fabs(z - v.z) < e &&
    fabs(w - v.w) < e;
}
TEMPLATE_DEF void _vec4<T>::zero() {
  x = y = z = w = static_cast<T>(0.0f);
}

TEMPLATE_DEF void _vec4<T>::set(const T& _x, const T& _y, const T& _z, const T& _w) {
  x = _x;
  y = _y;
  z = _z;
  w = _w;
}

TEMPLATE_DEF void _vec4<T>::clamp(const _vec4<T>& min, const _vec4<T>& max) {
  if(x < min.x) x = min.x; if(x > max.x) x = max.x;
  if(y < min.y) y = min.y; if(y > max.y) x = max.y;
  if(z < min.z) z = min.z; if(z > max.z) x = max.z;
  if(w < min.w) w = min.w; if(w > max.w) x = max.w;
}

TEMPLATE_DEF void _vec4<T>::clamp(const T& f) {
  if(x < static_cast<T>(0.0f)) x = static_cast<T>(0.0f); if(x > f) x = f;
  if(y < static_cast<T>(0.0f)) y = static_cast<T>(0.0f); if(y > f) x = f;
  if(z < static_cast<T>(0.0f)) z = static_cast<T>(0.0f); if(z > f) x = f;
  if(w < static_cast<T>(0.0f)) w = static_cast<T>(0.0f); if(w > f) x = f;
}

TEMPLATE_DEF void _vec4<T>::lerp(const _vec4<T>& v1, const _vec4<T>& v2, const T& t) {
  if(t <= static_cast<T>(0.0f)) { (*this) = v1; }
  else if(t >= static_cast<T>(1.0f)) { (*this) = v2; }
  else { (*this) = v1 + t * (v2 - v1); }
}

TEMPLATE_DEF T _vec4<T>::norm() const {
  return sqrt(x * x + y * y + z * z + w * w);
}

TEMPLATE_DEF T _vec4<T>::normSqr() const {
  return x * x + y * y + z * z + w * w;
}

TEMPLATE_DEF void _vec4<T>::normalize() {
  T n = norm();
  if(n) {
    n = 1.0f / n;
    x *= n;
    y *= n;
    z *= n;
    w *= n;
  }
}

TEMPLATE_DEF void _vec4<T>::normalize2() {
  T n = T(1.0) / sqrt(x * x + y * y + z * z + w * w);
  *this *= n;
}

TEMPLATE_DEF std::ostream& operator<<(std::ostream& out, const _vec4<T>& v) {
  return out << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
}


// -------------------- Predefined vec4 types ---------------------------------

typedef _vec4<float> vec4;
typedef _vec4<float> vec4f;
typedef _vec4<double> vec4d;
typedef _vec4<int> vec4i;
typedef _vec4<unsigned int> vec4u;
typedef _vec4<unsigned char> vec4b;
typedef _vec4<float> col4;
typedef _vec4<float> col4f;
typedef _vec4<double> col4d;
typedef _vec4<unsigned char> col4ub;

/* ----------------------------------------------------------------------------
 * _vec3
 * ----------------------------------------------------------------------------
 * Description :
 *    Defines a 3 components vector.
 * ----------------------------------------------------------------------------
 */
template<class T>
class _vec3 {
public:
  union {
    struct {
      T x, y, z;
    };
    struct {
      T r, g, b;
    };
  };

  _vec3();
  _vec3(const T& f);
  _vec3(const T& x, const T& y, const T& z);
  _vec3(const T *v);
  _vec3(const _vec3<T>& v);
  _vec3(const _vec4<T>& v);
  _vec3(const _vec2<T>& v, const T& f);
  _vec3(const _vec2<T>& v);

  bool operator==(const _vec3<T>& v);
  bool operator!=(const _vec3<T>& v);

  _vec3<T>& operator=(const _vec3<T>& v);
  const _vec3<T> operator-() const;

  const T operator[](int index) const;
  T& operator[](int index);

  const _vec3<T> operator+(const _vec3<T>& v) const;
  const _vec3<T> operator-(const _vec3<T>& v) const;
  const _vec3<T> operator*(const _vec3<T>& v) const;
  const _vec3<T> operator*(const T& f) const;
  const _vec3<T> operator/(const _vec3<T>& v) const;

  _vec3<T>& operator+=(const _vec3<T>& v);
  _vec3<T>& operator-=(const _vec3<T>& v);
  _vec3<T>& operator*=(const _vec3<T>& v);
  _vec3<T>& operator/=(const _vec3<T>& v);
  _vec3<T>& operator/=(const T& f);

  _vec3<T> operator^(const _vec3<T>& v);

  operator T*();
  operator const T*() const;

  operator _vec4<T>();
  operator const _vec4<T>() const;

  operator _vec2<T>();
  operator const _vec2<T>() const;

  void zero();
  void set(const T& _x, const T& _y, const T& _z);
  void clamp(const _vec3<T>& min, const _vec3<T>& max);
  void clamp(const T& f);
  void lerp(const _vec3<T>& v1, const _vec3<T>& v2, const T& t);
  void slerp(const _vec3<T> &v1, const _vec3<T> &v2, const T &t);

  T norm() const;
  T normSqr() const;
  void normalize();
  void normalize2();
  T dot(const _vec3<T>& v) const;
  _vec3<T> cross(const _vec3<T>& v) const;
  bool equal(const _vec3<T>& v, const T& e) const;
  T angle(const _vec3<T>& v) const;
  T angle2(const _vec3<T>& v) const;
  void project(const _vec3<T>& v);
  void project2(const _vec3<T> &v);
  void trunc(T length);
};

// friend functions with template are not supported in VC7.1, so they are
// declared outside the class
template<class T> const _vec3<T> operator*(const T& f, const _vec3<T>& v);
template<class T> const T dot(const _vec3<T> &v1, const _vec3<T> &v2);
template<class T> const _vec3<T> cross(const _vec3<T> &v1, const _vec3<T> &v2);
template<class T> const _vec3<T> reflect(const _vec3<T> &inc, const _vec3<T> &nor);
template<class T> const _vec3<T> refract(const _vec3<T>& inc, const _vec3<T>& nor, T n);
template<class T> std::ostream& operator<<(std::ostream& out, const _vec3<T>& v);


TEMPLATE_DEF _vec3<T>::_vec3() {}

TEMPLATE_DEF _vec3<T>::_vec3(const T& f)
  : x(f), y(f), z(f) {}

TEMPLATE_DEF _vec3<T>::_vec3(const T& x, const T& y, const T& z)
  : x(x), y(y), z(z) {}

TEMPLATE_DEF _vec3<T>::_vec3(const T *v)
  : x(v[0]), y(v[1]), z(v[2]) {}

TEMPLATE_DEF _vec3<T>::_vec3(const _vec3<T>& v)
  : x(v.x), y(v.y), z(v.z) {}

TEMPLATE_DEF _vec3<T>::_vec3(const _vec4<T>& v)
  : x(v.x), y(v.y), z(v.z) {}

TEMPLATE_DEF _vec3<T>::_vec3(const _vec2<T>& v, const T& f)
  : x(v.x), y(v.y), z(f) {}

TEMPLATE_DEF _vec3<T>::_vec3(const _vec2<T>& v)
  : x(v.x), y(v.y), z() {}

TEMPLATE_DEF bool _vec3<T>::operator==(const _vec3<T>& v) {
  return x == v.x &&
    y == v.y &&
    z == v.z;
}

TEMPLATE_DEF bool _vec3<T>::operator!=(const _vec3<T>& v) {
  return x != v.x ||
    y != v.y ||
    z != v.z;
}
 
TEMPLATE_DEF _vec3<T>& _vec3<T>::operator=(const _vec3<T>& v) {
  x = v.x;
  y = v.y;
  z = v.z;
    
  return *this;
}

TEMPLATE_DEF const _vec3<T> _vec3<T>::operator-() const {
  return _vec3<T>(-x, -y, -z);
}

TEMPLATE_DEF const T _vec3<T>::operator[](int index) const {
  return (&x)[index];
}

TEMPLATE_DEF T& _vec3<T>::operator[](int index) {
  return (&x)[index];
}

TEMPLATE_DEF const _vec3<T> _vec3<T>::operator+(const _vec3<T>& v) const {
  return _vec3<T>(x + v.x, y + v.y, z + v.z);
}

TEMPLATE_DEF const _vec3<T> _vec3<T>::operator-(const _vec3<T>& v) const {
  return _vec3<T>(x - v.x, y - v.y, z - v.z);
}

TEMPLATE_DEF const _vec3<T> _vec3<T>::operator*(const _vec3<T>& v) const {
  return _vec3<T>(x * v.x, y * v.y, z * v.z);
}

TEMPLATE_DEF const _vec3<T> _vec3<T>::operator*(const T& f) const {
  return _vec3<T>(f * x, f * y, f * z);
}

TEMPLATE_DEF const _vec3<T> _vec3<T>::operator/(const _vec3<T>& v) const {
  return _vec3<T>(x / v.x, y / v.y, z / v.z);
}

TEMPLATE_DEF _vec3<T>& _vec3<T>::operator+=(const _vec3<T>& v) {
  x += v.x;
  y += v.y;
  z += v.z;
    
  return *this;
}
 
TEMPLATE_DEF _vec3<T>& _vec3<T>::operator-=(const _vec3<T>& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
    
  return *this;
}

TEMPLATE_DEF _vec3<T>& _vec3<T>::operator*=(const _vec3<T>& v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
    
  return *this;
}

TEMPLATE_DEF _vec3<T>& _vec3<T>::operator/=(const _vec3<T>& v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;
    
  return *this;
}

TEMPLATE_DEF _vec3<T>& _vec3<T>::operator/=(const T& f) {
  x /= f;
  y /= f;
  z /= f;

  return *this;
}

TEMPLATE_DEF _vec3<T> _vec3<T>::operator^(const _vec3<T>& v) {
  return _vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

TEMPLATE_DEF _vec3<T>::operator T*() {
  return (T*)& x;
}

TEMPLATE_DEF _vec3<T>::operator const T*() const {
  return (T*)& x;
}

TEMPLATE_DEF _vec3<T>::operator _vec4<T>() {
  return *reinterpret_cast<_vec4<T> >(this);
}

TEMPLATE_DEF _vec3<T>::operator const _vec4<T>() const {
  return *reinterpret_cast<_vec4<T> >(this);
}

TEMPLATE_DEF _vec3<T>::operator _vec2<T>() {
  return *reinterpret_cast<_vec2<T> >(this);
}

TEMPLATE_DEF _vec3<T>::operator const _vec2<T>() const {
  return *reinterpret_cast<_vec2<T> >(this);
}

TEMPLATE_DEF void _vec3<T>::zero() {
  x = y = z = static_cast<T>(0.0f);
}

TEMPLATE_DEF void _vec3<T>::set(const T& _x, const T& _y, const T& _z) {
  x = _x;
  y = _y;
  z = _z;
}

TEMPLATE_DEF void _vec3<T>::clamp(const _vec3<T>& min, const _vec3<T>& max) {
  if(x < min.x) x = min.x; if(x > max.x) x = max.x;
  if(y < min.y) y = min.y; if(y > max.y) x = max.y;
  if(z < min.z) z = min.z; if(z > max.z) x = max.z;
}

TEMPLATE_DEF void _vec3<T>::clamp(const T& f) {
  if(x < static_cast<T>(0.0f)) x = static_cast<T>(0.0f); if(x > f) x = f;
  if(y < static_cast<T>(0.0f)) y = static_cast<T>(0.0f); if(y > f) x = f;
  if(z < static_cast<T>(0.0f)) z = static_cast<T>(0.0f); if(z > f) x = f;
}

TEMPLATE_DEF void _vec3<T>::lerp(const _vec3<T>& v1, const _vec3<T>& v2, const T& t) {
  if(t <= static_cast<T>(0.0f)) { (*this) = v1; }
  else if(t >= static_cast<T>(1.0f)) { (*this) = v2; }
  else { (*this) = v1 + t * (v2 - v1); }
}

TEMPLATE_DEF T _vec3<T>::norm() const {
  return sqrt(x * x + y * y + z * z);
}

TEMPLATE_DEF T _vec3<T>::normSqr() const {
  return x * x + y * y + z * z;
}

TEMPLATE_DEF void _vec3<T>::normalize() {
  T n = norm();
  if(n) {
    n = 1.0f / n;
    x *= n;
    y *= n;
    z *= n;
  }
}

TEMPLATE_DEF void _vec3<T>::normalize2() {
  T n = rSqrtf(x * x + y * y + z * z);
  *this *= n;
}

TEMPLATE_DEF T _vec3<T>::dot(const _vec3<T>& v) const {
  return x * v.x + y * v.y + z * v.z;
}

TEMPLATE_DEF _vec3<T> _vec3<T>::cross(const _vec3<T>& v) const {
  return _vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

TEMPLATE_DEF bool _vec3<T>::equal(const _vec3<T>& v, const T& e) const {
  return fabs(x - v.x) < e &&
    fabs(y - v.y) < e &&
    fabs(z - v.z) < e;
}

TEMPLATE_DEF T _vec3<T>::angle(const _vec3<T>& v) const {
  return acos(dot(v) / (norm() * v.norm()));
}

TEMPLATE_DEF T _vec3<T>::angle2(const _vec3<T>& v) const {
  return acos(dot(v));
}

TEMPLATE_DEF void _vec3<T>::project(const _vec3<T>& v) {
  *this = (dot(v) / v.normSqr()) * v;
}

TEMPLATE_DEF void _vec3<T>::project2(const _vec3<T> &v) {
  *this = dot(v) * v;
}

TEMPLATE_DEF void _vec3<T>::trunc(T length) {
  if(!length) {
    zero();
    return;
  }
  float l = normSqr();
  if(l > length * length) {
    float inv = length * T(1.0) / sqrt(l);
    x *= inv;
    y *= inv;
    z *= inv;
  }
}

TEMPLATE_DEF const _vec3<T> operator*(const T& f, const _vec3<T>& v) {
  return _vec3<T>(f * v.x, f * v.y, f * v.z);
}

TEMPLATE_DEF std::ostream& operator<<(std::ostream& out, const _vec3<T>& v) {
  return out << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

TEMPLATE_DEF const T dot(const _vec3<T> &v1, const _vec3<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

TEMPLATE_DEF const _vec3<T> cross(const _vec3<T> &v1, const _vec3<T> &v2) {
  return _vec3<T>(v1.y * v2.z - v1.z * v2.y,
		  v1.z * v2.x - v1.x * v2.z,
		  v1.x * v2.y - v1.y * v2.x);
}

/* ----------------------------------------------------------------------------
 * _vec3<T>::slerp
 * ----------------------------------------------------------------------------
 * Description :
 *    Spherical linear interpolation. Vectors v1 and v2 are expected to be
 *    normalized.
 * Arguments :
 *    const _vec3<T> &v1 : vector.
 *    const _vec3<T> &v2 : vector.
 *    const T &t : factor.
 * ----------------------------------------------------------------------------
 */
template<class T> void _vec3<T>::slerp(const _vec3<T> &v1, const _vec3<T> &v2, const T &t) {
  T omega, cosom, sinom, scale0, scale1;

  if (t <= 0.0f) {
    (*this) = v1;
    return;
  }
  else if (t >= 1.0f) {
    (*this) = v2;
    return;
  }

  cosom = v1 * v2;
  if (( 1.0f - cosom ) > LERP_DELTA) {
    omega = acos(cosom);
    sinom = sin(omega);
    scale0 = sin((1.0f - t) * omega) / sinom;
    scale1 = sin(t * omega) / sinom;
  }
  else {
    scale0 = 1.0f - t;
    scale1 = t;
  }

  (*this) = (v1 * scale0 + v2 * scale1);
}


/* ------------------------------------------------------------------------
 * reflect
 * ------------------------------------------------------------------------
 * Description :
 *    Compute the reflected ray.
 * Arguments :
 *    const _vec3<T>& inc : incident ray.
 *    const _vec3<T>& nor : surface normal.
 * Return :
 *    _vec3<T> : reflected ray.
 * ------------------------------------------------------------------------
 */
TEMPLATE_DEF const _vec3<T> reflect(const _vec3<T>& inc, const _vec3<T>& nor) {
  return nor * (2.0f * dot(nor, inc)) - inc;
}


/* ----------------------------------------------------------------------------
 * refract
 * ----------------------------------------------------------------------------
 * Description :
 *    Compute the refracted ray as:
 *
 *        n * inc -(n + sqrt(1 - n² * (1 - cos²(i)))) * nor
 *
 *    with n = n1 / n2 and i the angle between inc and nor.
 * Arguments :
 *    const _vec3<T>& inc : normalized incident ray.
 *    const _vec3<T>& nor : normalized normal surface.
 *    T n : coefficient (n1 / n2).
 * Return :
 *    _vec3<T> : refracted ray.
 * ----------------------------------------------------------------------------
 */
TEMPLATE_DEF const _vec3<T> refract(const _vec3<T>& inc, const _vec3<T>& nor, T n) {
  float cosiSqr = dot(inc, nor);  // cos(i)
  cosiSqr *= cosiSqr;             // cos²(i)

  float s = 1.0f;                 // 1
  s -= cosiSqr;                   // 1 - cos²(i)
  s *= n;                         // n * (1 - cos²(i))
  s *= -n;                        // -n² * (1 - cos²(i))
  s += 1.0f;                      // 1 - n² * (1 - cos²(i))

  float r = n;                    // n
  r += sqrtf(s);                  // n + sqrt(1 - n² * (1 - cos²(i)))

  _vec3<T> ref(n * inc);          // n * inc
  ref -= r * nor;                 // n * inc -(n + sqrt(1 - n² * (1 -cos²(i)))) * nor
  return ref;
}



// -------------------- Predefined vec3 types ---------------------------------

typedef _vec3<float> vec3;
typedef _vec3<float> vec3f;
typedef _vec3<double> vec3d;
typedef _vec3<int> vec3i;
typedef _vec3<unsigned int> vec3u;
typedef _vec3<unsigned char> vec3b;
typedef _vec3<float> col3;
typedef _vec3<float> col3f;
typedef _vec3<double> col3d;


/* ----------------------------------------------------------------------------
 * _vec2
 * ----------------------------------------------------------------------------
 * Description :
 *    Defines a 2 components vector.
 * ----------------------------------------------------------------------------
 */
template<class T>
class _vec2 {
public:
  T x, y;

  _vec2();
  _vec2(const T& f);
  _vec2(const T& x, const T& y);
  _vec2(const T *v);
  _vec2(const _vec2<T>& v);
  _vec2(const _vec3<T>& v);
  _vec2(const _vec4<T>& v);

  bool operator==(const _vec2<T>& v);
  bool operator!=(const _vec2<T>& v);

  _vec2<T>& operator=(const _vec2<T>& v);
  const _vec2<T> operator-() const;

  const T operator[](int index) const;
  T& operator[](int index);

  const _vec2<T> operator+(const _vec2<T>& v) const;
  const _vec2<T> operator-(const _vec2<T>& v) const;
  const _vec2<T> operator*(const _vec2<T>& v) const;
  const _vec2<T> operator*(const T f);
  const _vec2<T> operator/(const _vec2<T>& v) const;

  _vec2<T>& operator+=(const _vec2<T>& v);
  _vec2<T>& operator-=(const _vec2<T>& v);
  _vec2<T>& operator*=(const _vec2<T>& v);
  _vec2<T>& operator/=(const _vec2<T>& v);
  _vec2<T>& operator/=(const T f);

  operator T*();
  operator const T*() const;

  operator _vec3<T>();
  operator const _vec3<T>() const;

  operator _vec4<T>();
  operator const _vec4<T>() const;

  void zero();
  void set(const T& _x, const T& _y);
  void clamp(const _vec2<T>& min, const _vec2<T>& max);
  void clamp(const T& f);
  void lerp(const _vec2<T>& v1, const _vec2<T>& v2, const T& t);

  T norm() const;
  T normSqr() const;
  void normalize();
  void normalize2();
  T dot(const _vec2<T>& v) const;
  _vec2<T> cross() const;
  bool equal(const _vec2<T>& v, const T e) const;
  T angle(const _vec2<T>& v) const;
  T angle2(const _vec2<T>& v) const;
  void project(const _vec2<T>& v);
  void project2(const _vec2<T> &v);
  void trunc(T length);
};

// friend functions with template are not supported in VC7.1, so they are
// declared outside the class
template<class T> const _vec2<T> operator*(const T& f, const _vec2<T>& v);
template<class T> const T dot(const _vec2<T> &v1, const _vec2<T> &v2);
template<class T> const _vec2<T> cross(const _vec2<T> &v);
template<class T> const _vec2<T> reflect(const _vec2<T> &inc, const _vec2<T> &nor);
//template<class T> const _vec2<T> transmit(const _vec2<T> &inc, const _vec2<T> &nor, T n);
template<class T> const _vec2<T> refract(const _vec2<T>& inc, const _vec2<T>& nor, T n);
template<class T> std::ostream& operator<<(std::ostream& out, const _vec2<T>& v);


TEMPLATE_DEF _vec2<T>::_vec2() {}

TEMPLATE_DEF _vec2<T>::_vec2(const T& f)
  : x(f), y(f) {}

TEMPLATE_DEF _vec2<T>::_vec2(const T& x, const T& y)
  : x(x), y(y) {}

TEMPLATE_DEF _vec2<T>::_vec2(const T *v)
  : x(v[0]), y(v[1]) {}

TEMPLATE_DEF _vec2<T>::_vec2(const _vec2<T>& v)
  : x(v.x), y(v.y) {}

TEMPLATE_DEF _vec2<T>::_vec2(const _vec3<T>& v)
  : x(v.x), y(v.y) {}

TEMPLATE_DEF _vec2<T>::_vec2(const _vec4<T>& v)
  : x(v.x), y(v.y) {}

TEMPLATE_DEF bool _vec2<T>::operator==(const _vec2<T>& v) {
  return x == v.x &&
    y == v.y;
}

TEMPLATE_DEF bool _vec2<T>::operator!=(const _vec2<T>& v) {
  return x != v.x ||
    y != v.y;
}

TEMPLATE_DEF const T _vec2<T>::operator[](int index) const {
  return (&x)[index];
}

TEMPLATE_DEF T& _vec2<T>::operator[](int index) {
  return (&x)[index];
}

TEMPLATE_DEF _vec2<T>& _vec2<T>::operator=(const _vec2<T>& v) {
  x = v.x;
  y = v.y;
    
  return *this;
}

TEMPLATE_DEF const _vec2<T> _vec2<T>::operator-() const {
  return _vec2<T>(-x, -y);
}

TEMPLATE_DEF const _vec2<T> _vec2<T>::operator+(const _vec2<T>& v) const {
  return _vec2<T>(x + v.x, y + v.y);
}

TEMPLATE_DEF const _vec2<T> _vec2<T>::operator-(const _vec2<T>& v) const {
  return _vec2<T>(x - v.x, y - v.y);
}

TEMPLATE_DEF const _vec2<T> _vec2<T>::operator*(const _vec2<T>& v) const {
  return _vec2<T>(x * v.x, y * v.y);
}

TEMPLATE_DEF const _vec2<T> _vec2<T>::operator*(const T f) {
  return _vec2<T>(f * x, f * y);
}

TEMPLATE_DEF const _vec2<T> _vec2<T>::operator/(const _vec2<T>& v) const {
  return _vec2<T>(x / v.x, y / v.y);
}

TEMPLATE_DEF _vec2<T>& _vec2<T>::operator+=(const _vec2<T>& v) {
  x += v.x; y += v.y; return *this;
}

TEMPLATE_DEF _vec2<T>& _vec2<T>::operator-=(const _vec2<T>& v) {
  x -= v.x; y -= v.y; return *this;
}

TEMPLATE_DEF _vec2<T>& _vec2<T>::operator*=(const _vec2<T>& v) {
  x *= v.x; y *= v.y; return *this;
}

TEMPLATE_DEF _vec2<T>& _vec2<T>::operator/=(const _vec2<T>& v) {
  x /= v.x; y /= v.y; return *this;
}

TEMPLATE_DEF _vec2<T>& _vec2<T>::operator/=(const T f) {
  x /= f;
  y /= f;

  return *this;
}

TEMPLATE_DEF _vec2<T>::operator T*() {
  return (T*)& x;
}

TEMPLATE_DEF _vec2<T>::operator const T*() const {
  return (T*)& x;
}

TEMPLATE_DEF _vec2<T>::operator _vec3<T>() {
  return *reinterpret_cast<_vec3<T> >(this);
}

TEMPLATE_DEF _vec2<T>::operator const _vec3<T>() const {
  return *reinterpret_cast<_vec3<T> >(this);
}

TEMPLATE_DEF _vec2<T>::operator _vec4<T>() {
  return *reinterpret_cast<_vec4<T> >(this);
}

TEMPLATE_DEF _vec2<T>::operator const _vec4<T>() const {
  return *reinterpret_cast<_vec4<T> >(this);
}

TEMPLATE_DEF void _vec2<T>::zero() {
  x = y = static_cast<T>(0.0f);
}

TEMPLATE_DEF void _vec2<T>::set(const T& _x, const T& _y) {
  x = _x;
  y = _y;
}

TEMPLATE_DEF void _vec2<T>::clamp(const _vec2<T>& min, const _vec2<T>& max) {
  if(x < min.x) x = min.x; if(x > max.x) x = max.x;
  if(y < min.y) y = min.y; if(y > max.y) x = max.y;
}

TEMPLATE_DEF void _vec2<T>::clamp(const T& f) {
  if(x < static_cast<T>(0.0f)) x = static_cast<T>(0.0f); if(x > f) x = f;
  if(y < static_cast<T>(0.0f)) y = static_cast<T>(0.0f); if(y > f) x = f;
}

TEMPLATE_DEF void _vec2<T>::lerp(const _vec2<T>& v1, const _vec2<T>& v2, const T& t) {
  if(t <= static_cast<T>(0.0f)) { (*this) = v1; }
  else if(t >= static_cast<T>(1.0f)) { (*this) = v2; }
  else { (*this) = v1 + t * (v2 - v1); }
}

TEMPLATE_DEF T _vec2<T>::norm() const {
  return sqrt(x * x + y * y);
}

TEMPLATE_DEF T _vec2<T>::normSqr() const {
  return x * x + y * y;
}

TEMPLATE_DEF void _vec2<T>::normalize() {
  T n = norm();
  if(n) {
    n = 1.0f / n;
    x *= n;
    y *= n;
  }
  return *this;
}

TEMPLATE_DEF void _vec2<T>::normalize2() {
  T n = rSqrtf(x * x + y * y);
  *this *= n;
}

TEMPLATE_DEF T _vec2<T>::dot(const _vec2<T>& v) const {
  return x * v.x + y * v.y;
}

TEMPLATE_DEF _vec2<T> _vec2<T>::cross() const {
  return _vec2<T>(-y, x);
}

TEMPLATE_DEF bool _vec2<T>::equal(const _vec2<T>& v, const T e) const {
  return fabs(x - v.x) < e &&
    fabs(y - v.y) < e;
}

TEMPLATE_DEF T _vec2<T>::angle(const _vec2<T>& v) const {
  return acos(dot(v) / (norm() * v.norm()));
}

TEMPLATE_DEF T _vec2<T>::angle2(const _vec2<T>& v) const {
  return acos(dot(v));
}

TEMPLATE_DEF void _vec2<T>::project(const _vec2<T>& v) {
  *this = (dot(v) / v.normSqr()) * v;
}

TEMPLATE_DEF void _vec2<T>::project2(const _vec2<T> &v) {
  *this = dot(v) * v;
}

TEMPLATE_DEF void _vec2<T>::trunc(T length) {
  if(!length) {
    zero();
    return;
  }
  float l = normSqr();
  if(l > length * length) {
    float inv = length * T(1.0)/sqrt(l);
    x *= inv;
    y *= inv;
  }
}

TEMPLATE_DEF const _vec2<T> operator*(const T& f, const _vec2<T>& v) {
  return _vec2<T>(v.x * f, v.y * f);
}

TEMPLATE_DEF const T dot(const _vec2<T> &v1, const _vec2<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

TEMPLATE_DEF const _vec2<T> cross(const _vec2<T> &v) {
  return _vec2<T>(-v.y, v.x);
}

TEMPLATE_DEF std::ostream& operator<<(std::ostream& out, const _vec2<T>& v) {
  return out << "[" << v.x << ", " << v.y << "]";
}

/* ------------------------------------------------------------------------
 * reflect
 * ------------------------------------------------------------------------
 * Description :
 *    Compute the reflected ray.
 * Arguments :
 *    const _vec2<T>& inc : incident ray.
 *    const _vec2<T>& nor : surface normal.
 * Return :
 *    _vec2<T> : reflected ray.
 * ------------------------------------------------------------------------
 */
TEMPLATE_DEF const _vec2<T> reflect(const _vec2<T> &inc, const _vec2<T> &nor) {
  return nor * (2.0f * dot(nor, inc)) - inc;
}


/* ----------------------------------------------------------------------------
 * transmit
 * ----------------------------------------------------------------------------
 * Description :
 *    Compute the transmited ray.
 * Arguments :
 *    const _vec2<T>& inc : incident ray.
 *    const _vec2<T>& nor : normal surface.
 *    T n : coefficient.
 * Return :
 *    _vec2<T> : transmitted ray.
 * ----------------------------------------------------------------------------
 */
/*TEMPLATE_DEF const _vec2<T> transmit(const _vec2<T> &inc, const _vec2<T> &nor, T n) {
// TODO
return inc;
}*/

/* ----------------------------------------------------------------------------
 * refract
 * ----------------------------------------------------------------------------
 * Description :
 *    Compute the refracted ray as:
 *
 *        n * inc -(n + sqrt(1 - n² * (1 - cos²(i)))) * nor
 *
 *    with n = n1 / n2 and i the angle between inc and nor.
 * Arguments :
 *    const _vec3<T>& inc : normalized incident ray.
 *    const _vec3<T>& nor : normalized normal surface.
 *    T n : coefficient (n1 / n2).
 * Return :
 *    _vec3<T> : refracted ray.
 * ----------------------------------------------------------------------------
 */
TEMPLATE_DEF const _vec2<T> refract(const _vec2<T>& inc, const _vec2<T>& nor, T n) {
  float cosiSqr = dot(inc, nor);  // cos(i)
  cosiSqr *= cosiSqr;             // cos²(i)

  float s = 1.0f;                 // 1
  s -= cosiSqr;                   // 1 - cos²(i)
  s *= n;                         // n * (1 - cos²(i))
  s *= -n;                        // -n² * (1 - cos²(i))
  s += 1.0f;                      // 1 - n² * (1 - cos²(i))

  float r = n;                    // n
  r += sqrtf(s);                  // n + sqrt(1 - n² * (1 - cos²(i)))

  _vec2<T> ref(n * inc);          // n * inc
  ref -= r * nor;                 // n * inc -(n + sqrt(1 - n² * (1 -cos²(i)))) * nor
  return ref;
}



// -------------------- Predefined vec2 types ---------------------------------

typedef _vec2<float> vec2;
typedef _vec2<float> vec2f;
typedef _vec2<double> vec2d;
typedef _vec2<int> vec2i;
typedef _vec2<unsigned int> vec2u;
typedef _vec2<unsigned char> vec2b;

};


#undef TEMPLATE_DEF

#endif

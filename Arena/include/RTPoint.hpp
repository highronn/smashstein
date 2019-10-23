#ifndef _RTPOINT_HPP_
#define _RTPOINT_HPP_

namespace RTPoint {

template<class T> class _Point3;
template<class T> class _Point2;

template<class T> class _Point4 {
               
public:
      
  T x, y, z, w;
    
  _Point4(const _Point4<T>& p):x(p.x),y(p.y),z(p.z),w(p.w){}
  
  _Point4(const T& x, const T& y, const T& z, const T& w):x(x),y(y),z(z),w(w){}
  
  _Point4(const _Point3<T>& p):x(p.x),y(p.y),z(p.z),w(T(0.0)){}
 
  _Point4(const _Point3<T>& p, const T& w):x(p.x),y(p.y),z(p.z),w(w){} 
  
  _Point4(const _Point2<T>& p):x(p.x),y(p.y),z(T(0.0)),w(T(0.0)){} 
  
  _Point4(const _Point2<T>& p, const T& z):x(p.x),y(p.y),z(z),w(T(0.0)){}
  
  _Point4(const _Point2<T>& p, const T& z, const T& w):x(p.x),y(p.y),z(z),w(w){}
  
  _Point4(const T& p):x(p),y(p),z(p),w(p){} 

  _Point4():x(0),y(0),z(0),w(0){} 
      
  const _Point4<T> operator+ (const _Point4<T>& p){ return _Point4<T>(x + p.x, y + p.y, z + p.z, w + p.w); }
  
  const _Point4<T> operator- (const _Point4<T>& p){ return _Point4<T>(x - p.x, y - p.y, z - p.z, w - p.w); }
  
  const _Point4<T> operator* (const _Point4<T>& p){ return _Point4<T>(x * p.x, y * p.y, z * p.z, w * p.w); }
  
  const _Point4<T> operator/ (const _Point4<T>& p){ return _Point4<T>(x / p.x, y / p.y, z / p.z, w / p.w); }
  
  _Point4<T>& operator+= (const _Point4<T>& p){ x += p.x; y += p.y; z += p.z; w += p.w; return *this; }
  
  _Point4<T>& operator-= (const _Point4<T>& p){ x -= p.x; y -= p.y; z -= p.z; w -= p.w; return *this; }
  
  _Point4<T>& operator*= (const _Point4<T>& p){ x *= p.x; y *= p.y; z *= p.z; w *= p.w; return *this; }
  
  _Point4<T>& operator/= (const _Point4<T>& p){ x /= p.x; y /= p.y; z /= p.z; w /= p.w; return *this; }
  
  const _Point4<T> operator= (const _Point4<T>& p) { x = p.x; y = p.y; z = p.z; w = p.w; return *this;}
  
  const _Point4<T> operator+ (const T& p){ return _Point4<T>(x + p, y + p, z + p, w + p); }
  
  const _Point4<T> operator- (const T& p){ return _Point4<T>(x - p, y - p, z - p, w - p); }
  
  const _Point4<T> operator* (const T& p){ return _Point4<T>(x * p, y * p, z * p, w * p); }

  const _Point4<T> operator/ (const T& p){ return _Point4<T>(x / p, y / p, z / p, w / p); }
  
  _Point4<T>& operator+= (const T& p){ x += p; y += p; z += p; w += p; return *this; }
  
  _Point4<T>& operator-= (const T& p){ x -= p; y -= p; z -= p; w -= p; return *this; }
  
  _Point4<T>& operator*= (const T& p){ x *= p; y *= p; z *= p; w *= p; return *this; }
  
  _Point4<T>& operator/= (const T& p){ x /= p; y /= p; z /= p; w /= p; return *this; }
  
  const _Point4<T> operator= (const T& p) { x = p; y = p; z = p; w = p; return *this;}
  
  bool operator==(const _Point4<T>& p){ return(x == p.x && y == p.y && z == p.z && w == p.w); }
  
  bool operator!=(const _Point4<T>& p){ return (x != p.x || y != p.y || z != p.z || w != p.w); }   

};

template<class T> std::ostream& operator<<(std::ostream& out, const _Point4<T> p){
    return out << p.x << " " << p.y << " " << p.z << " " << p.w;
  }

typedef _Point4<float> point4;
typedef _Point4<float> point4f;
typedef _Point4<double> point4d;
typedef _Point4<int> point4i;
typedef _Point4<unsigned int> point4u;
typedef _Point4<unsigned char> point4b;



template<class T> class _Point3 {
               
public:
      
  T x, y, z;
    
  _Point3(const _Point3<T>& p):x(p.x),y(p.y),z(p.z){}
  
  _Point3(const T& x, const T& y, const T& z):x(x),y(y),z(z){}
  
  _Point3(const _Point2<T>& p):x(p.x),y(p.y),z(T(0.0)){}
 
  _Point3(const _Point2<T>& p, const T& z):x(p.x),y(p.y),z(p.z){}
  
  _Point3(const T& p):x(p),y(p),z(p){}

  _Point3():x(0),y(0),z(0){}
      
  const _Point3<T> operator+ (const _Point3<T>& p){ return _Point3<T>(x + p.x, y + p.y, z + p.z); }
  
  const _Point3<T> operator- (const _Point3<T>& p){ return _Point3<T>(x - p.x, y - p.y, z - p.z); }
  
  const _Point3<T> operator* (const _Point3<T>& p){ return _Point3<T>(x * p.x, y * p.y, z * p.z); }
  
  const _Point3<T> operator/ (const _Point3<T>& p){ return _Point3<T>(x / p.x, y / p.y, z / p.z); }
  
  _Point3<T>& operator+= (const _Point3<T>& p){ x += p.x; y += p.y; z += p.z; return *this; }
  
  _Point3<T>& operator-= (const _Point3<T>& p){ x -= p.x; y -= p.y; z -= p.z; return *this; }
  
  _Point3<T>& operator*= (const _Point3<T>& p){ x *= p.x; y *= p.y; z *= p.z; return *this; }
  
  _Point3<T>& operator/= (const _Point3<T>& p){ x /= p.x; y /= p.y; z /= p.z; return *this; }
  
  const _Point3<T> operator= (const _Point3<T>& p) { x = p.x; y = p.y; z = p.z; return *this;} 
  
  const _Point3<T> operator+ (const T& p){ return _Point3<T>(x + p, y + p, z + p); }
  
  const _Point3<T> operator- (const T& p){ return _Point3<T>(x - p, y - p, z - p); }
  
  const _Point3<T> operator* (const T& p){ return _Point3<T>(x * p, y * p, z * p); }

  const _Point3<T> operator/ (const T& p){ return _Point3<T>(x / p, y / p, z / p); }
  
  _Point3<T>& operator+= (const T& p){ x += p; y += p; z += p; return *this; }
  
  _Point3<T>& operator-= (const T& p){ x -= p; y -= p; z -= p; return *this; }
  
  _Point3<T>& operator*= (const T& p){ x *= p; y *= p; z *= p; return *this; }
  
  _Point3<T>& operator/= (const T& p){ x /= p; y /= p; z /= p; return *this; }
  
  const _Point3<T> operator= (const T& p) { x = p; y = p; z = p; return *this;}
  
  bool operator==(const _Point3<T>& p){ return(x == p.x && y == p.y && z == p.z); }
  
  bool operator!=(const _Point3<T>& p){ return (x != p.x || y != p.y || z != p.z); }   

};

template<class T> std::ostream& operator<<(std::ostream& out, const _Point3<T> p){
    return out << p.x << " " << p.y << " " << p.z;
  }
  
typedef _Point3<float> point3;
typedef _Point3<float> point3f;
typedef _Point3<double> point3d;
typedef _Point3<int> point3i;
typedef _Point3<unsigned int> point3u;
typedef _Point3<unsigned char> point3b;



template<class T> class _Point2 {
               
public:
      
  T x, y;
    
  _Point2(const _Point2<T>& p):x(p.x),y(p.y){}
  
  _Point2(const T& x, const T& y):x(x),y(y){}
  
  _Point2(const T& p):x(p),y(p){} 

  _Point2():x(0),y(0){} 
      
  const _Point2<T> operator+ (const _Point2<T>& p){ return _Point2<T>(x + p.x, y + p.y); }
  
  const _Point2<T> operator- (const _Point2<T>& p){ return _Point2<T>(x - p.x, y - p.y); }
  
  const _Point2<T> operator* (const _Point2<T>& p){ return _Point2<T>(x * p.x, y * p.y); }
  
  const _Point2<T> operator/ (const _Point2<T>& p){ return _Point2<T>(x / p.x, y / p.y); }
  
  _Point2<T>& operator+= (const _Point2<T>& p){ x += p.x; y += p.y; return *this; }
  
  _Point2<T>& operator-= (const _Point2<T>& p){ x -= p.x; y -= p.y; return *this; }
  
  _Point2<T>& operator*= (const _Point2<T>& p){ x *= p.x; y *= p.y; return *this; }
  
  _Point2<T>& operator/= (const _Point2<T>& p){ x /= p.x; y /= p.y; return *this; }
  
  const _Point2<T> operator= (const _Point2<T>& p) { x = p.x; y = p.y; return *this;}
  
  const _Point2<T> operator+ (const T& p){ return _Point2<T>(x + p, y + p); }
  
  const _Point2<T> operator- (const T& p){ return _Point2<T>(x - p, y - p); }
  
  const _Point2<T> operator* (const T& p){ return _Point2<T>(x * p, y * p); }

  const _Point2<T> operator/ (const T& p){ return _Point2<T>(x / p, y / p); }
  
  _Point2<T>& operator+= (const T& p){ x += p; y += p;; return *this; }
  
  _Point2<T>& operator-= (const T& p){ x -= p; y -= p;; return *this; }
  
  _Point2<T>& operator*= (const T& p){ x *= p; y *= p;; return *this; }
  
  _Point2<T>& operator/= (const T& p){ x /= p; y /= p;; return *this; }
  
  const _Point2<T> operator= (const T& p) { x = p; y = p;; return *this;}
  
  bool operator==(const _Point2<T>& p){ return(x == p.x && y == p.y); }
  
  bool operator!=(const _Point2<T>& p){ return (x != p.x || y != p.y); }  
  
};

template<class T> std::ostream & operator << (std::ostream& out, const _Point2<T> p){
    return out << p.x << " " << p.y;
  }
  
typedef _Point2<float> point2;
typedef _Point2<float> point2f;
typedef _Point2<double> point2d;
typedef _Point2<int> point2i;
typedef _Point2<unsigned int> point2u;
typedef _Point2<unsigned char> point2b;


}

#endif

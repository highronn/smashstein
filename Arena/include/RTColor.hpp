#ifndef _RTCOLOR_HPP_
#define _RTCOLOR_HPP_

#include <iostream>

namespace RTColor
{
	template<class T> class _Color
	{
				   
		public:
			  
			T r, g, b, a;

			_Color(const _Color<T>& c):r(c.r),g(c.g),b(c.b), a(c.a){}

			_Color(const T& red, const T& green, const T& blue):r(red),g(green),b(blue),a(1.0f){}

			_Color(const T& red, const T& green, const T& blue, const T& alpha):r(red),g(green),b(blue),a(alpha){}

			_Color(const T& c, const T& a):r(c),g(c),b(c),a(a){}

			_Color(const T& c):r(c),g(c),b(c),a(c){}

			_Color():r(T(0.0)),g(T(0.0)),b(T(0.0)),a(T(1.0)){}  

			const _Color<T> operator+ (const _Color<T>& c){ return _Color<T>(r + c.r, g + c.g, b + c.b, a + c.a); }

			const _Color<T> operator- (const _Color<T>& c){ return _Color<T>(r - c.r, g - c.g, b - c.b, a - c.a); }

			const _Color<T> operator* (const _Color<T>& c){ return _Color<T>(r * c.r, g * c.g, b * c.b, a * c.a); }

			const _Color<T> operator/ (const _Color<T>& c){ return _Color<T>(r / c.r, g / c.g, b / c.b, a / c.a); }

			_Color<T>& operator+= (const _Color<T>& c){ r += c.r; g += c.g; b += c.b; a += c.a; return *this;}

			_Color<T>& operator-= (const _Color<T>& c){ r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this;}

			_Color<T>& operator*= (const _Color<T>& c){ r *= c.r; g *= c.g; b *= c.b; a *= c.a; return *this;}

			_Color<T>& operator/= (const _Color<T>& c){ r /= c.r; g /= c.g; b /= c.b; a /= c.a; return *this;}

			_Color<T> operator= (const _Color<T>& c) { r = c.r; g = c.g; b = c.b; a = c.a; return *this;} 

			/*******************************************************************************************/  

			const _Color<T> operator+ (const T& c){ return _Color<T>(r + c, g + c, b + c, a + c); }

			const _Color<T> operator- (const T& c){ return _Color<T>(r - c, g - c, b - c, a - c); }

			const _Color<T> operator* (const T& c){ return _Color<T>(r * c, g * c, b * c, a * c); }

			const _Color<T> operator/ (const T& c){ return _Color<T>(r / c, g / c, b / c, a / c); }

			_Color<T>& operator+= (const T& c){ r += c; g += c; b += c; a += c; return *this; }

			_Color<T>& operator-= (const T& c){ r -= c; g -= c; b -= c; a -= c; return *this; }

			_Color<T>& operator*= (const T& c){ r *= c; g *= c; b *= c; a *= c; return *this; }

			_Color<T>& operator/= (const T& c){r /= c; g /= c; b /= c; a /= c.a; return *this; }

			const _Color<T> operator= (const T& c) { r = c; g = c; b = c; a = c; return *this;} 

			/*******************************************************************************************/

			bool operator==(const _Color<T>& c){ return(r == c.r && g == c.g && b == c.b && a = c.a); }

			bool operator!=(const _Color<T>& c){ return (r != c.r || g != c.g || b != c.b || a != c.a); }  

			bool operator>(const _Color<T>& c){ return ((r + g + b + a) > (c.r + c.g + c.b + c.a)); }  

			bool operator>=(const _Color<T>& c){ return ((r + g + b + a) >= (c.r + c.g + c.b + c.a)); } 

			bool operator<(const _Color<T>& c){ return((r + g + b + a) < (c.r + c.g + c.b + c.a)); }

			bool operator<=(const _Color<T>& c){ return((r + g + b + a) <= (c.r + c.g + c.b + c.a)); }

			bool operator>(const T& c){ return(r > c && g > c && b > c && a > c); }  

			bool operator>=(const T& c){ return(r >= c && g >= c && b >= c && a >= c); } 

			bool operator<(const T& c){ return(r < c && g < c && b < c && a < c); }

			bool operator<=(const T& c){ return(r <= c && g <= c && b <= c && a <= c); }

		/*******************************************************************************************/
		  
		friend std::ostream& operator<< (std::ostream& out, const _Color<T>& c)
		{
			return out << c.r << " " << c.g << " " << c.b << " " << c.a; 
		} 
	};

	typedef _Color<float> color;
	typedef _Color<float> colorf;
	typedef _Color<double> colord;
	typedef _Color<int> colori;
	typedef _Color<unsigned int> coloru;
	typedef _Color<unsigned char> colorb;
}

#endif

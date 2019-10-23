/*********************************************************
 * Nom du fichier   : RTMath.hpp
 * Date de creation : ven 11 fév 2005
 * Auteur :
 * Description :
 * Version : 1.0
 * Contact :
 * Copyright : libRT@2005
 * Dernière mise à jour : ven 11 fév 2005
\*********************************************************/

#ifndef RTMATH_HPP
#define RTMATH_HPP
#include<stdlib.h>
#include<iostream>
#include<cmath>

namespace RTMath {

  /*!
    \brief \f$\pi\f$
  */
  const float RT_PI            = 3.14159265358979323846f;
  /*!
    \brief \f$2\pi\f$
  */
  const float RT_TWO_PI        = 2.0f * RT_PI;
  /*!
    \brief \f$\frac{\pi}{2}\f$
  */
  const float RT_HALF_PI       = 0.5f * RT_PI;
  /*!
    \brief \f$\frac{\pi}{4}\f$
  */
  const float RT_ONEFOURTH_PI  = 0.25f * RT_PI;
  /*!
    \brief exponentiel
  */
  const float RT_E             = 2.71828182845904523536f;
  /*!
    \brief \f$\sqrt{2}\f$
  */
  const float RT_SQRT_TWO      = 1.41421356237309504880f;
  /*!
    \brief \f$\sqrt{3}\f$
  */
  const float RT_SQRT_THREE    = 1.73205080756887729352f;
  /*!
    \brief \f$\sqrt{\frac{1}{2}}\f$
  */
  const float RT_SQRT_1OVER2   = 0.70710678118654752440f;
  /*!
    \brief \f$\sqrt{\frac{1}{3}}\f$
  */
  const float RT_SQRT_1OVER3   = 0.57735026918962576450f;
  /*!
    \brief coefficient multiplicateur pour passer des degrés en radians
  */
  const float RT_M_DEG2RAD     = RT_PI / 180.0f;
  /*!
    \brief coefficient multiplicateur pour passer des radians en degres
  */
  const float RT_M_RAD2DEG     = 180.0f / RT_PI;
  /*!
    \brief \f$\infty\f$ 
  */
  const float RT_INFINITY      = 1e15f;
  /*!
    \brief \f$\approx\f$ 0
  */
  const float RT_FLT_EPSILON   = 1.192092896e-07f; 
 /*!
    \brief le nombre d'or \f$\rho\f$
  */
  const float RT_GOLDEN_NUMBER = 1.61803398874989484820f;
  
  /*!
    \function isPowerOfTwo
    \brief Determine si la valeur passée en parametre est une puissance de 2.
    \param n un entier.
    \return true si n est une puissance de 2, flase sinon.
  */
  inline bool isPowerOfTwo(int n) 
  {
    return (n & (n - 1)) == 0 && n > 0;
  }

  /*!
    \function ceilPowerOfTwo
    \brief Retourne la plus grande puissance de 2 de n la plus proche.
    \param n un entier.
    \return La plus grande puissance de 2 la plus proche.
  */
  inline int ceilPowerOfTwo(int n) 
  {
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    ++n;
        return n;
    }

  /*!
    \function floorPowerOfTwo
    \brief Retourne la plus petite puissance de 2 de n la plus proche.
    \param n un entier.
    \return La plus petitepuissance de 2 la plus proche.
  */
  inline int floorPowerOfTwo(int n) 
  {
    return ceilPowerOfTwo(n) >> 1;
  }
  
  /*!
    \function degToRad
    \brief Convertie une valeur en degré en radian.
    \param deg la valeur en degré.
    \return la valeur en radian.
    \sa #radToDeg
  */
  template<class T> T degToRad(T deg) 
  {
    return deg * T(RT_M_DEG2RAD);
  }

  /*!
    \function radToDeg
    \brief Convertie une valeur en radian en degré.
    \param deg la valeur en radian.
    \return la valeur en degré.
    \sa #degToRad
  */
  template<class T> T radToDeg(T rad) 
  {
    return rad * T(RT_M_RAD2DEG);
  }
  
  /*!
    \function factorial
    \brief Calcul du factoriel de l'entier passé en parametre.
    \param x le factoriel recherché.
    \return le factoriel de x (x!).
  */
  inline int factorial(int x)
  {
    int i, factx = 1;
    for(i=1; i<=x ; ++i)
      factx *= i;
    return factx;
  }

  /*!
    \function rsqrtf
    \brief Calcul de 1/sqrt(x) à une precision de 64 bits.
    \param x la racine inverse recherchée.
    \return 1/sqrt(x).
    
    Ce code vient d'Id-Software.
  */
  /*inline float rsqrtf(float x)
  {
    float vhalf = x * 0.5f;
    long i = * (long *) &x;
    i = 0x5f3759df - (i>>1);
    x = * (float *) &i;
    return x * ( 1.5f - vhalf * x * x );
  }*/
  
  /*!
    \function getRandom
    \brief Determine une valeur aleatoire entre x et 0.
    \param x la borne.
    \return une valeur aleatoire compris entre x et 0.
  */
  template<class T> T getRandom(T x)
  {
    if(x<T(0))
      x=-x;

    return T(float(x) * float(rand())/float(RAND_MAX));
  }
  
}

#endif

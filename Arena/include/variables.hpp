/* 
 * File:   variables.hpp
 * Author: alexandre
 *
 * Created on 24 décembre 2009, 02:06
 */

#ifndef _VARIABLES_HPP
#define	_VARIABLES_HPP

#include <iostream>
#include <cstdio>
#include <vector>

#include <Robots.hpp>
#include <Mesh.hpp>
#include <MD2Model.hpp>
#include <QTime>

#define NB_ARENA 2
#define NB_CHARACTER 4

#define ROME 1
#define MOMOSHIRO 2

typedef enum enumCollisionFace{TOP, BOTTOM, LEFT, RIGHT, NONE} collisionFace;

extern QTime TIMER;
extern int TEST;
//extern Vertex TARGET;
//extern GLUquadric* TARGET_S;

#endif	/* _VARIABLES_HPP */


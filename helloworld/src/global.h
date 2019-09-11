/*
 * global.h
 *
 *  Created on: Jun. 18, 2019
 *      Author: kusha
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "global.h"

class Character;
class Player;
class Game;

extern const int score_size = 10;
struct score;
void collision(float x, float y, float h, float w, int m1[3][17][50], float a, int m_n, score a_score, int end);

#endif /* GLOBAL_H_ */

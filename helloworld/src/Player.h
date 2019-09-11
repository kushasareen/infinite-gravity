/*
 * Player.h
 *
 *  Created on: Jun. 18, 2019
 *      Author: kusha
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "global.h"
#include "Character.h"

class Player : public Character { //stores information for player

	const static float height;
	const static float width;

public:

	// constructors and access functions

	Player() : Character() {

	}

	Player(float a_x, float a_y, float a_vx, float a_vy, int a_g) : Character(a_x, a_y, a_vx, a_vy, a_g) {

	}

	float getHeight() {
		return height;

	}

	float getWidth() {
		return width;

	}


};

const float Player::height = 0.3;
const float Player::width = 0.1;




#endif /* PLAYER_H_ */

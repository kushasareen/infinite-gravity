/*
 * Character.h
 *
 *  Created on: Jun. 18, 2019
 *      Author: kusha
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "global.h"

class Character { //class that stores information for a character in the gam

	float x; //x pos
	float y; //y pos
	float v_x; // x vel
	float v_y; //y vel
	int g; //gravity direction

public:
	Character() { //default constructor

	}

	Character(float a_x, float a_y, float a_vx, float a_vy, int a_g) { //constructor with initial conditions
		x = a_x;
		y = a_y;
		v_x = a_vx;
		v_y = a_vy;
		g = a_g;
	}

	void incrementMovement() {
		x += v_x;
		y += v_y;

	}

	void gravity(){ //acceleration due to gravity
		v_y -= 0.002*g;
	}

	//access functions
	float getX() const {
		return x;
	}
	void setX(float a_x) {
		x = a_x;
	}
	float getY() const {
		return y;
	}
	void incY(float inc) {
		y += inc;
	}
	float getV_x() const {
		return v_x;
	}
	float getV_y() {
		return v_y;
	}
	void setV_y(float a_vy){
		v_y = a_vy;
	}
	void setY(float a_y) {
		y = a_y;
	}
	void setV_x(float a_vx) {
		v_x = a_vx;
	}
	void reverseGrav(){
		g *= -1;
	}
	int getG() const {
		return g;
	}

};




#endif /* CHARACTER_H_ */

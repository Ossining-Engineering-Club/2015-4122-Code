/*
 * Lift.h
 *
 *  Created on: Feb 3, 2015
 *      Author: ossining
 */

#ifndef LIFT_H_
#define LIFT_H_
#include "WPIlib.h"

class Lift {
public:
	Lift(uint32_t liftchannel, uint32_t grabchannel);
	void MoveVertical(float);
	void OpenAndClose(float);
	void SetThrottle(float);
	void SetSpeed(float);

private:
	Jaguar liftmotor;
	Jaguar grabmotor;

	float throttle;
	float speed;
	float liftStickValue;
	float openStickValue;
};

#endif /* ROBOT2015_V1_1__LIFT_ATTEMPT__SRC_LIFT_H_ */

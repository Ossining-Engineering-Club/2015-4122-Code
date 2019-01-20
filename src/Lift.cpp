/*
 * Lift.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: ossining
 */
#include "Lift.h"
#include "WPILib.h"

Lift::Lift(uint32_t liftchannel, uint32_t grabchannel):
liftmotor(liftchannel),
grabmotor(grabchannel)
{
 liftStickValue=0;
 openStickValue=0;
 throttle=0;
 speed=0;

}

void Lift::MoveVertical(float liftStickValue)
{
	liftmotor.Set(speed*liftStickValue);
}

void Lift::OpenAndClose(float openStickValue)
{
	grabmotor.Set(-speed* openStickValue);
}

void Lift::SetThrottle(float throttle)
{
	speed = 0.5*(1 - throttle);
}

void Lift::SetSpeed(float input)
{
	speed = -input;
}



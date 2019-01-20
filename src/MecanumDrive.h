/*
 * mecanumDrive.h
 *
 *  Created on: Jan 8, 2015
 *      Author: ossining
 */

#ifndef MECANUMDRIVE_H_
#define MECANUMDRIVE_H_
#include "WPIlib.h"

class mecanumDrive {

	public:
		mecanumDrive(uint32_t frontLeftMotorChannel, uint32_t rearLeftMotorChannel,
				uint32_t frontRightMotorChannel, uint32_t rearRightMotorChannel);
		void Drive(float leftx, float lefty, float rightx, float righty);
		void SetThrottle(float);	//Change the throttle setting
		void SetSpeed(float);

	private:
	    RobotDrive drive;    // robot drive system
		float scalespeed;
		float xValue, yValue, rValue, zValue;
};

#endif /* MECANUMDRIVE_H_ */

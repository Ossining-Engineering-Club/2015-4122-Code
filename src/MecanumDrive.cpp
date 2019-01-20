/*
 * mecanumDrive.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: ossining
 */

#include "mecanumDrive.h"
#include "WPILib.h"

mecanumDrive::mecanumDrive(uint32_t frontLeftMotorChannel, uint32_t rearLeftMotorChannel,
				uint32_t frontRightMotorChannel, uint32_t rearRightMotorChannel):
drive(frontLeftMotorChannel, rearLeftMotorChannel, frontRightMotorChannel, rearRightMotorChannel)
{
	drive.SetExpiration(0.1);
	//Initialize all values to zero
	xValue=0;
	yValue=0;
	rValue=0;
	zValue=0; //for the gyro angle
	scalespeed=0;


}

void mecanumDrive::Drive(float leftx, float lefty, float rightx, float righty)
{
	/* Compute x, y and r values, inverting sign for left joystick */
	xValue = scalespeed * (  leftx + rightx ) / 2.0;
	yValue = scalespeed * (- lefty + righty ) / 2.0;
	rValue = scalespeed * (- lefty - righty ) / 2.0;
	//zValue = ;
	drive.MecanumDrive_Cartesian(xValue, yValue, rValue, zValue); // drive with the joysticks
}

void mecanumDrive::SetThrottle(float throttle)
{
	// Convert Throttle from the range of -1 to 1 to the range of 0 to 1
	// The new scalespeed will be used on next xValue, YValue and rValue
	scalespeed = 0.5 * ( 1.0 - throttle );
}

void mecanumDrive::SetSpeed(float throttle)
{
	// Convert Throttle from the range of -1 to 1 to the range of 0 to 1
	// The new scalespeed will be used on next xValue, YValue and rValue
	scalespeed = -throttle;
}





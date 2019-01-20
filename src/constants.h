/*
 * constants.h
 *
 *  Created on: Jan 21, 2015
 *      Author: ossining
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define feetpervolt 8.503   // Feet per volt for US Sensor using 5 V power Supply

/*
 * AUTONOMOUS MODE Constants
 * Times are in Seconds
 * Speeds are Throttle Settings
 */

// BUMP is the initial siight drive to the container so it is not initially touching
#define BUMP_TIME 		0.9		// Time for Bump Drive
#define BUMP_SPEED 		0.2	// Throttle for Bump Drive was .2

// Drive Forward time
#define DRIVE_M_TIME 	3.0	//Drive Forward time from Middle Position
#define DRIVE_L_TIME 	2.3	//Drive Forward time from Left Position
#define DRIVE_R_TIME 	2.7 //Drive forward time from Right Position
#define DRIVE_SPEED 	0.0 // was .35

// Angles to Turn Left ahd Right - May have to be switched
#define TURN_INVERT		1		// Invert if Turns are the wrong way
#define TURN_SPEED		0.0 //was .4	//Throttle value when turning

// Drive Across Field Time
#define DRIVE_L_TIME2 	2.0	//Drive Acroos field time from Left Side
#define DRIVE_R_TIME2 	2.0	//Drive Across Field time from Right Side
#define DRIVE_SPEED2 	0.0 // was .35

// Gyro time backup
#define MAX_GYRO_TIME 3.5 //Moves onto the next part if gyro does not work in this time

// Time to Backup After Placing Container
#define BACKUP_TIME 	0.2
#define BACKUP_SPEED 	0.0 //was .35

#define LIFT_THROTTLE 	0.5

#define LIFT1			1.7
#define LOWER1			2.0

#define LIFT2			3.0
#define LOWER2			3.0

#define LIFT3			4.5
#define LOWER3			4.5


#endif /* CONSTANTS_H_ */

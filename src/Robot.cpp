#include "mecanumDrive.h"
#include "Pneumatics.h"
#include "Lift.h"
#include "USSensor.h"
#include "WPILib.h"
#include "constants.h"
#include <unistd.h>
#include <stdio.h>

auto grip = NetworkTable::GetTable("grip");
const char *JAVA = "/usr/local/frc/JRE/bin/java";
char *GRIP_ARGS[5] = { "java", "-jar", "/home/lvuser/grip.jar", "/home/lvuser/project.grip", NULL };

class Robot: public SampleRobot
{
private:
	mecanumDrive mecdrive;
	Pneumatics pneumatics;
	Lift lift;
	Joystick rightStick;
	Joystick leftStick;
	Joystick liftStick;
	//Gyro gyro;
	USSensor ussensor;
	SmartDashboard *dash;
	Timer autoTimer;
	DigitalInput input0; // lift height = 0
	DigitalInput input1; // lift height = 1
	DigitalInput input2; // lift height = 2
	DigitalInput input3; // lift height = 3

	DigitalInput input7; // left side position
	DigitalInput input8; // middle
	DigitalInput input9; // right side



public:
	Robot() :
		mecdrive(2, 3, 4, 1),	// mecanum drive in ports 2, 3, 4, and 1
		pneumatics(0,0,1),
		lift(5,6),				// lift motor in ports 5 and 6
		rightStick(0),			// right stick should be 0 on the driver station
		leftStick(1),			// left stick should be 1 on the driver station
		liftStick(2),			// lift stick should be 2 on the driver station
 		//gyro(),				// gyro should be in port 0 and is analog
        ussensor(1),			// ultrasonic sensor (if we are using one) should be in port 1
		dash(),
		input0(0),
		input1(1), // lift height = 1
		input2(2), // lift height = 2
		input3(3), // lift height = 3

		input7(7), // left side position
		input8(8), // middle
		input9(9) // right side
	{
			dash->init();
			dash->PutBoolean("AUTO RUN",0);				//informs if robot is running is automomous
			dash->PutString("Version","Code V2.7");		//check on the dashboard to make sure your program has been updated

	}


	/**
	 * Runs the motors with arcade steering.
	 */
	void Autonomous()
	{
		//Height that lift will go for stacking: 0= Push 1= Lift for Bottom Layer, 2 = 2nd layer, 3 = 3rd Layer
		float liftTime=0;
		float lowerTime=0;
		float delayTime=0;
		enum start_positions {LEFT, MIDDLE, RIGHT};
		start_positions position=MIDDLE;

		dash->PutBoolean("AUTO RUN",1);
		//dash->PutNumber("Gyro", gyro.GetAngle());	//gyro gets angel value
		/* these next 7 lines tell you on the dashboard what input the digital I/O is reciving from the robot
		and these inputs determine what actions the robot preforms in automonous*/
		dash->PutBoolean("input0",!input0.Get());
		dash->PutBoolean("input1",!input1.Get());
		dash->PutBoolean("input2",!input2.Get());
		dash->PutBoolean("input3",!input3.Get());

		dash->PutBoolean("input7",!input7.Get());
		dash->PutBoolean("input8",!input8.Get());
		dash->PutBoolean("input9",!input9.Get());

		/* if the digital I/O gets the input of 8 the robot will recieve instructions to
		run the program regarding when it is in the middle of the field (if the it is 7 it will be left
		and if it is 9 it will be right*/


		if(!input8.Get()){position=MIDDLE, dash->PutString("route", "middle");}
		else if(!input7.Get()){position=LEFT, dash->PutString("route", "left");}
		else if(!input9.Get()){position=RIGHT, dash->PutString("route", "right");}
		else position= MIDDLE;


		 	 	 /* the digital I/O gets a value of 0 it will not pick anything up (the lift will not be activated)
		 	 	 if the digialt I/O gets an input of 1 it will go to the constants.h to see what LIFT1 and LOWER1 are declared as
		 	 	 to lift it up a certain amount and but it down a certain amount, the same if the input is 2,3
		 	 	 the LIFT(number) and the LOWER(number) are different becuase if you start out some place different on the play
		 	 	 area you may need to lift are lower by a different amount (in the next 6 lines)*/


		lift.SetSpeed(LIFT_THROTTLE);
		if(!input0.Get()){liftTime=0; lowerTime=0; dash->PutString("Lift Height", "0");}
		else if(!input1.Get()){liftTime=LIFT1; lowerTime=LOWER1; dash->PutString("Lift Height", "1");}
		else if(!input2.Get()){liftTime=LIFT2; lowerTime=LOWER2; dash->PutString("Lift Height", "2");}
		else if(!input3.Get()){liftTime=LIFT3; lowerTime=LOWER3; dash->PutString("Lift Height", "3");}
		else {liftTime=LIFT1; lowerTime=LOWER1; dash->PutString("Lift Height", "defualt 1");}


		autoTimer.Reset(); //Reset timer first so time starts at 0
		autoTimer.Start(); //Start the timer for Autonomous
		//gyro.Reset();		//reset gyro for autonomous

		//Do delay first if a Delay was requested
		while(autoTimer.Get() < delayTime)
		{
				Wait(.01);
		}

		switch(position)
		{
			case (LEFT):	//if the digital I/O get a value of left (input 7) do this
			{
				// Drive to Bump the Box
				while(autoTimer.Get() < BUMP_TIME)		// while the BUMP TIME is greater then the autotimer run autonoums
				{
					Wait(.01);
					mecdrive.SetSpeed(BUMP_SPEED);	// BUMP_SPEED loacted in constants.h and deteermines the speed when goes over a bump
					mecdrive.Drive(0,1,0,1);		// more forward
				}
				mecdrive.Drive(0,0,0,0);			// stop moving
				autoTimer.Reset();					// reset timer for autonomous
				// Lift the Box
				while(autoTimer.Get() < liftTime)	// while the liftTime is greater than the autotimer move the lift stick up
				{
					Wait(.01);
					lift.MoveVertical(1.0);			// move the lift stick up
				}
				lift.MoveVertical(0);
				autoTimer.Reset();

				// Drive Forward
				while(autoTimer.Get() < DRIVE_L_TIME)
				{
					Wait(.01);
					mecdrive.SetSpeed(DRIVE_SPEED);		// in constants.h
					mecdrive.Drive(0,-1,0,-1); // backwards drive
				}
				mecdrive.Drive(0,0,0,0);		// stop moving
				autoTimer.Reset();
				while(autoTimer.Get() < lowerTime)
				{
					Wait(.01);
					lift.MoveVertical(-1.0);	// move the lift stick down
				}
				lift.MoveVertical(0);			// stop moving the lift stick
				autoTimer.Reset();
				while(autoTimer.Get() < BACKUP_TIME)
				{
					Wait(.01);
					mecdrive.SetSpeed(BACKUP_SPEED);		// in constants.h
					mecdrive.Drive(0,-1,0,-1);				// move backwards
				}
				mecdrive.Drive(0,0,0,0);					//stop moving
				autoTimer.Reset();
				break;
			}
			case (MIDDLE):									// if the Digital I/O gets a reading of middle (input 8)
			{
				while(autoTimer.Get() < BUMP_TIME)
				{
					Wait(.01);
					mecdrive.SetSpeed(BUMP_SPEED);			// in constants.h
					mecdrive.Drive(0,1,0,1);				// move forward
				}
				mecdrive.Drive(0,0,0,0);					// stop moving
				autoTimer.Reset();
				while(autoTimer.Get() < liftTime)
				{
					Wait(.01);
					lift.MoveVertical(1);					// move the lift stick up
				}
				lift.MoveVertical(0);						// stop moving the lift stick
				autoTimer.Reset();
				while(autoTimer.Get() < DRIVE_M_TIME)		// DRIVE_M_TIME is in constants.h
				{
					Wait(.01);
					mecdrive.SetSpeed(DRIVE_SPEED);			// DRIVE_SPEED in constants.h
					mecdrive.Drive(0,-1,0,-1);				// move backwards
				}
				mecdrive.Drive(0,0,0,0);					// stop moving
				autoTimer.Reset();
				while(autoTimer.Get() < lowerTime)
				{
					Wait(.01);
					lift.MoveVertical(-1);					// lower the lift stick
				}
				lift.MoveVertical(0);						// stop moving the lift stick
				autoTimer.Reset();
				while(autoTimer.Get() < BACKUP_TIME)		// BACKUP_TIME in constants.h
				{
					Wait(.01);
					mecdrive.SetSpeed(BACKUP_SPEED);		// BACKUP_SPEED is in constants.h
					mecdrive.Drive(0,-1,0,-1);				// move backward
				}
				mecdrive.Drive(0,0,0,0);					// stop moving
				autoTimer.Reset();
				break;
			}
			case (RIGHT):									// if the Digital I/O gets a value of right (input 9)
			{
				while(autoTimer.Get() < BUMP_TIME)			// BUMP_TIME is in constants.h
				{
					Wait(.01);
					mecdrive.SetSpeed(BUMP_SPEED);			// BUMP_SPEED is in constants.h
					mecdrive.Drive(0,1,0,1);				// move forward
				}
				mecdrive.Drive(0,0,0,0);					// stop moving
				autoTimer.Reset();
				while(autoTimer.Get() < liftTime)
				{
					Wait(.01);
					lift.MoveVertical(1);					// move the lift up
				}
				lift.MoveVertical(0);						// stop moving the lift
				autoTimer.Reset();
				while(autoTimer.Get() < DRIVE_R_TIME)		// DRIVE_R_TIME in constants.h
				{
					Wait(.01);
					mecdrive.SetSpeed(DRIVE_SPEED);			// DRIVE_SPEED in constants.h
					mecdrive.Drive(0,-1,0,-1);				// move backward
				}
				mecdrive.Drive(0,0,0,0);					// stop moving
				autoTimer.Reset();
				//gyro.Reset();								// reset gyro
				/*while(fabs(gyro.GetAngle()) < 90 && autoTimer.Get() < MAX_GYRO_TIME)			//Use Absolute value so Turn works in either direction
				{
					Wait(.01);
					dash->PutNumber("Gyro", gyro.GetAngle());		// put the gyro's angle and display it on the dashboard
					mecdrive.SetSpeed(DRIVE_SPEED);					// set the mecanum drive speed to the value of DRIVE_SPEED located in constants.h
					mecdrive.Drive(0,TURN_INVERT,0,-TURN_INVERT);	// this is used to make the robot turn ( in this situation we want it to turn 90 degrees)
				}*/
				mecdrive.Drive(0,0,0,0);							// stop moving
				autoTimer.Reset();
				while(autoTimer.Get() < DRIVE_R_TIME2)
				{
					Wait(.01);
					mecdrive.SetSpeed(DRIVE_SPEED2);				// set the speed to the value of DRIVE_SPEED2 located in constants.h
					mecdrive.Drive(0,1,0,1);						// move forward
				}
				mecdrive.Drive(0,0,0,0);							// stop moving
				autoTimer.Reset();
				while(autoTimer.Get() < lowerTime)
				{
					Wait(.01);
					lift.MoveVertical(-1);							// move the lift down
				}
				lift.MoveVertical(0);								// stop moving the lift
				autoTimer.Reset();
				while(autoTimer.Get() < BACKUP_TIME)
				{
					Wait(.01);
					mecdrive.SetSpeed(BACKUP_SPEED);				// set the new speed of the mecanum drive to the value of BACKUP_SPEED located in constants.h
					mecdrive.Drive(0,-1,0,-1);						// move backwards
				}
				mecdrive.Drive(0,0,0,0);							// stop moving
				autoTimer.Reset();
				break;
			}
		}
		dash->PutBoolean("AUTO RUN",0);								// once done with autonomous the AUTO RUN  on the dashboard will be false
	}
	void OperatorControl()							// when driver is controlling the robot
	{
		pneumatics.Enable();
		//gyro.Reset();

		while (IsOperatorControl() && IsEnabled())				// while operating control is enabled to this
		{
			mecdrive.SetThrottle(rightStick.GetZ());			// set the throttle to whatever the driver sets it to (for the right stick)
			lift.SetThrottle(liftStick.GetZ());					// set the throttle to whatever the driver sets it to (for the left stick)
	//		blue->Set(Relay::Value::kOn);
			for (int i = 0 ; i < 10; ++i)
			{
				// FAST Response activities run every 10 msec are put here

				// Drive Bot using Mecanum Drive
				mecdrive.Drive(leftStick.GetX(),leftStick.GetY(),rightStick.GetX(),rightStick.GetY());

				//code for the lift mechanism

				lift.MoveVertical(liftStick.GetY());				// if the lift stick is moved in the Y direction the lift stick will move up and down at the driver's will
				lift.OpenAndClose(liftStick.GetX());				// if the lift stick is moved in the X direstion the lift stick will move in and out to grap a tote at the driver's will

				//code for the gyroscope


				Wait(0.005);	// wait for a motor update time
			}

			// SLOW CODE after this is run every 100 msec


			if (liftStick.GetRawButton(2)) // solenoid on
			{
				pneumatics.ShiftGear(true);

			}else if(liftStick.GetRawButton(3)) // solenoid off
			{
				pneumatics.ShiftGear(false);
			}

			if (liftStick.GetRawButton(4)) // compressor on/off
				pneumatics.AllowCompress(true);
			else
				pneumatics.AllowCompress(false);


			/* DASHBOARD VALUES */
			dash->PutNumber("Throttle",rightStick.GetZ());
			dash->PutNumber("Right X",rightStick.GetX());
			dash->PutNumber("Right Y",rightStick.GetY());
			dash->PutNumber("Left X",leftStick.GetX());
			dash->PutNumber("Left Y",leftStick.GetY());
			dash->PutBoolean("Button 2",liftStick.GetRawButton(2));
			dash->PutBoolean("Button 3",liftStick.GetRawButton(3));
			dash->PutBoolean("Button 4",liftStick.GetRawButton(4));
			dash->PutBoolean("Compressor", pneumatics.GetCompState());
			//dash->PutNumber("Gyro", gyro.GetAngle());
			dash->PutNumber("USSensor (Feet)", ussensor.GetRange());


		}
	}

};

START_ROBOT_CLASS(Robot);

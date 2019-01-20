/* Control Pneumatics
 *
 */
#ifndef Pneumatics_H_	//Checks to see whether this header is defined
#define Pneumatics_H_	//Defines header file
#include "WPILib.h"	//Includes WPI Library for Joysticks, Jaguars

class Pneumatics	//Declaring class
{
	public:	//Stuff in here can be accessed from other classes
		Pneumatics(uint32_t compressChan, uint32_t compressSwitchChan,uint32_t gearChan);
		void Enable();	//Enable Compressor
		void Disable(); // Prevent Compressor from Running
		void ShiftGear(bool);			//ShiftGear is set to false for Low Gear, true for High Gear
		void AllowCompress(bool);
		bool GetCompState();
	private:	//Stuff accessible only to this class

		Compressor compressor;
		Solenoid gearShift;
		bool wasTriggerPressed;     //for Pass trigger
		bool compressButtonDown;	//True when Button 5 is pressed
		bool compressButtonNew;		//True when it is a new button Press
		bool compressState;			//Compressor is on (1) or off (0)
		float speed;
		bool gear;
		bool wasOn;//for use with pass
};
#endif//ends header file definition

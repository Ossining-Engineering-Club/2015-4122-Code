#include "Pneumatics.h"
//#include "Compressor.h"//Includes header file where all methods are declared
#include "WPILib.h"	//includes WPI library for jaguars
//constructor method, sets jaguar channels
Pneumatics::Pneumatics(uint32_t compressChan, uint32_t compressSwitchChan,uint32_t gearChan):
compressor(compressChan),
gearShift(gearChan)

	{
		gear=false;
		gearShift.Set(false);
		compressButtonNew=true;
		wasOn=false;
		wasTriggerPressed = false;
		compressButtonDown = false;
		compressState = false;
		speed = 0.0; //speed takes float
		compressor.SetClosedLoopControl(0);
	}

void Pneumatics::ShiftGear(bool gearPos)//shifts gear to true or false (solenoid)
{
	gearShift.Set(gearPos);
}
void Pneumatics::Enable()
{
	compressor.Start();
}
void Pneumatics::Disable()
{
	compressor.Stop();
}
bool Pneumatics::GetCompState()
{
//	return compressor.Enabled();
	return compressState;
}

void Pneumatics::AllowCompress(bool isPressed)//handles the switching of the compressor on or off from the implementing class
{
	compressButtonDown=isPressed;
	if(compressButtonDown && compressButtonNew)
	{
		if(!compressor.Enabled())  {compressor.Start(); compressState = true;}
		else {compressor.Stop(); compressState = false;}
		compressButtonNew=false;
	}
	else if(!compressButtonDown) compressButtonNew=true;
}

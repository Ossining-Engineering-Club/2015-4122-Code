#include "USSensor.h"
#include "WPILib.h"

USSensor::USSensor(uint32_t channel):
	uschannel(channel)
{
	averagerange=0.0;
}

void USSensor::GetSample(void)
{
	averagerange=0.9*averagerange+0.1*8.503*uschannel.GetVoltage();
}

float USSensor::GetRange(void)
{
	averagerange =0.9*averagerange+0.1*8.503*uschannel.GetVoltage();
	return averagerange;
}


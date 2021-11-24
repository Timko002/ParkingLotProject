#include "ParkingSpace.h"
bool ParkingSpace::checkIsFull()
{
	// If any one timeSlot is true, i.e. free return false
	// Else return true
	for (int i = 0; i <= AVAILABILITY_OF_TIME_SLOT; i++)
	{
		if (timeSlot[i] == true)
			return false;
	}
	return true;

}

/*9:00 = 0
  9:15 = 1
  9:30 = 2
  ...
  6:00 = 36
*/
bool ParkingSpace::reserve(int start_hour, int start_min, int blocks)
{
	int starting_index;
	int starting_hour_index = (start_hour * 4) - 36;
	bool flag = true;
	switch (start_min)
	{
	case 15:
		starting_index = starting_hour_index + 1;
		break;
	case 30:
		starting_index = starting_hour_index + 2;
		break;
	case 45:
		starting_index = starting_hour_index + 3;
		break;
	default:
		starting_index = starting_hour_index;
	}

	for (int i = starting_index; i <= starting_index + blocks; i++)
	{
		if (timeSlot[i] == false)
		{
			flag = false;
			break;
		}
	}
	if (flag == true)
	{
		for (int i = starting_index; i <= starting_index + blocks; i++)
			timeSlot[i] = false;
	}
	return flag;
}

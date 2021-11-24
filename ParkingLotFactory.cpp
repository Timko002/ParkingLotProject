#include "ParkingLotFactory.h"
ParkingLot* ParkingLotFactory::chooseParkingLot(string LotName)
{
	ParkingLot* Lot;
	 
	if (LotName == "A")
		Lot = LotA::getInstance();
	else
		if (LotName == "B")
			Lot = LotB::getInstance();
		else
			if (LotName == "C")
				Lot = LotC::getInstance();
			else
				if (LotName == "D")
					Lot = LotD::getInstance();
				else
					if (LotName == "E")
						Lot = LotD::getInstance();
					else
						if (LotName == "F")
							Lot = LotD::getInstance();
						else
							if (LotName == "G")
								Lot = LotD::getInstance();
							else
								if (LotName == "H")
									Lot = LotD::getInstance();
								else
									if (LotName == "I")
										Lot = LotD::getInstance();
									else
										if (LotName == "J")
											Lot = LotD::getInstance();
										else
											Lot = NULL;
	return Lot;
}
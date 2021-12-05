#include "ParkingLotFactory.h"
//factory method to get the lot instances
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
						Lot = LotE::getInstance();
					else
						if (LotName == "F")
							Lot = LotF::getInstance();
						else
							if (LotName == "G")
								Lot = LotG::getInstance();
							else
								if (LotName == "H")
									Lot = LotH::getInstance();
								else
									if (LotName == "I")
										Lot = LotI::getInstance();
									else
										if (LotName == "J")
											Lot = LotJ::getInstance();
										else
											Lot = NULL;
	return Lot;
}
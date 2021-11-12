#ifndef PSPOTCOMPOSITE_H
#define PSPOTCOMPOSITE_H

#include <iostream>
#include <vector>
#include "PSpotComponent.h"

using namespace std;

class PSpotComposite : public PSpotComponent
{
	vector < PSpotComponent* > spots;

	public:
		void add(PSpotComponent* ele)
		{
			spots.push_back(ele);
		}
		void spotDetails()
		{
			for (int i = 0; i < spots.size(); i++)
				// 5. Use polymorphism to delegate to children
				spots[i]->spotDetails();
		}
};
#endif // !PSPOTCOMPOSITE_H

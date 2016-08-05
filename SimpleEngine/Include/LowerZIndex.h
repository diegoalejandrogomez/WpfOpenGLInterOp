#pragma once
#include "SimpleLayer.h"

struct LowerZIndex
{
	inline bool operator() (SimpleLayer* struct1, SimpleLayer* struct2)
	{
		return (struct1->GetZ() < struct2->GetZ());
	}
};
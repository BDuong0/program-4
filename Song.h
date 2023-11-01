#pragma once
#include "Media.h"


class Song : public Media {
public:
	Song();

	bool getTop40() { return top40; }
	void setTop40(bool setTop40) { top40 = setTop40; }

private:
	bool top40;
};
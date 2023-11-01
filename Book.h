#pragma once
#include "Media.h"


class Book : public Media {
public:
	Book();

	int getWeeks() { return weeksNYT; }
	void setWeeks(int weeks) { weeksNYT = weeks; }

private:
	int weeksNYT;
};
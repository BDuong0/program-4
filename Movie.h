#pragma once
#include "Media.h"

class Movie : public Media {
	public:
		Movie();

		vector<string> getStars() { return stars; }
		void setStars(vector<string> new_stars) { stars = new_stars; }
		
	private:
		vector<string> stars;
};
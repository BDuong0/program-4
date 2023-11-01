#include "Movie.h"

Movie::Movie() : Media() {
	stars = { "None1", "None2" };

	++num_movies;
	++total_items;
}


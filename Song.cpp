#include "Song.h"

Song::Song() : Media() {
	top40 = false;

	++num_songs;
	++total_items;
}
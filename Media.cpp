#include "Media.h"
using namespace std;

Media::Media() {
	type = 'N';
	title = "None";
	keyName = "None";
	rating = 0;
	genre = "None";
	length = 0;
	yearReleased = 0;
}

Media::Media(char typ, string tle, string kn, int r, string g, int l, int yr) {
	type = typ;
	title = tle;
	keyName = kn;
	rating = r;
	genre = g;
	length = l;
	yearReleased = yr;
}


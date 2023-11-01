#pragma once
#include "function.h"

/*  ===================================
	Functions to Read and Process Input
	===================================
*/  

int readMediaList(istream& i, ostream& o, vector<Media*>& m, vector<Movie>& movies, vector<Book>& books, vector<Song>& songs) {
	istringstream input_line;
	string file_text;

	Media temp_media;


	// Go through each line in mediaList.txt
	while (getline(i, file_text)) {
		try {
			input_line.clear();
			input_line.str(file_text);

			// Read first character M, B, S.. etc. of each line of text and call corresponding function
			if (file_text[0] == 'M') {
				readMovieinput(file_text, o, m, movies);
			}
			else if (file_text[0] == 'B') {
				//cout << "BOOK DETECTED: ";
				//cout << file_text;
				readBookinput(file_text, o, m, books);
			}
			else if (file_text[0] == 'S') {
				//cout << "Song Detected: ";
				//cout << file_text;
				readSonginput(file_text, o, m, songs);
			}
			else {
				//cout << file_text;
			}

			cout << "Processing mediaList.txt ..." << endl;
		}
		catch (runtime_error& error) { // Invalid Rating Error
			// Prints the error message passed by throw statement
			o << "ERROR: " << file_text << endl;
			o << error.what() << endl << endl;
		}
		catch (invalid_argument& error) { // Stoi error like when rating is supposed to be a number
			o << "ERROR: " << file_text << endl;
			o << error.what() << endl << endl;
		}
		catch (yearError& error) { //Invalid Year
			o << "ERROR: " << file_text << endl;
			o << error.what() << endl << endl;
		}
		catch (boolError& error) { //Invalid song top40 bool value
			o << "ERROR: " << file_text << endl;
			o << error.what() << endl << endl;
		}

		
	}
		
	return 1;
}




void addNewMedia(istream& inCommands, ostream& out, ostream& outErr, vector<Media*>& m, vector<Movie>& movies, vector<Book>& books, vector<Song>& songs) {
	string newMediaCmd;
	getline(inCommands, newMediaCmd, ','); //Get the comma after'N' 
	getline(inCommands, newMediaCmd); // I want everything after the 2nd comma 
	// 'N,M,Hidden Figures' -> 'M, Hidden Figures ....'
	

	//Get media title to output
	stringstream inSS;
	inSS.clear();
	inSS.str(newMediaCmd);
	string media_title;
	getline(inSS, media_title, ',');
	getline(inSS, media_title, ',');

	try {
		if (newMediaCmd[0] == 'M') {
			readMovieinput(newMediaCmd, outErr, m, movies);
		}
		if (newMediaCmd[0] == 'B') {
			readBookinput(newMediaCmd, outErr, m, books);
		}
		if (newMediaCmd[0] == 'S') {
			readSonginput(newMediaCmd, outErr, m, songs);
		}

		
		out << media_title << " was added to your list" << endl << endl << endl;
	}
	catch (runtime_error& error) { // Invalid Rating Error
		// Prints the error message passed by throw statement
		outErr << "Unable to process command. There was an invalid value entered for rating: " << media_title << endl << endl;
	}
	catch (invalid_argument& error) { // Stoi error like when rating is supposed to be a number
		outErr << "Unable to process command. There was an invalid value entered for item: " << media_title << endl << endl;
	}
	catch (yearError& error) { //Invalid Year
		outErr << "Unable to process command. There was an invalid value entered for year: " << media_title << endl << endl;
	}
	catch (boolError& error) { //Invalid song top40 bool value
		outErr << "Unable to process command. There was an invalid value entered for bool: " << media_title << endl << endl;
	}
}






/*	====================================================
	Output Functions to write to report files and error files
	=====================================================
*/ 



void printMovieList(istream& in, ostream& out, ostream& outErr, vector<Movie>& m) {
	out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	out << right << setw(35) << "YOUR MOVIE LIST" << endl << endl;
	out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << endl;
	for (int i = 0; i < m.size(); i++) {
		if (m.at(i).getType() == 'M') {
			out << left << setw(4) << (i + 1) << setw(40) << m.at(i).getTitle() << setw(11) << m.at(i).getYearReleased() << setw(5) << m.at(i).getRating() << endl;
		}
	}
	out << endl << endl << endl;
}


void printMovieList(istream& in, ostream& out, ostream& outErr, vector<Movie>& m, string str_sortCriteria) {
	// Check to see if sortCriteria is a string or integer by counting characters
	int chr_count = 0;
	for (auto character : str_sortCriteria) {
		if (isalpha(character) || ispunct(character)) {
			chr_count += 1;
		}
	}

	// If the sort criteria is a strnig like "R&B" then print all songs with genre "R&B"
	if (chr_count == str_sortCriteria.size()) {
		// See if there are any songs with genre 
		int items_printed = 0;
		for (int i = 0; i < m.size(); i++) {
			if (m.at(i).getType() == 'M' && m.at(i).getGenre() == str_sortCriteria) {
				items_printed += 1;
			}
		}

		if (items_printed == 0) { // If there are no movies of a certain genre print to error file
			outErr << "Unable to process command. There was not item of genre: " << str_sortCriteria << " in your list. " << endl << endl;
		}
		else { // Print movies that have a certain genre
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR MOVIE LIST" << "(GENRE: " << str_sortCriteria << ")" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "GENRE" << endl;
			for (int i = 0; i < m.size(); i++) { // Print songs that have a certain genre
				if (m.at(i).getType() == 'M' && m.at(i).getGenre() == str_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << m.at(i).getTitle() << setw(8) << m.at(i).getYearReleased() << m.at(i).getGenre() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
	// If the sort criteria is an integer rating print media with certain rating
	else {
		stringstream str_to_int;
		int int_sortCriteria;
		str_to_int.str(str_sortCriteria);
		str_to_int >> int_sortCriteria;

		// Verify that rating is a valid rating 1-10 inclusive 
		if (int_sortCriteria < 1 || int_sortCriteria > 10) {
			outErr << "Unable to process command. The rating of: " << int_sortCriteria << " is invalid" << endl << endl;
		}
		else { // If rating is valid input, print all movies that have a rating of inputed rating or higher
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR MOVIE LIST" << "(RATING: " << int_sortCriteria << " or higher)" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << endl;
			for (int i = 0; i < m.size(); i++) {
				if (m.at(i).getType() == 'M' && m.at(i).getRating() >= int_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << m.at(i).getTitle() << setw(11) << m.at(i).getYearReleased() << setw(5) << m.at(i).getRating() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
}



void printBookList(istream& in, ostream& out, ostream& outErr, vector<Book>& b) {
	out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	out << right << setw(35) << "YOUR BOOK LIST" << endl << endl;
	out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << endl;
	for (int i = 0; i < b.size(); i++) {
		if (b.at(i).getType() == 'B') {
			out << left << setw(4) << (i + 1) << setw(40) << b.at(i).getTitle() << setw(11) << b.at(i).getYearReleased() << setw(5) << b.at(i).getRating() << endl;
		}
	}
	out << endl << endl << endl;
}


void printBookList(istream& in, ostream& out, ostream& outErr, vector<Book>& b, string str_sortCriteria) {
	// Check to see if sortCriteria is a string or integer by counting characters
	int chr_count = 0;
	for (auto character : str_sortCriteria) {
		if (isalpha(character) || ispunct(character)) {
			chr_count += 1;
		}
	}

	// If the sort criteria is a strnig like "R&B" then print all songs with genre "R&B"
	if (chr_count == str_sortCriteria.size()) {
		// See if there are any songs with genre 
		int items_printed = 0;
		for (int i = 0; i < b.size(); i++) {
			if (b.at(i).getType() == 'B' && b.at(i).getGenre() == str_sortCriteria) {
				items_printed += 1;
			}
		}

		if (items_printed == 0) { // If there are no books of a certain genre print to error file
			outErr << "Unable to process command. There was not item of genre: " << str_sortCriteria << " in your list. " << endl << endl;
		}
		else { // Print books that have a certain genre
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR BOOK LIST" << "(GENRE: " << str_sortCriteria << ")" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "GENRE" << endl;
			for (int i = 0; i < b.size(); i++) { // Print songs that have a certain genre
				if (b.at(i).getType() == 'B' && b.at(i).getGenre() == str_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << b.at(i).getTitle() << setw(8) << b.at(i).getYearReleased() << b.at(i).getGenre() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
	// If the sort criteria is an integer rating print media with certain rating
	else {
		stringstream str_to_int;
		int int_sortCriteria;
		str_to_int.str(str_sortCriteria);
		str_to_int >> int_sortCriteria;

		// Verify that rating is a valid rating 1-10 inclusive 
		if (int_sortCriteria < 1 || int_sortCriteria > 10) {
			outErr << "Unable to process command. The rating of: " << int_sortCriteria << " is invalid" << endl << endl;
		}
		else { // If rating is valid input, print all books that have a rating of inputed rating or higher
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR BOOK LIST" << "(RATING: " << int_sortCriteria << " or higher)" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << endl;
			for (int i = 0; i < b.size(); i++) {
				if (b.at(i).getType() == 'B' && b.at(i).getRating() >= int_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << b.at(i).getTitle() << setw(11) << b.at(i).getYearReleased() << setw(5) << b.at(i).getRating() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
}


void printSongList(istream& in, ostream& out, ostream& outErr, vector<Song>& s) {
	out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	out << right << setw(35) << "YOUR SONG LIST" << endl << endl;
	out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << endl;
	for (int i = 0; i < s.size(); i++) {
		if (s.at(i).getType() == 'S') {
			out << left << setw(4) << (i + 1) << setw(40) << s.at(i).getTitle() << setw(11) << s.at(i).getYearReleased() << setw(5) << s.at(i).getRating() << endl;
		}
	}
	out << endl << endl << endl;
}

void printSongList(istream& in, ostream& out, ostream& outErr, vector<Song>& s, string str_sortCriteria) {
	// Check to see if sortCriteria is a string or integer by counting characters
	int chr_count = 0;
	for (auto character : str_sortCriteria) {
		if (isalpha(character) || ispunct(character)) {
			chr_count += 1;
		}
	}

	// If the sort criteria is a strnig like "R&B" then print all songs with genre "R&B"
	if (chr_count == str_sortCriteria.size()) {
		// See if there are any songs with genre 
		int items_printed = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s.at(i).getType() == 'S' && s.at(i).getGenre() == str_sortCriteria) {
				items_printed += 1;
			}
		}

		if (items_printed == 0) { // If there are no songs of a certain genre print to error file
			outErr << "Unable to process command. There was not item of genre: " << str_sortCriteria << " in your list. " << endl << endl;
		}
		else { // Print songs that have a certain genre
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR SONG LIST" << "(GENRE: " << str_sortCriteria << ")" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "GENRE" << endl;
			for (int i = 0; i < s.size(); i++) { // Print songs that have a certain genre
				if (s.at(i).getType() == 'S' && s.at(i).getGenre() == str_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << s.at(i).getTitle() << setw(8) << s.at(i).getYearReleased() << s.at(i).getGenre() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
	else { // If the sort criteria is an integer rating 
		stringstream str_to_int;
		int int_sortCriteria;
		str_to_int.str(str_sortCriteria);
		str_to_int >> int_sortCriteria;

		// Verify that rating is a valid rating 1-10 inclusive 
		if (int_sortCriteria < 1 || int_sortCriteria > 10) {
			outErr << "Unable to process command. The rating of: " << int_sortCriteria << " is invalid" << endl << endl;
		}
		else { // If rating is valid input, print all songs that have a rating of inputed rating or higher
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR SONG LIST" << "(RATING: " << int_sortCriteria << " or higher)" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << endl;
			for (int i = 0; i < s.size(); i++) {
				if (s.at(i).getType() == 'S' && s.at(i).getRating() >= int_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << s.at(i).getTitle() << setw(11) << s.at(i).getYearReleased() << setw(5) << s.at(i).getRating() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
}


void printAllMedia(istream& in, ostream& out, ostream& outErr, vector<Media*>& m) {
	out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	out << right << setw(35) << "YOUR MEDIA LIST" << endl << endl;
	out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << right << setw(5) << "TYPE" << endl;
	for (int i = 0; i < m.size(); i++) {
		out << left << setw(4) << (i + 1) << setw(40) << m.at(i)->getTitle() << setw(11) << m.at(i)->getYearReleased() << setw(5) << m.at(i)->getRating() << setw(5) << m.at(i)->getType() << endl;
	}
	out << endl << endl << endl;
}

void printAllMedia(istream& in, ostream& out, ostream& outErr, vector<Media*>& m, string str_sortCriteria) {
	// Check to see if sortCriteria is a string or integer by counting characters
	int chr_count = 0;
	for (auto character : str_sortCriteria) {
		if (isalpha(character) || ispunct(character)) {
			chr_count += 1;
		}
	}

	// If the sort criteria is a strnig like "R&B" then print all songs with genre "R&B"
	if (chr_count == str_sortCriteria.size()) {
		// See if there are any media with genre 
		int items_printed = 0;
		for (int i = 0; i < m.size(); i++) {
			if (m.at(i)->getGenre() == str_sortCriteria) {
				items_printed += 1;
			}
		}

		if (items_printed == 0) { // If there's no media of a certain genre print to error file
			outErr << "Unable to process command. There was not item of genre: " << str_sortCriteria << " in your list. " << endl << endl;
		}
		else { // If media of genre exist then print all media 
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR MEDIA LIST" << "(GENRE: " << str_sortCriteria << ")" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "GENRE" << endl;
			for (int i = 0; i < m.size(); i++) { // Print all media that have a certain genre
				if (m.at(i)->getGenre() == str_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << m.at(i)->getTitle() << setw(8) << m.at(i)->getYearReleased() << m.at(i)->getGenre() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
	else { // If the sort criteria is an integer rating 
		stringstream str_to_int;
		int int_sortCriteria;
		str_to_int.str(str_sortCriteria);
		str_to_int >> int_sortCriteria;

		// Verify that rating is a valid rating 1-10 inclusive 
		if (int_sortCriteria < 1 || int_sortCriteria > 10) {
			outErr << "Unable to process command. The rating of: " << int_sortCriteria << " is invalid" << endl << endl;
		}
		else { // If rating is valid input, print all songs that have a rating of inputed rating or higher
			out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			out << right << setw(35) << "YOUR MEDIA LIST" << "(RATING: " << int_sortCriteria << " or higher)" << endl << endl;
			out << left << setw(4) << "#" << setw(40) << "TITLE" << setw(8) << "YEAR" << "RATING" << endl;
			for (int i = 0; i < m.size(); i++) {
				if (m.at(i)->getRating() >= int_sortCriteria) {
					out << left << setw(4) << (i + 1) << setw(40) << m.at(i)->getTitle() << setw(11) << m.at(i)->getYearReleased() << setw(5) << m.at(i)->getRating() << endl;
				}
			}
			out << endl << endl << endl;
		}
	}
}

void printTotals(ostream& out) {
	out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	out << "YOUR MEDIA LIBRARY " << endl;
	out << "#   TYPE" << endl;
	out << Media::num_movies << "  Movies" << endl;
	out << Media::num_books << "  Books" << endl;
	out << Media::num_songs << "  Songs" << endl;
	out << Media::total_items << "  Items" << endl << endl << endl;
}

void listMovieStars(istream& inCommands, ostream& out, ostream& outErr, vector<Movie>& m, string str_sortCriteria) {
	// See if movie exist in our movie list
	bool movie_exist = false;
	for (auto item : m) {
		if (item.getTitle() == str_sortCriteria) {
			movie_exist = true;
			break;
		}
	}

	// Print out the stars of the movie if movie does exist in our movie lsit 
	if (movie_exist == true) {
		out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		out << "THE STARS OF THE MOVIE " << str_sortCriteria << " ARE :" << endl;

		for (int i = 0; i < m.size(); i++) {
			if (m.at(i).getTitle() == str_sortCriteria) {
				//Print each star of the movie
				for (auto star : m.at(i).getStars()) {
					out << star << endl;
				}
			}
		}
		out << endl << endl << endl;
	}
	else { // Print to error file if movie isn't fond in our movie list 
		outErr << "Unable to process command. The movie: \"" << str_sortCriteria << "\" is not found in your list" << endl << endl;
	}	
}

void findStarInMovie(istream& inCommands, ostream& out, ostream& outErr, vector<Movie>& m, string str_sortCriteria) {
	// See if star exist in our movie list
	bool star_exist = false;
	// Iterate through each Movie Object -> each item in getStars() string vector
	for (auto item : m) {
		for (auto star : item.getStars()) {
			if (star == str_sortCriteria) {
				star_exist = true;
				break;
			}
		}
	}

	// Print out the stars of the movie if star does exist somewhere in our movie lsit 
	if (star_exist == true) {
		out << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		out << str_sortCriteria << " appears in the following movie(s): " << endl;

		// Go through all movies in movie list
		for (int i = 0; i < m.size(); i++) {
			// Go through each string vector of stars each movie object has
			for (auto star : m.at(i).getStars()) {
				// Print out movies the movie star is in 
				if (star == str_sortCriteria) {
					out << m.at(i).getTitle() << endl;
				}
			}
		}
		out << endl << endl << endl;
	}
	else { // Print to error file if star isn't found in your list
		outErr << "Unable to process command. The star: " << str_sortCriteria << " is not found in any movie in your list" << endl << endl;
	}
}
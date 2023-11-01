#pragma once
#include "function.h"




void readMovieinput(string& input_line, ostream& o, vector<Media*>& m, vector<Movie>& movies) {
	// Prepare line of text to get separated by commas
	istringstream inputLine;
	inputLine.clear();
	inputLine.str(input_line);

	// Setup new Movie object to input each data column from line of comma separated text
	Movie tempMovie;
	
	/*  =================================================================================
		Step 1:
		Go through all data columns and process all data into a Movie object
	*/
	string data_column;
	for (int i = 0; i < 7; i++) {
		getline(inputLine, data_column, ',');
		//cout << "-[" << data_column << " ";

		// Go through first 7 data columns in line of text to see if all columns have valid input
		switch (i) {
		case 0:
			tempMovie.setType(data_column[0]);
			break;
		case 1:
			tempMovie.setTitle(data_column);
			break;
		case 2:
			tempMovie.setKeyName(data_column);
			break;
		case 3:	// // Data-column #4: Rating. Need to verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					//stoi_error = true;
					Media::num_movies--;
					Media::total_items--;
					throw invalid_argument("Previous record has an invalid stoi argument error");
					break;
				}
			}
			// Covnert substr to int cause stoi doesn't work how I want
			int int_rating;
			istringstream ss(data_column);
			ss >> int_rating;

			// Check #2: Verify if rating is 1-10 inclusive
			if (int_rating < 1 || int_rating > 10) {
				//rating_error = true;
				Media::num_movies--;
				Media::total_items--;
				throw runtime_error("There was an invalid value entered for rating.");
				break;
			}

			// If check #1 and check #2 pass then setRating
			tempMovie.setRating(int_rating);
			break;
		}
		case 4:
			tempMovie.setGenre(data_column);
			break;
		case 5: // Data-column #6: Length. Verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					//stoi_error = true;
					Media::num_movies--;
					Media::total_items--;
					throw invalid_argument("Previous record has an invalid stoi argument error");
					break;
				}
			}

			// If numeric then convert data_column to int and set data member 
			int int_length;
			istringstream ss(data_column);
			ss >> int_length;
			tempMovie.setLength(int_length);
			break;
		}
		case 6: // Data-column #7: Year. Verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					//year_error = true;
					Media::num_movies--;
					Media::total_items--;
					throw yearError("There was an invalid value entered for year.");
					break;
				}
			}

			// Use stringstream to convert what's in data-column #7 into an integer.
			// Did it this way because when I try stoi, it didn't work
			int int_year;
			istringstream ss(data_column);
			ss >> int_year;

			// Check #2: Verify if rating is 1500-2023 inclusive
			if (int_year < 1500 || int_year > 2023) {
				//year_error = true;
				Media::num_movies--;
				Media::total_items--;
				throw yearError("There was an invalid value entered for year.");
				break;
			}
			// setYearReleased if both check #1 and check #2 passed
			tempMovie.setYearReleased(int_year);
			break;
		}
		}
	}
	
	// Read the rest of the data_column after the 7th column. However many there are after.
	vector<string> set_stars;
	while (getline(inputLine, data_column, ',')) {
		set_stars.push_back(data_column);
	}
	tempMovie.setStars(set_stars);

	/*	=========================================================================
		Step 2:
		Decide whether or not we should add the tempMovie object into the final vectors or descard it and print errors
		to wrror file
	*/
	Movie* tempM = new Movie(tempMovie);
	movies.push_back(tempMovie);
	m.push_back(tempM);
	
}

void readBookinput(string& input_line, ostream& o, vector<Media*>& m, vector<Book>& books) {
	// Prepare line of text to get separated by commas
	istringstream inputLine;
	inputLine.clear();
	inputLine.str(input_line);

	// Setup new Book object to input each data column from line of comma separated text
	Book tempBook;

	/*  =================================================================================
		Step 1:
		Go through all data columns and process all data into a tempBook object
	*/
	string data_column;
	for (int i = 0; i < 8; i++) {
		getline(inputLine, data_column, ',');

		// Go through first 7 data columns in line of text to see if all columns have valid input
		switch (i) {
		case 0:
			tempBook.setType(data_column[0]);
			break;
		case 1:
			tempBook.setTitle(data_column);
			break;
		case 2:
			tempBook.setKeyName(data_column);
			break;
		case 3:	// // Data-column #4: Rating. Need to verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					Media::num_books--;
					Media::total_items--;
					throw invalid_argument("Previous record has an invalid stoi argument error");
					break;
				}
			}
			// Covnert substr to int cause stoi doesn't work how I want
			int int_rating;
			istringstream ss(data_column);
			ss >> int_rating;

			// Check #2: Verify if rating is 1-10 inclusive
			if (int_rating < 1 || int_rating > 10) {
				Media::num_books--;
				Media::total_items--;
				throw runtime_error("There was an invalid value entered for rating.");
				break;
			}

			// If check #1 and check #2 pass then setRating
			tempBook.setRating(int_rating);
			break;
		}
		case 4:
			tempBook.setGenre(data_column);
			break;
		case 5: // Data-column #6: Length. Verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					Media::num_books--;
					Media::total_items--;
					throw invalid_argument("Previous record has an invalid stoi argument error");
					break;
				}
			}

			// If numeric then convert data_column to int and set data member 
			int int_length;
			istringstream ss(data_column);
			ss >> int_length;
			tempBook.setLength(int_length);
			break;
		}
		case 6: // Data-column #7: Year. Verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					Media::num_books--;
					Media::total_items--;
					throw yearError("There was an invalid value entered for year.");
					break;
				}
			}

			// Use stringstream to convert what's in data-column #7 into an integer.
			// Did it this way because when I try stoi, it didn't work
			int int_year;
			istringstream ss(data_column);
			ss >> int_year;

			// Check #2: Verify if rating is 1500-2023 inclusive
			if (int_year < 1500 || int_year > 2023) {
				Media::num_books--;
				Media::total_items--;
				throw yearError("There was an invalid value entered for year.");
				break;
			}
			// setYearReleased if both check #1 and check #2 passed
			tempBook.setYearReleased(int_year);
			break;
		}
		case 7: // 8th data column is for weeksNYT. Verify if numeric.
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					Media::num_books--;
					Media::total_items--;
					throw invalid_argument("Previous record has an invalid stoi argument error");
					break;
				}
			}

			// IF check #1 passed, Convert info in data_column to integer and call setWeeks
			int int_weeks;
			istringstream ss(data_column);
			ss >> int_weeks;

			tempBook.setWeeks(int_weeks);
		}
		}
	}
	/*	=========================================================================
		Step 2:
		Decide whether or not we should add the tempBook object into the final vectors or descard it and print errors
		to wrror file
	*/
	Book* tempB = new Book(tempBook);
	books.push_back(tempBook);
	m.push_back(tempB);
	
}



void readSonginput(string& input_line, ostream& o, vector<Media*>& m, vector<Song>& songs) {
	// Prepare line of text to get separated by commas
	istringstream inputLine;
	inputLine.clear();
	inputLine.str(input_line);

	// Setup new Song object to input each data column from line of comma separated text
	Song tempSong;

	/*  =================================================================================
		Step 1:
		Go through all data columns and process all data into a tempSong object
	*/
	string data_column;
	for (int i = 0; i < 8; i++) {
		getline(inputLine, data_column, ',');

		// Go through first 7 data columns in line of text to see if all columns have valid input
		switch (i) {
		case 0:
			tempSong.setType(data_column[0]);
			break;
		case 1:
			tempSong.setTitle(data_column);
			break;
		case 2:
			tempSong.setKeyName(data_column);
			break;
		case 3:	// // Data-column #4: Rating. Need to verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					Media::num_songs--;
					Media::total_items--;
					throw invalid_argument("Previous record has an invalid stoi argument error");
					break;
				}
			}
			// Covnert substr to int cause stoi doesn't work how I want
			int int_rating;
			istringstream ss(data_column);
			ss >> int_rating;

			// Check #2: Verify if rating is 1-10 inclusive
			if (int_rating < 1 || int_rating > 10) {
				Media::num_songs--;
				Media::total_items--;
				throw runtime_error("There was an invalid value entered for rating.");
				break;
			}

			// If check #1 and check #2 pass then setRating
			tempSong.setRating(int_rating);
			break;
		}
		case 4:
			tempSong.setGenre(data_column);
			break;
		case 5: // Data-column #6: Length. Verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					Media::num_songs--;
					Media::total_items--;
					throw invalid_argument("Previous record has an invalid stoi argument error");
					break;
				}
			}

			// If numeric then convert data_column to int and set data member 
			int int_length;
			istringstream ss(data_column);
			ss >> int_length;
			tempSong.setLength(int_length);
			break;
		}
		case 6: // Data-column #7: Year. Verify valid input
		{
			// Check #1: Verify if numeric
			for (char letter : data_column) {
				if (isalpha(letter)) {
					Media::num_songs--;
					Media::total_items--;
					throw yearError("There was an invalid value entered for year.");
					break;
				}
			}

			// Use stringstream to convert what's in data-column #7 into an integer.
			// Did it this way because when I try stoi, it didn't work
			int int_year;
			istringstream ss(data_column);
			ss >> int_year;

			// Check #2: Verify if rating is 1500-2023 inclusive
			if (int_year < 1500 || int_year > 2023) {
				Media::num_songs--;
				Media::total_items--;
				throw yearError("There was an invalid value entered for year.");
				break;
			}
			// setYearReleased if both check #1 and check #2 passed
			tempSong.setYearReleased(int_year);
			break;
		}
		case 7: // 8th data column is for if song is top40 song. Verify if bool.
		{
			// Check #1: Verify if data is boolean
			if (data_column != "0" && data_column != "1" && data_column != "Y" && data_column != "N") {
				Media::num_songs--;
				Media::total_items--;
				throw boolError("Previous record has an error in boolean value");
				break;
			}
			
			// IF check #1 passed, Convert info in data_column to bool and setTop40
			bool bool_top40;
			//istringstream ss(data_column);
			//ss >> bool_top40;
			if (data_column == "1" || data_column == "Y") {
				bool_top40 = 1;
			}
			if (data_column == "0" || data_column == "N") {
				bool_top40 = 0;
			}

			tempSong.setTop40(bool_top40);
		}
		}
	}
	/*	=========================================================================
		Step 2:
		Decide whether or not we should add the tempSong object into the final vectors or descard it and print errors
		to wrror file
	*/
	Song* tempS = new Song(tempSong);
	songs.push_back(tempSong);
	m.push_back(tempS);
	
}
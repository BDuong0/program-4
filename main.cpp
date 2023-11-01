#pragma once
#include "function.h"
using namespace std;

int Media::total_items = 0;
int Media::num_movies = 0;
int Media::num_books = 0;
int Media::num_songs = 0;

int main() {
	vector <Media*> Media_list; //Create vector to store all individual media from mediaList.txt
	vector <Movie> Movie_list;
	vector <Book> Book_list;
	vector <Song> Song_list;

	// Open Input Files
	ifstream inFile;
	inFile.open("mediaList.txt");

	ifstream cmd_file;
	cmd_file.open("mediaCommands.txt");

	// Open Output files to write to
	ofstream error_file;
	error_file.open("mediaError.txt");

	ofstream report_file;
	report_file.open("mediaReport.txt");

	if (inFile.is_open()) {
		cout << "infile has successfully opened" << endl;
	}

	
	// Load Media_list vector 
	readMediaList(inFile, error_file, Media_list, Movie_list, Book_list, Song_list);
	cout << "# Movies: " << Media::num_movies << endl;
	cout << "# Books: " << Media::num_books << endl;
	cout << "# Songs: " << Media::num_songs << endl;
	cout << "# Total Items: " << Media::total_items << endl;
	
	
	
	// Go through mediaCommands.txt and create output files
	string fileText;
	vector<string> splitData;
	while (getline(cmd_file, fileText)) {
		istringstream inSS;
		string substr;
		inSS.clear();
		inSS.str(fileText);

		// If each line of text is just a character
		if (fileText.size() == 1) {
			if (fileText == "M") {
				printMovieList(inFile, report_file, error_file, Movie_list);
			}
			else if (fileText == "B") {
				printBookList(inFile, report_file, error_file, Book_list);
			}
			else if (fileText == "S") {
				printSongList(inFile, report_file, error_file, Song_list);
			}
			else if (fileText == "A") {
				printAllMedia(inFile, report_file, error_file, Media_list);
			}
			else if (fileText == "T") {
				printTotals(report_file);
			}
			else if (fileText == "Q") {
				break;
			}
		}
		else { // Process line of text that has commas in it
			
			// Count commas in individual line of text
			int num_commas = 0;
			for (int i = 0; i < fileText.size(); i++) {
				if (fileText[i] == ',') {
					num_commas += 1;
				}
			}

			// Process command inputs like M,1 .. S,R&B.. F,Victor Lee ..etc.
			if (num_commas == 1) {
				getline(inSS, substr, ',');
				if (substr == "M" || substr == "B" || substr == "S" || substr == "A" || substr == "L" || substr == "F") {
					string sortCriteria;
					getline(inSS, sortCriteria, ',');
					
					if (substr == "M") {
						printMovieList(inFile, report_file, error_file, Movie_list, sortCriteria);
					}
					if (substr == "B") {
						printBookList(inFile, report_file, error_file, Book_list, sortCriteria);
					}
					if (substr == "S") {
						printSongList(inFile, report_file, error_file, Song_list, sortCriteria);
					}
					if (substr == "A") {
						printAllMedia(inFile, report_file, error_file, Media_list, sortCriteria);
					}
					if (substr == "L") {
						listMovieStars(inFile, report_file, error_file, Movie_list, sortCriteria);
					}
					if (substr == "F") {
						findStarInMovie(inFile, report_file, error_file, Movie_list, sortCriteria);
					}
				}
			}
			// Process commands that have 'N' as first character. This command will add new media to final vectors.
			else { 
				// Lines that have 'N' as first character in line of text 
				//Convert line of text to stringstream so getline can work
				stringstream input_line;
				input_line.str(fileText);
				addNewMedia(input_line, report_file, error_file, Media_list, Movie_list, Book_list, Song_list);
			}
		}
		cout << "Processing mediaCommands .... " << endl;
	}
	cout << "Done processing." << endl;
	cout << "mediaReport.txt, mediaError.txt created " << endl;
	
	
	return 0;
}
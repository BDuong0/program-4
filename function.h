#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>
#include <stdexcept>

#include "Media.h" //Base Class
#include "Movie.h"
#include "Book.h"
#include "Song.h"
using namespace std;

// Custom Exception Types Generated with ChatGPT prompt "Can you make a simple c++ custom exception class"
class yearError : public exception {
public:
	yearError(const std::string& message) : message_(message) {}

	const char* what() const noexcept override {
		return message_.c_str();
	}

private:
	std::string message_;
};

class boolError : public exception {
public:
	boolError(const std::string& message) : message_(message) {}

	const char* what() const noexcept override {
		return message_.c_str();
	}

private:
	std::string message_;
};


/*  ================================================================================================
	Functions in function.cpp
*/
int readMediaList(istream& i, ostream& o, vector<Media*>& m, vector<Movie>& movies, vector<Book>& books, vector<Song>& songs);
	//PRE: input and error output file are opened and Media_List vector is empty 
	//POST Load Media_List vector with Media class objects and output any errors to error output file

void addNewMedia(istream& inCommands, ostream& out, ostream& outErr, vector<Media*>& m, vector<Movie>& movies, vector<Book>& books, vector<Song>& songs);
	//PRE: mediaCommands.txt is opened and Media_List vector is fully loaded
	//POST: Add new media objects into Media_List vector and print to error file any errors that occur


// All overload functions print media with a type (book, movie, song) with a certain sorting criteria like a certain rating or genre

void printMovieList(istream& in, ostream& out, ostream& outErr, vector<Movie>& m);
void printMovieList(istream& in, ostream& out, ostream& outErr, vector<Movie>& m, string str_sortCriteria);
	//PRE: Media_List vector is fully loaded and output files are opened to write to
	//POST: Outputs a list of all movies in the output file and prints any errors to error output file

void printBookList(istream& in, ostream& out, ostream& outErr, vector<Book>& b);
void printBookList(istream& in, ostream& out, ostream& outErr, vector<Book>& b, string str_sortCriteria);
	//PRE: Media_List vector is fully loaded and output files are opened to write to
	//POST: Outputs a list of all books in the output file and prints any errors to error output file

void printSongList(istream& in, ostream& out, ostream& outErr, vector<Song>& s);
void printSongList(istream& in, ostream& out, ostream& outErr, vector<Song>& s, string str_sortCriteria);
	//PRE: Media_List vector is fully loaded and output files are opened to write to
	//POST: Outputs a list of all songs in the output file and prints any errors to error output file

void printAllMedia(istream& in, ostream& out, ostream& outErr, vector<Media*>& m);
void printAllMedia(istream& in, ostream& out, ostream& outErr, vector<Media*>& m, string str_sortCriteria);
	//PRE: Media_List vector is fully loaded and output files are opened to write to
	//POST: Outputs a list of all media in the output file and prints any errors to error output file

void printTotals(ostream& out);

void listMovieStars(istream& inCommands, ostream& out, ostream& outErr, vector<Movie>& m, string str_sortCriteria);

void findStarInMovie(istream& inCommands, ostream& out, ostream& outErr, vector<Movie>& m, string str_sortCriteria);



/*  ============================================================================
	Functions in function2.cpp
*/


void readMovieinput(string& input_line, ostream& o, vector<Media*>& m, vector<Movie>& movies);

void readBookinput(string& input_line, ostream& o, vector<Media*>& m, vector<Book>& books);

void readSonginput(string& input_line, ostream& o, vector<Media*>& m, vector<Song>& songs);

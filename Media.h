#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

/*
Brian Duong
Program 3 - Media Library
Oct 22, 2023
*/

class Media {
	public:
		Media();
		Media(char typ, string tle, string kn, int r, string g, int l, int yr);
		
		static int total_items;
		static int num_movies;
		static int num_books;
		static int num_songs;
		
		

		//Getters
		char getType() { return type; }
		string getTitle() { return title; }
		string getKeyName() { return keyName;  }
		int getRating() { return rating;  }
		string getGenre() { return genre; }
		int getLength() { return length; }
		int getYearReleased() { return yearReleased; }

		//Setters 
		void setType(char t) { type = t; }
		void setTitle(string t) { title = t; }
		void setKeyName(string kn) { keyName = kn; }
		void setRating(int r) { rating = r; }
		void setGenre(string g) { genre = g; }
		void setLength(int l) { length = l; }
		void setYearReleased(int yr) { yearReleased = yr; }
		
	private:
		char type;
		string title;
		string keyName;
		int rating;
		string genre;
		int length;
		int yearReleased;
};


#include "highscore.h"

#include <iostream>
#include <string>

int ReadHighScore()
{
	ifstream file;
	file.open( "highscore.txt" );

	string line;
	getline( file, line );

	return stoi( line );
}

void WriteHighScore( int score )
{
	ofstream file;
	file.open( "highscore.txt", std::ofstream::out | std::ofstream::trunc );

	file << std::to_string(score);

	file.close();
}
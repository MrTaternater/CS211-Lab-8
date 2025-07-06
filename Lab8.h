#ifndef LAB8_H
#define LAB8_H

// Include for printing to the screen
#include <stdio.h>

// Include to use various string functions
#include <string.h>

#include <stdlib.h>

// Macro for line length
#define LINE_LENGTH 110

// Macros for divider types
#define STAR '*'
#define DASH '-'

// Macros for stat headers
#define PLAYER "Player"
#define NUMBER "#"
#define POSITION "Position"
#define AT_BATS "AB"
#define H "H"
#define TOTAL_BASES "BT"
#define BATTING_AVERAGE "BA"
#define SLUGGING_PERCENTAGE "SLG%"
#define NAME "Name"
#define HITS "Hits"

// Macros for standard header details
#define SCHOOL "[COLLEGE]"
#define LAB "Lab 8 - Arrays of Structures"
#define PROGRAMMER "Program Written by: [NAME]"

// Creates playerRecord struct for all .c files to access
struct playerRecord
{
	// Char lengths are arbitrary; just long enought to fit needed information
	char name[50];
	char position[20];
	int number;
	int atBats;
	int hits;
	int basesTaken;
	int ranking;
	double battingAverage;
	double sluggingAverage;
	
};

// Prototypes for functions listed below
void PrintDividerStar(int *counter, FILE *pOutputFile);

void PrintDividerDash(FILE *pOutputFile);

void PrintHeader(FILE *pOutputFile);

int CenterString(char value[], int size);

int InputPlayerData(FILE *playerData, struct playerRecord player[]);

double CalculateBattingAverage(struct playerRecord player[], int playerNum);

double CalculateSluggingAverage(struct playerRecord player[], int playerNum);

void CalculateAverages(struct playerRecord player[], int totalPlayers);

void PrintPlayerDataHeader(FILE *pOutputFile);

void OutputPlayerData(struct playerRecord player[], int totalPlayers, FILE *pOutputFile);

void OutputOverHits(struct playerRecord player[], FILE *pOutputFile, int totPlayers, int minHits);

int InputPlayerPosition(FILE *positionData, char playerPosition[][15]);

void OutputPlayerByPosition(FILE *pOutputFile, int totalPlayers, int positionTotal, 
		char playerPosition[][15], struct playerRecord player[]);
		
void SelectionSort(struct playerRecord player[], int totalPlayers);
		
void Swap(struct playerRecord player[], int indexA, int indexB);

void OutputPlayerByNumber(FILE *pOutputFile, int totalPlayers, struct playerRecord player[]);

#endif

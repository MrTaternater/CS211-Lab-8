// Includes header details in header file
#include "Lab8.h"

// Creates main function
int main(void)
{
	// Declares integers necessary for main
	int counter;
	int totalPlayers;
	int totalPositions;
	
	// Declares array of playerRecord struct
	struct playerRecord player[15];
	
	// Declares array for different positions
	char playerPosition[9][15];
	
	// Declare two input file pointers
	FILE* positionData = fopen("PlayerPos.txt", "r");
	FILE* playerData = fopen("SoftballData.txt", "r");
	
	// Declare output file pointer
	FILE* pOutputFile = fopen("SoftballResults.txt", "w");
	
	// Determines if the text files contain contents
	if (positionData != NULL && playerData != NULL)
	{
		// Prints parts of header to the screen
		PrintDividerStar(&counter, pOutputFile);
		PrintHeader(pOutputFile);
		PrintDividerStar(&counter, pOutputFile);
		
		// Inputs the total player data and determines total number of players
		totalPlayers = InputPlayerData(playerData, player);
	
		// Function call to calculate the averages of each player
		CalculateAverages(player, totalPlayers);
	
		// Function call to print the header for the player data
		PrintPlayerDataHeader(pOutputFile);
	
		// Prints a line of dashes across the screen
		PrintDividerDash(pOutputFile);
	
		// Function call to output the data of all players
		OutputPlayerData(player, totalPlayers, pOutputFile);
	
		// Prints a line of dashes across the screen
		PrintDividerDash(pOutputFile);
	
		// Function calls to output players with certain amount of hits
		OutputOverHits(player, pOutputFile, totalPlayers, 10);
		OutputOverHits(player, pOutputFile, totalPlayers, 20);
	
		// Function call to input positions into an array
		totalPositions = InputPlayerPosition(positionData, playerPosition);
	
		// Function call to output players in order of position
		OutputPlayerByPosition(pOutputFile, totalPlayers, totalPositions, 
			playerPosition, player);
		
		// Prints a line of dashes across the screen
		PrintDividerDash(pOutputFile);
		
		// Function call to sort players by number 
		SelectionSort(player, totalPlayers);
	
		// Function call to output the players in order of number
		OutputPlayerByNumber(pOutputFile, totalPlayers, player);
		
	}
	else
	{
		// Print error message to the screen
		fprintf(pOutputFile, "One or both files did not open\n");
		
	}
	
	// Closes all input and output files
	fclose(positionData);
	fclose(playerData);
	fclose(pOutputFile);
	
	// Return 0 to end main
	return 0;
}

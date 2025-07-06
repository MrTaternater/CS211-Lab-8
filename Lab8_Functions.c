// Includes header details in header file
#include "Lab8.h"

//-----------------------------------------------------------------------------
// Function Name: PrintDividerStar
// Description: Prints a line of 110 stars as a divider to the screen.
//
//-----------------------------------------------------------------------------
void PrintDividerStar(int *counter, FILE *pOutputFile)
{
	// Initialize LCV (Loop Control Variable) to 0
	*counter = 0;
	
	// Print a bunch of symbols across the screen
	while (*counter < LINE_LENGTH)
	{
		// Print one character to the screen
		fprintf(pOutputFile, "%c", STAR);

		// Increment counter
		(*counter)++;
	}
	// Move the cursor down to the next line
	fprintf(pOutputFile, "\n");
}

//-----------------------------------------------------------------------------
// Function Name: PrintDividerDash
// Description: Prints a line of 110 dashes as a divider to the screen.
//
//-----------------------------------------------------------------------------
void PrintDividerDash(FILE *pOutputFile)
{
	// Initialize LCV (Loop Control Variable) to 0
	int counter = 0;
	
	// Print a bunch of symbols across the screen
	while (counter < LINE_LENGTH)
	{
		// Print one character to the screen
		fprintf(pOutputFile, "%c", DASH);

		// Increment counter
		counter++;
	}
	
	// Move the cursor down to the next line
	fprintf(pOutputFile, "\n");
}

//-----------------------------------------------------------------------------
// Function Name: PrintHeader
// Description: Prints the standard header, including the school name, lab name 
// and programmer name to the screen.
//
//-----------------------------------------------------------------------------
void PrintHeader(FILE *pOutputFile)
{
	// Declares number of spaces needed to print string
	int spaces = 0;
	
	// Creates header elements
	char school[LINE_LENGTH];
	strcpy(school, SCHOOL);
	char lab[LINE_LENGTH];
	strcpy(lab, LAB);
	char programmer[LINE_LENGTH];
	strcpy(programmer, PROGRAMMER);
	
	// Centers all header elements
	spaces = CenterString(school, LINE_LENGTH);
	
	// Print school to the screen
    fprintf(pOutputFile, "%*s\n", spaces, school);
	
	// Repeat for lab and programmer
	spaces = CenterString(lab, LINE_LENGTH);
    fprintf(pOutputFile, "%*s\n", spaces, lab);
	spaces = CenterString(programmer, LINE_LENGTH);
    fprintf(pOutputFile, "%*s\n", spaces, programmer);
}

//-----------------------------------------------------------------------------
// Function Name: CenterString
// Description: Centers a given string across the standard width of the output
// file.
//
//-----------------------------------------------------------------------------
int CenterString(char value[], int size)
{
	// Finds the width of the 
	int width = (size + (int)strlen(value)) / 2;;

	// Returns the found width
	return width;
	
}

//-----------------------------------------------------------------------------
// Function Name: InputPlayerData
// Description: Obtains data from each line of an input file and assigns the
// data to the proper variable of the playerRecord struct for each player in
// the data file.
//
//-----------------------------------------------------------------------------
int InputPlayerData(FILE *playerData, struct playerRecord player[])
{
	// Declares counter variables to place data in correct variable and player
	int statCounter = 0;
	int playerCounter = 0;
	int lineNumber = 0;
	
	// Creates string for fgets to assign to
	char currentLine[50];
	
	// Loop continues until end of input file
	while(fscanf(playerData, "%d", &lineNumber) == 1 || 
			fgets(currentLine, sizeof(currentLine), playerData) != NULL)
	{
		
		//Removes the enter key from the end of a line
		if(currentLine[strlen(currentLine) - 1] == '\n')
		{
			currentLine[strlen(currentLine) - 1] = 0;
		}
		
		// Switch statement determines which value of the struct to assign to
		switch(statCounter)
		{
			case 0:
				strcpy(player[playerCounter].name, currentLine);
				break;
			case 1:
				strcpy(player[playerCounter].position, currentLine);
				break;
			case 2:
				player[playerCounter].number = lineNumber;
				break;
			case 3:
				player[playerCounter].atBats = lineNumber;
				break;
			case 4:
				player[playerCounter].hits = lineNumber;
				break;
			case 5:
				player[playerCounter].basesTaken = lineNumber;
				break;
		}
		
		// Increments statCounter
		statCounter++;

		// Resets statCounter and increments playerCounter when player is complete
		if(statCounter == 6)
		{
			statCounter = 0;
			playerCounter++;
		}
		
	}
	
	// Returns the length of the array
	return playerCounter;
	
}

//-----------------------------------------------------------------------------
// Function Name: CalculateBattingAverage
// Description: Takes a player's hits and divides them by the at bats while
// converting each of them to a double. The calculated value is then returned.
//
//-----------------------------------------------------------------------------
double CalculateBattingAverage(struct playerRecord player[], int playerNum)
{
	// Declares batting average return variable
	double avg;
	
	// Calculates batting average
	avg = (double)(player[playerNum].hits)/(double)(player[playerNum].atBats);
	
	// Returns batting average
	return avg;
}

//-----------------------------------------------------------------------------
// Function Name: CalculateSluggingAverage
// Description: Takes a player's bases taken and divides them by the at bats
// while converting each of them to a double. The calculated value is then 
// returned.
//
//-----------------------------------------------------------------------------
double CalculateSluggingAverage(struct playerRecord player[], int playerNum)
{
	// Declares slugging percentage return variable
	double slg;
	
	// Calculates batting average
	slg = (double)(player[playerNum].basesTaken)/(double)(player[playerNum].atBats);
	
	// Returns batting average
	return slg;
	
}

//-----------------------------------------------------------------------------
// Function Name: CalculateAverages
// Description: Calculates the batting average and slugging percentage of each
// player in the struct and adds that data to the struct.
//
//-----------------------------------------------------------------------------
void CalculateAverages(struct playerRecord player[], int totalPlayers)
{
	// Creates counter for each player
	int playerCount = 0;
	
	// While loop continues until all players have been assigned proper stats
	while(playerCount < totalPlayers)
	{
		// Function call to recieve player's batting average
		player[playerCount].battingAverage = CalculateBattingAverage(player, playerCount);
		
		// Function call to recieve player's slugging percentage
		player[playerCount].sluggingAverage = CalculateSluggingAverage(player, playerCount);
		
		// Increments the player count
		playerCount++;
		
	}
	
}

//-----------------------------------------------------------------------------
// Function Name: PrintPlayerDataHeader
// Description: Prints out the header for the section where each player's stats
// are printed to the screen.
//
//-----------------------------------------------------------------------------
void PrintPlayerDataHeader(FILE *pOutputFile)
{
	fprintf(pOutputFile, "%-20s", PLAYER);
    fprintf(pOutputFile, "%9s", NUMBER);
    fprintf(pOutputFile, "%12s", POSITION);
    fprintf(pOutputFile, "%9s", AT_BATS);
	fprintf(pOutputFile, "%7s", H);
	fprintf(pOutputFile, "%7s", TOTAL_BASES);
	fprintf(pOutputFile, "%10s", BATTING_AVERAGE);
	fprintf(pOutputFile, "%10s\n", SLUGGING_PERCENTAGE);
	
}

//-----------------------------------------------------------------------------
// Function Name: OutputPlayerData
// Description: Prints out the stats for each player in organized rows.
//
//-----------------------------------------------------------------------------
void OutputPlayerData(struct playerRecord player[], int totalPlayers, FILE *pOutputFile) {
    // Creates counter for each player
    int playerCount = 0;

    // While loop continues until all players have been printed to the screen
    while (playerCount < totalPlayers) {
        fprintf(pOutputFile, "%-20s", player[playerCount].name);
        fprintf(pOutputFile, "%10d", player[playerCount].number);
		fprintf(pOutputFile, "%3c", ' ');
        fprintf(pOutputFile, "%-15s", player[playerCount].position);
        fprintf(pOutputFile, "%d", player[playerCount].atBats);
		fprintf(pOutputFile, "%7d", player[playerCount].hits);
		fprintf(pOutputFile, "%7d", player[playerCount].basesTaken);
		fprintf(pOutputFile, "%10.3f", player[playerCount].battingAverage);
		fprintf(pOutputFile, "%10.3f", player[playerCount].sluggingAverage);

        fprintf(pOutputFile, "\n");

        // Increments player count
        playerCount++;
    }
}

//-----------------------------------------------------------------------------
// Function Name: OutputOverHits
// Description: Outputs the names and total hits of all players who exceeded
// a specified number of hits.
//
//-----------------------------------------------------------------------------
void OutputOverHits(struct playerRecord player[], FILE *pOutputFile, int totPlayers, int minHits)
{
	// Creates counter for each player
	int playerCount = 0;
	
	// Creates counter for players who surpassed the hit total
	int playerWins = 0;
	
	// Prints section header to screen
	fprintf(pOutputFile, "These players had more than %d hits\n", minHits);
	fprintf(pOutputFile, "%-26s", PLAYER);
	fprintf(pOutputFile, "%s\n", HITS);
	
	// Prints a line of dashes across the screen
	PrintDividerDash(pOutputFile);
	
	// While loop continues until all players have been checked
	while(playerCount < totPlayers)
	{
		// Checks if the player had more than the specified hit count
		if(player[playerCount].hits > minHits)
		{
			// Prints player and total hits to the screen
			fprintf(pOutputFile, "%-26s", player[playerCount].name);
			fprintf(pOutputFile, "%4d\n", player[playerCount].hits);
			
			// Increments the player win counter
			playerWins++;
			
		}
		
		// Increments the player count
		playerCount++;
	}
	
	// Prints the total number of players who surpassed the hit total
	fprintf(pOutputFile, "The number of players who had hits over %d is %d\n", 
			minHits, playerWins);
	
	// Prints a line of dashes across the screen
	PrintDividerDash(pOutputFile);
	
}

//-----------------------------------------------------------------------------
// Function Name: InputPlayerPosition
// Description: Takes a data file of a list of all positions and adds them to
// a provided array.
//
//-----------------------------------------------------------------------------
int InputPlayerPosition(FILE *positionData, char playerPosition[][15])
{
	// Declares counter variables to place data in array
	int positionCounter = 0; 
	
	// Creates string for fgets to assign to
	char currentLine[50];
	
	// Loop continues until the end of the input file
	while(fgets(currentLine, sizeof(currentLine), positionData) != NULL)
	{
		// Removes the enter key from the end of a string
		if(currentLine[strlen(currentLine) - 1] == '\n')
		{
			currentLine[strlen(currentLine) - 1] = 0;
		}
		
		// Sets the current index of the array to the corresponding line of the data file
		strcpy(playerPosition[positionCounter], currentLine);
		
		// Increments position counter
		positionCounter++;
		
	}
	
	// Returns number of positions
	return positionCounter;
	
}

//-----------------------------------------------------------------------------
// Function Name: OutputPlayerByPosition
// Description: Outputs the names and positions of players in order of their
// positions by standard position order.
//
//-----------------------------------------------------------------------------
void OutputPlayerByPosition(FILE *pOutputFile, int totalPlayers, int positionTotal, 
		char playerPosition[][15], struct playerRecord player[])
{
	// For loop continues through all positions
	for(int positionCount = 0; positionCount < positionTotal; positionCount++)
	{
		
		// For loop continues through all players
		for(int playerCount = 0; playerCount < totalPlayers; playerCount++)
		{
			
			// Checks if the current position and the player's position match
			if(strcmp(player[playerCount].position, playerPosition[positionCount]) == 0)
			{
				// Prints out the name of the player
				fprintf(pOutputFile, "%-26s", player[playerCount].name);
				
				// Prints out the position of the player
				fprintf(pOutputFile, "%s\n", player[playerCount].position);
				
			}
			
		}
		
	}
	
}

//-----------------------------------------------------------------------------
// Function Name: SelectionSort
// Description: Sorts the players within the struct in order of lowest number
// to highest number.
//
//-----------------------------------------------------------------------------
void SelectionSort(struct playerRecord player[], int totalPlayers)
{
	// Declares integers necessary to perform sort
	int indexMin = 0;
	int indexSwap = 0;
	
	// Loop will continue until all indexes are put in place
	while(indexMin < totalPlayers - 1)
	{
		indexSwap = indexMin;
		// Loop will continue until it checks every index
		for(int counter = indexMin; counter < totalPlayers; counter++)
		{
			// Compares the values of two indexes of the function
			if(player[indexSwap].number > player[counter].number)
			{
				// Sets indexSwap to the value of counter
				indexSwap = counter;
			}
			
		}

		// Checks if the swap index is lower than the min index
		if(player[indexSwap].number < player[indexMin].number)
		{
			// Swaps the two values
			Swap(player, indexMin, indexSwap);
			
		}
		
		// Increments the counter
		indexMin++;
		
	}		
	
}

//-----------------------------------------------------------------------------
// Function Name: Swap
// Description: Swaps the location of two players within the struct.
//
//-----------------------------------------------------------------------------
void Swap(struct playerRecord player[], int indexA, int indexB)
{
	// Declares temporary data to hold one index of struct array
	struct playerRecord temp = player[indexA];
	
	// Sets the value of indexB to the location of indexA
	player[indexA] = player[indexB];
	
	// Sets the value of indexA to the location of indexB
	player[indexB] = temp;
	
}

//-----------------------------------------------------------------------------
// Function Name: OutputPlayerByNumber
// Description: Outputs the names and numbers of players in the struct after
// they were sorted by number.
//
//-----------------------------------------------------------------------------
void OutputPlayerByNumber(FILE *pOutputFile, int totalPlayers, struct playerRecord player[])
{
	// Prints the header for this section
	fprintf(pOutputFile, "%-28s", "Player");
	fprintf(pOutputFile, "%2c\n", '#'); 
	
	// Prints a line of dashes across the screen
	PrintDividerDash(pOutputFile);
	
	// Loop continues until all players are printed
	for(int counter = 0; counter < totalPlayers; counter++)
	{
		// Prints out the name of the player
		fprintf(pOutputFile, "%-28s", player[counter].name);
		
		// Prints out the number of the player
		fprintf(pOutputFile, "%2d\n", player[counter].number);
	}
	
}

#include <iostream>

using namespace std;

const int FIELD_SIZE = 5, NOSHIPS = 3;
//I REDUCED THE NUM OF SHIPS AND FIELD TO TRY THE PROGRAM;

// Check to see if player has won every time they hit the opponnents ship
bool IsPlayerAWinner(bool fieldofopponent[FIELD_SIZE][FIELD_SIZE],int player) {
	bool element_num1_1 = false;
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int m = 0; m < FIELD_SIZE; m++) {
			if (fieldofopponent[i][m] != element_num1_1) {
				return false;
			}
		}
	}
	return true;
}

//To see if there any ship X-length left
bool IsShipAvailable(int* arr,const int size,int wantedshiplength) {
	for (int i = 0; i < NOSHIPS;i++)	{
		if (arr[i] == wantedshiplength)	{
			arr[i] = 0;
			return true;
		}
	}
	return false;
}

//Create the initial bool field matrix - i put in a random el to try the app!!!
 
void createField(bool arr[FIELD_SIZE][FIELD_SIZE], const int size)	{
	for (int i = 0; i < FIELD_SIZE; i++)	{
		for (int m = 0; m < FIELD_SIZE; m++)	{
			arr[i][m] = false;
		}
	}
}

//For players to see the visualized playfield
void printField(bool arr[FIELD_SIZE][FIELD_SIZE], int size)
{
	for (int i = 0; i < FIELD_SIZE + 1;i++)	{
		if (i == 0) {
			cout << "  ";
		}
		else {
			cout << "| " << i;
		}
	}
	cout << endl;

	for (int i = 0; i < FIELD_SIZE;i++)	{
		if (i < 9) {
			cout << " ";
		}

		cout << i + 1 << "| ";

		for (int m = 0; m < FIELD_SIZE; m++)	{
			cout <<arr[i][m]<< "  ";
		}
		cout << endl;
	}
	
}
void printFieldChar(char arr[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE + 1;i++)	{
		if (i == 0) {
			cout << " ";
		}
		else {
			cout << "| " << i;
		}
	}
	cout << endl;

	for (int i = 0; i < FIELD_SIZE;i++)	{
		if (i < 9) {
			cout << " ";
		}
		cout << i + 1 << "| ";

		for (int m = 0; m < FIELD_SIZE; m++)	{
			cout << arr[i][m] << "  ";
		}
		cout << endl;
	}
}

//Print out a field legend
void PrintFieldLegend()
{
	cout << "'-' - NOT a yet hit spot\n'S' - a piece of ship/successfully hit shot\n'X' - an empty hit spot" << endl;
}

//Functions for ship-placement on the playfields - Either Vert/Horiz
void putAship(bool arr[FIELD_SIZE][FIELD_SIZE], int n,int m)
{
	arr[n-1][m-1] = true;
}

void putAPieceShipVert(bool arr[FIELD_SIZE][FIELD_SIZE],int collumn,int startrow,int length)
{
	for (int i = startrow;i < startrow + length;i++) {
		putAship(arr, i, collumn);
	}
}
void putAPieceShipHor(bool arr[FIELD_SIZE][FIELD_SIZE], int startcollumn, int row, int length)
{
	for (int i = startcollumn;i < startcollumn + length;i++) {
		putAship(arr, row, i);
	}
}

void ChooseLengthOfShipVer(bool arr[FIELD_SIZE][FIELD_SIZE],int* shiplen)
{
	cout << "Please choose a length from 2-4 or 6 for your ship:" << endl;
	int length;
	cin >> length;

	while ( !IsShipAvailable(shiplen, NOSHIPS, length)	)	{
		cout << "No " << length << "-size ships left. Please select a new ship length: \n";
		cin >> length;
	}
	cout << endl;
	int col, startrow;

	cout << "Please choose from which collumn AND from which row to start:" << endl;
	cin >> col >> startrow;

	putAPieceShipVert(arr, col, startrow, length);

}
void ChooseLengthOfShipHor(bool arr[FIELD_SIZE][FIELD_SIZE],int* shiplen)
{
	cout << "Please choose a length from 2-4 or 6 for your ship:" << endl;
	int length;
	cin >> length;

	while ( !IsShipAvailable(shiplen, NOSHIPS, length) )	{
		cout << "No " << length << "-size ships left. Please select a new ship length: \n";
		cin >> length;
	}
	cout << endl;
	int startcol, row;

	cout << "Please choose from which collumn to start AND for which row:" << endl;
	cin >> startcol >> row;

	 putAPieceShipHor(arr, startcol, row, length);
    
}

void ChooseADirectionofShip(bool arr[FIELD_SIZE][FIELD_SIZE],int* shiplen,int numship)
{
		cout << "Do you want to place your ship" << numship +1 << " horrizontally or vertically? (click 'H'/'V')" << endl;
		char a;
		cin >> a;

		switch (a)	{

		case 'H': ChooseLengthOfShipHor(arr, shiplen); break;
		case 'V': ChooseLengthOfShipVer(arr, shiplen); break;
		default: cout << "Error! Pick again: \n";
			ChooseADirectionofShip(arr, shiplen,numship); break;

		}

}

void SelectShipFormation(bool arr[FIELD_SIZE][FIELD_SIZE], int shipNum, int* shiplen)
{
	for (int f = 0; f < shipNum;f++)	{
		ChooseADirectionofShip(arr, shiplen,f);
		system("CLS");

	}
}

//The actual playingfield made using the bool matrix of the 2 players
void makerealField(bool arr[FIELD_SIZE][FIELD_SIZE], char arr2[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int m = 0; m < FIELD_SIZE; m++)
		{
			if (!arr[i][m])
			{
				arr2[i][m] = '-';
			}
			else
			{
				arr2[i][m] = 'S';
			}
		}
	}
}

void HitAShip(char opponnentsChField[FIELD_SIZE][FIELD_SIZE], bool opponentsField[FIELD_SIZE][FIELD_SIZE], int coordX, int coordY,int &playerturn)
{  
	if (opponentsField[coordY-1][coordX-1])
	{
		opponentsField[coordY-1][coordX-1] = !opponentsField[coordY - 1][coordX - 1];
		opponnentsChField[coordY - 1][coordX - 1] = 'S';
		cout << "Congratulations, You hit a ship!\n";
		printFieldChar(opponnentsChField);
		PrintFieldLegend();

		if (IsPlayerAWinner(opponentsField, playerturn))
		{
			cout << "Congratulations, Player " << playerturn << " YOU HAVE WON THE GAME!!!" << endl;
			
		}
	}
	else
	{
		opponnentsChField[coordY - 1][coordX - 1] = 'X';
		cout << "You hit an empty spot!\n";
		printFieldChar(opponnentsChField);
		PrintFieldLegend();

		if (playerturn == 1)
		{
			playerturn++;
		}
		else
		{
			playerturn--;
		}

	}
}

bool HasPreviousCoordinates(int coordX, int coordY)
{
	return coordX >= 1 && coordY >= 1;
}
bool AreCoordinatesInvalid(int coordX, int coordY)
{
	return coordX<1 || coordX>FIELD_SIZE || coordY<1 || coordY>FIELD_SIZE;
	
}
void WarningBasedOnLastCoordinates(int lastcoordX, int lastcoordY)
{

	if ((lastcoordX == 1 || lastcoordX == FIELD_SIZE) || (lastcoordY == 1 || lastcoordY == FIELD_SIZE))
	{   
		cout << "Warning!!! Based on your previous coordinates you can't pick options";

		if (lastcoordX == 1)
		{
			cout << " - LEFT";
		}
		
		if (lastcoordX == FIELD_SIZE)
		{
			cout << " - RIGHT";
		}

		if (lastcoordY == 1)
		{
			cout << " - UP";
		}
		
		if(lastcoordY == FIELD_SIZE)
		{
			cout << " - DOWN";
		}
		cout << " - because you will go outside the game field\n";
	}

}

void PickACloseTarget(char opp_field_player[FIELD_SIZE][FIELD_SIZE], bool opp_bool_field[FIELD_SIZE][FIELD_SIZE], int &lastcoordX, int &lastcoordY, int &player_turn)
{
	char option;
	cout << "Where do you wanna hit according to your last hit(" << "\nCoordinate X - " << lastcoordX
		<< "\nCoordinate Y - " << lastcoordY << endl;
	cout << "U - UP\nD - DOWN\nL - LEFT\nR - RIGHT\n(Click 'U','D''L' or 'R')\n";
	WarningBasedOnLastCoordinates(lastcoordY, lastcoordX);

	cin >> option;
	cout << endl;

	switch (option)
	{
	case 'U': lastcoordY--;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX , lastcoordY , player_turn);
			break;
		     
	case 'D':lastcoordY++;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX , lastcoordY , player_turn);
			break;

	case 'L': lastcoordX--;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX , lastcoordY , player_turn);
	          break;

	case 'R': lastcoordX++;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX , lastcoordY , player_turn);
			  break;
	default:cout << "Error! Pick Again:\n";
		 PickACloseTarget(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn); break;
	}

}
void PickATarget(char opp_field_player[FIELD_SIZE][FIELD_SIZE], bool opp_bool_field[FIELD_SIZE][FIELD_SIZE], int &lastcoordX, int &lastcoordY, int &player_turn)
{
	char Option;
	int GuessX, GuessY;
	cout << "Do you want to make a guess:\na)On your own \nb)According to my last guess\n";
	cout << "(Click 'a' or 'b')\n";
	cin >> Option;
	cout << endl;

	switch (Option)
	{
	case 'a': cout << "NEW GUESS\n";
		cin >> GuessX >> GuessY;
			while (AreCoordinatesInvalid(GuessX, GuessY))
			{
			cout << "Invalid Coordinates! Please guess again:\n";
			cin >> GuessX >> GuessY;
			}
			lastcoordX = GuessX;
			lastcoordY = GuessY;
			HitAShip(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
		break;

	case 'b': cout << endl << lastcoordX << endl << lastcoordY << endl;
				if (HasPreviousCoordinates(lastcoordX, lastcoordY))
				{
				PickACloseTarget(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
				}
			else
			{
		cout << "Error! No previous coordinates! Pick again:\n";
		PickATarget(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
			}
			break;

	default:cout << "Error! Pick again!\n";
		PickATarget(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
		break;
	}

	
}

void PlayersTurn(char opp_field_player[FIELD_SIZE][FIELD_SIZE], bool opp_bool_field[FIELD_SIZE][FIELD_SIZE], int &lastcoordX, int &lastcoordY,int &player_turn)
{   
	int whoseturnitis = player_turn;
	while (player_turn == whoseturnitis)
	{
		
		int Option;
		cout << "Choose what to do:\n1)Show the the opponents field until now\n2)Select new target\n(Click '1' or '2')\n";
		cin >> Option;
		 
		switch (Option)
		{
		case 1: printFieldChar(opp_field_player); 
			PrintFieldLegend(); break;

		case 2: PickATarget(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);break;

		default: cout << "Error!!!\nPlease pick again option!";
				PlayersTurn(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
				break;
		}
		
		if (IsPlayerAWinner(opp_bool_field, player_turn))
		{
			break;
	    }
	}

}

//Start of Actual Game
void StartOfGame(char field_player1[FIELD_SIZE][FIELD_SIZE], char field_player2[FIELD_SIZE][FIELD_SIZE],bool bool_field1[FIELD_SIZE][FIELD_SIZE], bool bool_field2[FIELD_SIZE][FIELD_SIZE])
{
	int lastcoord_Y_p1 = -1, lastcoord_X_p1 = -1;
	int lastcoord_Y_p2 = -1, lastcoord_X_p2 = -1;
	int playersturn = 1;

	while (!(IsPlayerAWinner(bool_field1, playersturn) || IsPlayerAWinner(bool_field1, playersturn)))
	{   while(playersturn == 1)
		{
			cout << "Player One it's your turn\n";
			PlayersTurn(field_player2, bool_field2, lastcoord_X_p1, lastcoord_Y_p1, playersturn);
			if (IsPlayerAWinner(bool_field2, playersturn))
			{
				break;
			}
		}

		while (playersturn == 2)
		{
			cout << "Player Two it's your turn\n";
			PlayersTurn(field_player1, bool_field1, lastcoord_X_p2, lastcoord_Y_p2, playersturn);
		}

	}

}

int main()
{  // Player One- bool field, real playfield,available ship-sizes
	bool Field1[FIELD_SIZE][FIELD_SIZE];
	char RealHiddenField1[FIELD_SIZE][FIELD_SIZE];
	int AvailableLengthsOfShips1[NOSHIPS] = { 3,3,2 };// REDUCED THE NUM TO 3 TO TRY APP

	cout << "Players 1, Please choose your ship formation:\n";

	createField(Field1, FIELD_SIZE);
	printField(Field1, FIELD_SIZE);
	makerealField(Field1, RealHiddenField1);
	SelectShipFormation(Field1, NOSHIPS, AvailableLengthsOfShips1);
	

	// Player Two- bool field, real playfield,available ship-sizes
	bool Field2[FIELD_SIZE][FIELD_SIZE];
	char RealHiddenField2[FIELD_SIZE][FIELD_SIZE];
	int AvailableLengthsOfShips2[NOSHIPS] = { 3,3,2 };// REDUCED THE NUM TO 3 TO TRY APP

	cout << "Players 2, Please choose your ship formation:\n";

	createField(Field2, FIELD_SIZE);
	makerealField(Field2, RealHiddenField2);
	SelectShipFormation(Field2,NOSHIPS, AvailableLengthsOfShips2);
    

	//Start the game with the 2 players' ready field formations
	 
	StartOfGame(RealHiddenField1, RealHiddenField2, Field1, Field2);
	 
  
}

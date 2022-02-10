
/**
*
* Solution to course project #8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2021/2022
*
* @author Silvia Dineva
* @idnumber 4MI0600104
* @compiler VC
*
* <Main cpp file, ShipFormationSelection, Gameplay>
*
*/

#include <iostream>
#include "Legend.h"

using namespace std;

const int FIELD_SIZE = 10, NOSHIPS = 10, STOPTURN = 3;

//CHECKS IF There are any other ships where and around where the players wants to place their NEW SHIP - OR
//IF the ship can't fit in the field

//bool ShipFits(bool arr[FIELD_SIZE][FIELD_SIZE], int startcol_row, int row_col, int shiplen);
/* {
	
	if (startcol_row + shiplen > FIELD_SIZE + 1)
	{

		return false;
	}

	int startcol1 = startcol_row - 1 - 1, endcol = startcol_row + shiplen - 1;
	int startrow = row_col - 1 - 1, endrow = row_col + 1;

	

	for (int i = startcol1; i < endcol; i++) {
		for (int m = startrow; m < endrow; m++) {
			if (arr[m][i]) {
				return false;
			}
		}
	}

	return true;

}
*/

//If ShipFits() returns false - this function 'restarts' the length as available so the player can choose it for another ship
void MakeAShipAvailable(int* lengths, int len) {
	for (int i = 0; i < NOSHIPS; i++) {
		if (lengths[i] == 0)
		{
			lengths[i] = len;
			break;
		}
	}
}



// Check to see if player has won every time they hit the opponnents ship
bool IsPlayerAWinner(bool fieldofopponent[FIELD_SIZE][FIELD_SIZE], int player) {
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
bool IsShipAvailable(int* arr, const int size, int wantedshiplength) {
	for (int i = 0; i < NOSHIPS;i++) {
		if (arr[i] == wantedshiplength) {
			arr[i] = 0;
			return true;
		}
	}
	return false;
}

//Create the initial bool field matrix 
void createField(bool arr[FIELD_SIZE][FIELD_SIZE], const int size) {
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int m = 0; m < FIELD_SIZE; m++) {
			arr[i][m] = false;
		}
	}
}

//For players to see the visualized playfield
void printField(bool arr[FIELD_SIZE][FIELD_SIZE], int size)
{
	for (int i = 0; i < FIELD_SIZE + 1;i++) {
		if (i == 0) {
			cout << "  ";
		}
		else {
			cout << "| " << i;
		}
	}
	cout << endl;

	for (int i = 0; i < FIELD_SIZE;i++) {
		if (i < 9) {
			cout << " ";
		}

		cout << i + 1 << "| ";

		for (int m = 0; m < FIELD_SIZE; m++) {
			cout << arr[i][m] << "  ";
		}
		cout << endl;
	}

}
void printFieldChar(char arr[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE + 1;i++) {
		if (i == 0) {
			cout << " ";
		}
		else {
			cout << "| " << i;
		}
	}
	cout << endl;

	for (int i = 0; i < FIELD_SIZE;i++) {
		if (i < 9) {
			cout << " ";
		}
		cout << i + 1 << "| ";

		for (int m = 0; m < FIELD_SIZE; m++) {
			cout << arr[i][m] << "  ";
		}
		cout << endl;
	}
}

//Functions for ship-placement on the playfields - Either Vert/Horiz
void putAship(bool arr[FIELD_SIZE][FIELD_SIZE], int n, int m)
{
	arr[n - 1][m - 1] = true;
}

void ChooseADirectionofShip(bool [FIELD_SIZE][FIELD_SIZE], int* , int);

void putAPieceShipVert(bool arr[FIELD_SIZE][FIELD_SIZE], int collumn, int startrow, int length, int* shiplen, int currentnumship)
{
	/*if (!ShipFits(arr, length, startrow, collumn)) {
		MakeAShipAvailable(shiplen, length);
		ChooseADirectionofShip(arr, shiplen, currentnumship);
	}
	*/
	//else {
		for (int i = startrow;i < startrow + length;i++) {
			putAship(arr, i, collumn);
		}
	//}

}
void putAPieceShipHor(bool arr[FIELD_SIZE][FIELD_SIZE], int startcollumn, int row, int length, int* shiplen, int currentnumship)
{
	/*if (!ShipFits(arr, length, startcollumn, row)) {
		MakeAShipAvailable(shiplen, length);
		ChooseADirectionofShip(arr, shiplen, currentnumship);
	}
	*/
	//else {
		for (int i = startcollumn;i < startcollumn + length;i++) {
			putAship(arr, row, i);
		}
	//}
}

void ChooseLengthOfShipVer(bool arr[FIELD_SIZE][FIELD_SIZE], int* shiplen, int numship)
{
	cout << "Please choose a length from 2-4 or 6 for your ship:" << endl;
	int length;
	cin >> length;

	while (!IsShipAvailable(shiplen, NOSHIPS, length)) {
		cout << "No " << length << "-size ships left. Please select a new ship length: \n";
		cin >> length;
	}
	cout << endl;
	int col, startrow;

	cout << "Please choose from which collumn AND from which row to start:" << endl;
	cin >> col >> startrow;

	putAPieceShipVert(arr, col, startrow, length, shiplen, numship);

}
void ChooseLengthOfShipHor(bool arr[FIELD_SIZE][FIELD_SIZE], int* shiplen, int numship)
{
	cout << "Please choose a length from 2-4 or 6 for your ship:" << endl;
	int length;
	cin >> length;

	while (!IsShipAvailable(shiplen, NOSHIPS, length)) {
		cout << "No " << length << "-size ships left. Please select a new ship length: \n";
		cin >> length;
	}
	cout << endl;
	int startcol, row;

	cout << "Please choose from which collumn to start AND for which row:" << endl;
	cin >> startcol >> row;

	putAPieceShipHor(arr, startcol, row, length, shiplen, numship);

}

void ChooseADirectionofShip(bool arr[FIELD_SIZE][FIELD_SIZE], int* shiplen, int numship)
{
	cout << "Do you want to place your ship" << numship + 1 << " horrizontally or vertically? (click 'H'/'V')" << endl;
	char a;
	cin >> a;

	switch (a) {

	case 'H': ChooseLengthOfShipHor(arr, shiplen, numship); break;
	case 'V': ChooseLengthOfShipVer(arr, shiplen, numship); break;
	default: cout << "Error! Pick again: \n";
		ChooseADirectionofShip(arr, shiplen, numship); break;

	}

}

//MAIN - SHIP SELECTION FUNCTION
void SelectShipFormation(bool arr[FIELD_SIZE][FIELD_SIZE], int shipNum, int* shiplen)
{   // Could be made into a case - 1/ show my field till NOW 2/Place A Ship  3/Redact a ship/DELETE + REPLACE or CANCEL/
	// Options 1 and 3 to go back to either CHOOSE AGAIN/Directly to option 2
	// The switch-case placed inside the 'FOR' - cycle

	for (int f = 0; f < shipNum;f++) {
		ChooseADirectionofShip(arr, shiplen, f);
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

void HitAShip(char opponnentsChField[FIELD_SIZE][FIELD_SIZE], bool opponentsField[FIELD_SIZE][FIELD_SIZE], int coordX, int coordY, int& playerturn)
{
	if (opponentsField[coordY - 1][coordX - 1])
	{
		opponentsField[coordY - 1][coordX - 1] = !opponentsField[coordY - 1][coordX - 1];
		opponnentsChField[coordY - 1][coordX - 1] = 'S';
		cout << "Congratulations, You hit a ship!\n";
		printFieldChar(opponnentsChField);
		PrintFieldLegend();
		cout << endl;

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
		cout << endl;
		
		

		if (playerturn == 1)
		{
			playerturn++;
		}
		else
		{
			playerturn--;
		}
		system("CLS");
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
void WarningBasedOnLastCoordinates(int lastcoordY, int lastcoordX)
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

		if (lastcoordY == FIELD_SIZE)
		{
			cout << " - DOWN";
		}
		cout << " - because you will go outside the game field\n";
	}

}

void PickACloseTarget(char opp_field_player[FIELD_SIZE][FIELD_SIZE], bool opp_bool_field[FIELD_SIZE][FIELD_SIZE], int& lastcoordX, int& lastcoordY, int& player_turn)
{
	char option;
	cout << "\nWhere do you wanna hit according to your last hit(" << "\nCoordinate X - " << lastcoordX
		<< "\nCoordinate Y - " << lastcoordY << endl;
	cout << "U - UP\nD - DOWN\nL - LEFT\nR - RIGHT\n(Click 'U','D''L' or 'R')\n";
	WarningBasedOnLastCoordinates(lastcoordY, lastcoordX);

	cin >> option;
	cout << endl;

	switch (option)
	{
	case 'U': lastcoordY--;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
		break;

	case 'D':lastcoordY++;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
		break;

	case 'L': lastcoordX--;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
		break;

	case 'R': lastcoordX++;
		HitAShip(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn);
		break;
	default:cout << "Error! Pick Again:\n";
		PickACloseTarget(opp_field_player, opp_bool_field, lastcoordX, lastcoordY, player_turn); break;
	}

}
void PickATarget(char opp_field_player[FIELD_SIZE][FIELD_SIZE], bool opp_bool_field[FIELD_SIZE][FIELD_SIZE], int& lastcoordX, int& lastcoordY, int& player_turn)
{
	char Option;
	int GuessX, GuessY;
	cout << "\nDo you want to make a guess:\na)On your own \nb)According to my last guess\n";
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

void PlayersTurn(char opp_field_player[FIELD_SIZE][FIELD_SIZE], bool opp_bool_field[FIELD_SIZE][FIELD_SIZE], int& lastcoordX, int& lastcoordY, int& player_turn)
{
	int whoseturnitis = player_turn;
	while (player_turn == whoseturnitis)
	{
		if (IsPlayerAWinner(opp_bool_field, player_turn))
		{
			break;
		}

		int Option;
		cout << "\nChoose what to do:\n1)Show the the opponents field until now\n2)Select new target\n(Click '1' or '2')\n";
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



	}

}

//Start of Actual Game
void StartOfGame(char field_player1[FIELD_SIZE][FIELD_SIZE], char field_player2[FIELD_SIZE][FIELD_SIZE], bool bool_field1[FIELD_SIZE][FIELD_SIZE], bool bool_field2[FIELD_SIZE][FIELD_SIZE])
{
	int lastcoord_Y_p1 = -1, lastcoord_X_p1 = -1;
	int lastcoord_Y_p2 = -1, lastcoord_X_p2 = -1;
	int playersturn = 1;

	while (playersturn == 1 || playersturn == 2)
	{
		while (playersturn == 1)
		{
			cout << "\nPlayer One it's your turn\n\n";
			PlayersTurn(field_player2, bool_field2, lastcoord_X_p1, lastcoord_Y_p1, playersturn);
			if (IsPlayerAWinner(bool_field2, playersturn))
			{
				playersturn = STOPTURN;

			}
		}

		while (playersturn == 2)
		{
			cout << "\nPlayer Two it's your turn\n";
			PlayersTurn(field_player1, bool_field1, lastcoord_X_p2, lastcoord_Y_p2, playersturn);
			if (IsPlayerAWinner(bool_field1, playersturn))
			{

				playersturn = STOPTURN;

			}

		}

	}

}

//Function gives option to player to choose for themselves a ready configuration
void CopyArrInArr(bool playerarr[FIELD_SIZE][FIELD_SIZE], bool arr[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0;i < FIELD_SIZE;i++)
	{
		for (int f = 0; f < FIELD_SIZE; f++)
		{
			playerarr[i][f] = arr[i][f];

		}
	}
	system("CLS");
}
bool ChooseAReadyConfiguration(bool playerarr[FIELD_SIZE][FIELD_SIZE], bool arr[FIELD_SIZE][FIELD_SIZE])
{
	char option;
	cout << "Do you want to choose this ready configuration:\n\n";
	printField(arr, FIELD_SIZE);
	cout << "\nClick 'y' or 'n'\n\n";
	cin >> option;


	switch (option)
	{
	case 'y': CopyArrInArr(playerarr, arr); return true; break;
	case 'n': return false; break;

	default: ChooseAReadyConfiguration(playerarr, arr);break;
	}

}

int main()
{  // Player One - bool field, real playfield,available ship-sizes
	bool Field1[FIELD_SIZE][FIELD_SIZE];
	char RealHiddenField1[FIELD_SIZE][FIELD_SIZE];
	int AvailableLengthsOfShips1[NOSHIPS] = { 2,2,2,2,3,3,3,4,4,6, };


	bool ReadyField[FIELD_SIZE][FIELD_SIZE] = { {1,1,0,1,0,0,1,1,1,1}, {0,0,0,1,0,0,0,0,0,0},
		{1,0,0,1,0,1,1,1,0,1}, {1,0,0,0,0,0,0,0,0,1}, {1,0,0,0,0,0,0,0,0,0}, {1,0,0,0,0,1,0,0,0,1},
		{0,0,0,0,0,1,0,0,0,1}, {1,1,0,0,0,0,0,0,0,1}, {0}, {0,0,0,0,1,1,1,1,1,1}
	};


	cout << "Player 1, Please choose your ship formation:\n\n";


	createField(Field1, FIELD_SIZE);
	makerealField(Field1, RealHiddenField1);
	if (!ChooseAReadyConfiguration(Field1, ReadyField)) {
		SelectShipFormation(Field1, NOSHIPS, AvailableLengthsOfShips1);
	}


	// Player Two - bool field, real playfield,available ship-sizes
	bool Field2[FIELD_SIZE][FIELD_SIZE];
	char RealHiddenField2[FIELD_SIZE][FIELD_SIZE];
	int AvailableLengthsOfShips2[NOSHIPS] = { 2,2,2,2,3,3,3,4,4,6 };

	cout << "\nPlayer 2, Please choose your ship formation:\n\n";

	createField(Field2, FIELD_SIZE);
	makerealField(Field2, RealHiddenField2);
	if (!ChooseAReadyConfiguration(Field2, ReadyField)) {
		SelectShipFormation(Field2, NOSHIPS, AvailableLengthsOfShips2);
	}


	//Start the game with the 2 players' ready field formations

	StartOfGame(RealHiddenField1, RealHiddenField2, Field1, Field2);


}


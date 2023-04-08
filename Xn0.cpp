#include <iostream>
#include <string>
#include <time.h>

using namespace std;

	string Lines[10][10];
	string AllLines[30][10];
	string PossibleMoves[100];
	int LinesCount;
	int PossibleMovesCount;
	int Level;
	int Turn;
	string PlayerValue;
	string ComputerValue;
	string player1, player2;
	void Draw();
	void ReplaceValue(string matValue, string value);
	void Init();
	void GenerateAllLines();
	void GeneratePossibleMoves();
	void Run();
	void SelectLevel();
	void SelectLines();
	void RandomFirstTurn();
	void SwitchTurn();
	int IsFinished();
	bool IsCompletedLine(string line[]);
	bool IsValidMove(string value);
	void PlayerMove();
	void RandomMove();
	void BuildMove();
	void BlockMove();

void Draw(){
    if(PossibleMovesCount == 0) PossibleMoves[PossibleMovesCount-1]=1;
	int lenMax = PossibleMoves[PossibleMovesCount-1].length();
	int lenVal;
	string orizLine = string(lenMax * LinesCount + LinesCount + 1, '-');
	cout << orizLine << endl;
	for (int i = 0; i < LinesCount; i++)
	{
		cout << "|";
		for (int j = 0; j < LinesCount; j++)
		{
			lenVal = Lines[i][j].length();
			cout << string(lenMax - lenVal, ' ') << Lines[i][j] << "|";
		}
		cout << endl << orizLine << endl;
	}
}
void ReplaceValue(string matValue, string value)
{
	for (int i = 0; i < LinesCount; i++)
		for (int j = 0; j < LinesCount; j++)
			if (Lines[i][j] == matValue) Lines[i][j] = value;

	GenerateAllLines();
	GeneratePossibleMoves();
}
void Init()
{
	int k = 1;

	for (int i = 0; i < LinesCount; i++)
	{
		for (int j = 0; j < LinesCount; j++)
		{
			Lines[i][j] = to_string(k++);
		}
	}
	GenerateAllLines();
	GeneratePossibleMoves();
}
void GenerateAllLines()
{
	int k = 0;
	for (int i = 0; i < LinesCount; i++)
	{
		for (int j = 0; j < LinesCount; j++)
		{
			AllLines[k][j] = Lines[i][j]; 
			AllLines[k + 1][j] = Lines[j][i];
		}
		k += 2;
	}

	for (int j = 0; j < LinesCount; j++)
	{
		AllLines[k][j] = Lines[j][j]; 
		AllLines[k + 1][j] = Lines[j][LinesCount - j - 1]; 
	}
}
void GeneratePossibleMoves()
{
	int k = 0;
	for (int i = 0; i < LinesCount; i++)
		for (int j = 0; j < LinesCount; j++)
			if (Lines[i][j] != "X" && Lines[i][j] != "0") PossibleMoves[k++] = Lines[i][j];

	PossibleMovesCount = k;
}
void SelectLevel()
{
	cout << endl << "Please select a level:";
	cout << endl << "Level 1: Random Moves";
	cout << endl << "Level 2: Building Moves";
	cout << endl << "Level 3: Blocking Moves";
	cout << endl << "Level 4: Two players mode" << endl;

	while (true) {
		cin >> Level;
		if (Level < 1 || Level > 4)
			cout << endl << "Please enter a number between 1 and 4:";
		else
			break;
	}
}
void SelectLines() {
	cout << endl << "How many lines? ";
	int n;
	while (true) {
		cin >> n;
		if (n < 3 || n > 10)
			cout << endl << "Please enter a number between 3 and 10:";
		else {
			LinesCount=n;
			break;
		}
	}

}
void RandomFirstTurn() {
	srand(time(NULL));
	Turn = rand() % 2;
	if (Turn == 1) {
		PlayerValue = "X";
		ComputerValue = "0";
	}
	else {
		PlayerValue = "0";
		ComputerValue = "X";
	}
}
void SwitchTurn() {
	if (Turn == 0) Turn = 1;
	else Turn = 0;
}
bool IsCompletedLine(string line[])
{
	int cx = 0, c0 = 0;
	for (int i = 0; i < LinesCount; i++)
	{
		if (line[i] != "X" && line[i] != "0") return false;
		if (line[i] == "X") cx++;
		if (line[i] == "0") c0++;
		if (cx > 0 && c0 > 0) return false;
	}

	return true;
}
int IsFinished() {
	if (PossibleMovesCount == 0) return 0; //S-au terminat mutarile si este egalitate
	for (int i = 0; i < LinesCount * 2 + 2; i++)
	{
		if (IsCompletedLine(AllLines[i])) return 1; //O linie este completa si se decide cine a castigat
	}                                              //in functie de cine a facut ultima mutare
	return -1;
}
bool IsValidMove(string value)
{
	for (int i = 0; i < PossibleMovesCount; i++)
	{
		if (PossibleMoves[i] == value) return true;
	}
	return false;
}
void GetPlayers(){
	cout<<"\nPlayer 1's name: "; cin>>player1;
	cout<<"Player 2's name: "; cin>>player2;

}
void TwoPlayers(int t){
	if(PlayerValue == "X") PlayerValue = "0";
		else PlayerValue = "X";
	if(t == 1) cout<< endl << player1 << "'s turn: ";
		else cout<< endl<< player2 << "'s turn: ";
}
void PlayerMove()
{
	string matValue;
	if(Level==4) TwoPlayers(Turn);
		else cout << endl << "Player's turn: ";
	while (true)
	{
		cin >> matValue;
		if (IsValidMove(matValue))
		{
			ReplaceValue(matValue, PlayerValue);
			SwitchTurn();
			break;
		}
		else
		{
			cout << endl << "Please enter a valid move: ";
		}
	}
}
void RandomMove() {
	srand(time(NULL));
	int i = rand() % PossibleMovesCount;
	cout << PossibleMoves[i] << endl;
	ReplaceValue(PossibleMoves[i], ComputerValue);
}
void BuildMove() {
	bool buildMove = false;
	for (int i = 0; i < LinesCount * 2 + 2; i++) //parcurgem vectorul de linii
	{
		bool buildLine = false;
		string possibleMoves[10];
		int k = 0;
		for (int j = 0; j < LinesCount; j++)
		{
			if (AllLines[i][j] == PlayerValue) { //daca pozitia de pe linie este egala cu valoarea jucatorului
				buildLine = false;				//constructia pe linie devine falsa
				break;
			}
			else if (AllLines[i][j] == ComputerValue) buildLine = true; //altfel daca pozitia de pe linie este egala cu valoarea calculatorului constructia pe linie devine adevarata
			else possibleMoves[k++] = AllLines[i][j]; //altfel adaugam pozitia in vectorul de mutari posibile
		}

		if (buildLine) 
		{
			srand(time(NULL));
			int i = rand() % k;
			cout << possibleMoves[i] << endl;
			ReplaceValue(possibleMoves[i], ComputerValue);
			buildMove = true;
			break;
		} //daca putem construi pe linie calculatorul alege o pozitie random de pe linie
	}

	if (!buildMove) RandomMove(); //daca nu avem linii pe care sa construim spre castig, alegem o pozitie random 

};
void BlockMove() {
	bool blockMove = false;

	for (int i = 0; i < LinesCount * 2 + 2; i++)    // parcurgem vectorul de linii 
	{
		bool blockLine = true;
		string possibleMoves[10];
		int k = 0;
		for (int j = 0; j < LinesCount; j++)
		{
			if (AllLines[i][j] == PlayerValue) {      //daca pozitia de pe linie este egala cu pozitia jucatorului
				blockLine = false;                   //blocare linii devine falsa
				break;
			}
			else if (AllLines[i][j] != ComputerValue) possibleMoves[k++] = AllLines[i][j]; 
		} //altfel daca pozitia de pe linie este diferita de pozitia calculatorului adaugam pozitia vectorului de alegeri posibile 

		if (blockLine == true && k == 1) {
			cout << possibleMoves[0] << endl;
			ReplaceValue(possibleMoves[0], ComputerValue);
			blockMove = true;
			break;
		} //daca blocarea liniei este true si avem o pozitie posibila calculatorul alege pozitia respectiva
	}

	if (!blockMove) //daca nu s-au facut mutari de blocare
	{
		for (int i = 0; i < LinesCount * 2 + 2; i++)  //parcurgem vectorul de linii
		{
			bool blockLine = true;
			string possibleMoves[10];
			int k = 0;
			for (int j = 0; j < LinesCount; j++)
			{
				if (AllLines[i][j] == ComputerValue) {//daca pozitia de pe linie este egala cu valoarea calculatorului
					blockLine = false;			     //blocare linii devine falsa
					break;
				}
				else if (AllLines[i][j] != PlayerValue) possibleMoves[k++] = AllLines[i][j];
			} //altfel daca pozitia de pe linie este diferita de pozitia jucatorului adaugam pozitia
			  //in vectorul de alegeri posibile

			if (blockLine == true && k == 1) {
				cout << possibleMoves[0] << endl;
				ReplaceValue(possibleMoves[0], ComputerValue);
				blockMove = true;
				break;
			}//daca blocare linii true si avem o mutare posibila pe linie calculatorul alege mutarea posibila
		}
	} 

	if (!blockMove) BuildMove(); //daca nu avem o linie care necesita blocare construim o noua mutare
}
void Run()
{
	SelectLines();
	SelectLevel();
	Init();
	if(Level == 4) GetPlayers();
	Draw();
	RandomFirstTurn();
	if(Level == 4) PlayerValue = "0";
	int isFinished = -1;
	bool firstMove = true;
	while (isFinished == -1)
	{
		if (Turn == 1) PlayerMove();
		else if (firstMove) {
			if(Level==4){
				 PlayerMove();
				 SwitchTurn();
			}
			else{
			    cout << endl << "Computer's move: ";
				RandomMove();
			}
			firstMove = false;
			SwitchTurn();
		}
		else {
			if(Level!=4) cout << endl << "Computer's move: ";
			switch (Level)
			{
			case 1:
				RandomMove();
				break;
			case 2:
				BuildMove();
				break;
			case 3:
				BlockMove();
				break;
			case 4:
				PlayerMove();
				break;
			default:
				break;
			}
			if(Level != 4) SwitchTurn();
		}
		isFinished = IsFinished();
		Draw();
	}

	if (isFinished == 0) cout << endl << "DRAW!";
	else if (Turn == 0) 
			if(Level != 4) cout << endl << "YOU WON! :D";
				else cout << endl << player1 << " WON!";
	else if(Level != 4) cout << endl << "YOU LOST! :(";
			 else cout << endl << player2 << " WON!";

	int n;

	cout<<"\n\n0) Exit\n1) Start again";
	cin>>n;

	switch(n){
		case 1:
			Run();
			break;
		default:
			cout<<"You quit the game.";
			break;
	}
}

int main()
{
	Run();
	return 0;
}

//*************************************** KINDLY READ INSTRUCTIONS BEFORE TESTING THE GAME ***************************************************

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <thread>
#include <cstring>
#include <string>
#include <iostream>
#include <future>
#include <unistd.h>
using namespace std;
			
char arr[10] = { '0','1','2','3','4','5','6','7','8','9' };			// Grid For Game

//**************** FUNCTIONS PROTOTYES************************
int check_winner();
void game_board();
int select_player(int game_player);
auto de_player(int holding_pointer,string str);
int input_number(int choose,int holding_pointer);
//***********************************************************


int main()
{
	int i, choose;string str; bool indicator = false; int count=0;		// Declare Variables
	bool*point = &indicator; bool invalid = false;
	int holding_pointer = 1;  char mark;
	mkfifo("/tmp/myfifo",0666);

	// for writing
	int pfd;  char arr2[50];int pfd2;int pfd3,pfd4;int pfd7;


			pfd2 = open("/tmp/myfifo", O_RDONLY);
			read(pfd2,point,sizeof(indicator));			// Receiving Indicator to its turn or not
			close(pfd2);

			if(*point == false){
			pfd7 = open("/tmp/myfifo", O_RDONLY);
			read(pfd7,arr,sizeof(arr));
			close(pfd7);
			*point = true; 						 // turn on the game machine 
			}

			if(*point == true){

	do
	{
			if(invalid != true){
			if(count >= 1){
			pfd3 = open("/tmp/myfifo", O_RDONLY);
			read(pfd3,arr,sizeof(arr));
			close(pfd3);
			}
			}

		game_board();
		
		future<int>fp= async(select_player,holding_pointer);
		if(fp.valid()){
		holding_pointer = fp.get();					// getting marked value!
		}

		future<int>fp2 = async(input_number,choose,holding_pointer);
		if(fp2.valid()){   						// getting an input through threads
		choose = fp2.get();
		}
		mark = (holding_pointer == 1) ? 'X' : 'O';
		if (choose == 1 && arr[1] == '1'){
			arr[1] = mark;
			invalid = false;
		}
		else if (choose == 2 && arr[2] == '2'){
			arr[2] = mark;
			invalid = false;
		}
		else if (choose == 3 && arr[3] == '3'){
			arr[3] = mark;
			invalid = false;
		}
		else if (choose == 4 && arr[4] == '4'){
			arr[4] = mark;
			invalid = false;
		}
		else if (choose == 5 && arr[5] == '5'){
			arr[5] = mark;
			invalid = false;
		}
		else if (choose == 6 && arr[6] == '6'){				// Conditions To marks the index
			arr[6] = mark;
			invalid = false;
		}
		else if (choose == 7 && arr[7] == '7'){
			arr[7] = mark;
			invalid = false;
		}
		else if (choose == 8 && arr[8] == '8'){
			arr[8] = mark;
			invalid = false;
		}
		else if (choose == 9 && arr[9] == '9'){
			arr[9] = mark;
			invalid = false;
		}
		else
		{
			cout << "Invalid move ";
			invalid = true;
			cin.ignore();
			cin.get();
		}
			if(invalid != true){
			i = check_winner();
			count++;
				system("clear");
				pfd2 = open("/tmp/myfifo", O_WRONLY);		// write to pipe for second user
				write(pfd2,arr,sizeof(arr));
				close(pfd2);
			}
	} while (i == -1);
	game_board();	
	}
	if (i == 1)
	{
		cout << "==>\aPlayer " << holding_pointer << " win :) ";	// Condition for winning
	}
	else
		cout << "==>\aGame draw";					// Condition for Draw

	cin.ignore();
	cin.get();
	return 0;
}

int check_winner()
{
	if (arr[1] == arr[2] && arr[2] == arr[3])

		return 1;
	else if (arr[4] == arr[5] && arr[5] == arr[6])

		return 1;
	else if (arr[7] == arr[8] && arr[8] == arr[9])

		return 1;
	else if (arr[1] == arr[4] && arr[4] == arr[7])

		return 1;
	else if (arr[2] == arr[5] && arr[5] == arr[8])

		return 1;
	else if (arr[3] == arr[6] && arr[6] == arr[9])

		return 1;
	else if (arr[1] == arr[5] && arr[5] == arr[9])

		return 1;
	else if (arr[3] == arr[5] && arr[5] == arr[7])

		return 1;
	else if (arr[1] != '1' && arr[2] != '2' && arr[3] != '3'
		&& arr[4] != '4' && arr[5] != '5' && arr[6] != '6'
		&& arr[7] != '7' && arr[8] != '8' && arr[9] != '9')

		return 0;
	else
		return -1;
}


/*******************************************************************
FUNCTIONS OF GAME ==> "(TICK TAC TOE)"
********************************************************************/


void game_board()
{
	cout << "\n\n\tTic Tac Toe Threads Game\n\n";

	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;

	cout << "     |     |     " << endl;
	cout << "  " << arr[1] << "  |  " << arr[2] << "  |  " << arr[3] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << arr[4] << "  |  " << arr[5] << "  |  " << arr[6] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << arr[7] << "  |  " << arr[8] << "  |  " << arr[9] << endl;

	cout << "     |     |     " << endl << endl;
}

int select_player(int game_player){

game_player =  2;  	// thread selecting player turn randomly
return game_player;

}

auto de_player(int holding_pointer,string str){

if(str == "dec"){
holding_pointer--;
}
else if (str == "inc")
{
 holding_pointer++; 
}
return holding_pointer;				// decrement in player

}

int input_number(int choose,int holding_pointer){

cout << "Player " << holding_pointer << ", enter a number:  ";
cin>>choose;
return choose;

}




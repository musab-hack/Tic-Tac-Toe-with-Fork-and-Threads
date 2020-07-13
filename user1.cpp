//*************************************** KINDLY READ INSTRUCTIONS BEFORE TESTING THE GAME ***************************************************

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <thread>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
#include <future>
#include <unistd.h>
using namespace std;
						
char arr[10] = { '0','1','2','3','4','5','6','7','8','9' };			// Grid For Game

//************** FUNCTIONS PROTOTYPE******************
int check_winner();
void game_board();
int select_player(int game_player);
auto de_player(int holding_pointer,string str);
int input_number(int choose,int holding_pointer);
int choose_player();
//****************************************************

int main()
{
	int i, choose;string str;bool indicator = true;
	bool*point = &indicator; bool invalid = false; int count=0;		// Declare Variables
	int holding_pointer = 1;  char mark;
	mkfifo("/tmp/myfifo",0666);

	// for writing
	int pfd;  char arr2[50];int pfd2;int pfd3, pfd4;int pfd7;
	
			if(choose_player() != 1){
			cout<<"**Second Player Win The Toss**\n\n";
			pfd = open("/tmp/myfifo", O_WRONLY);			// Sending Indicator to second player for its turn
			write(pfd,point,sizeof(indicator));
			close(pfd);	
			pfd4 = open("/tmp/myfifo", O_RDONLY);			// get Input array from second user
			read(pfd4,arr,sizeof(arr));
			close(pfd4);
						

			} else{
			cout<<"**First Player Win The Toss**\n\n";
			indicator = false;
			pfd = open("/tmp/myfifo", O_WRONLY);			// If toss wins send other player indication
			write(pfd,point,sizeof(indicator));
			close(pfd);
			}
	do
	{
			if(invalid != true){
			if(count >= 1){
			pfd7 = open("/tmp/myfifo", O_RDONLY);
			read(pfd7,arr,sizeof(arr));
			close(pfd7);
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
		else if (choose == 4 && arr[4] == '4'){				// Condtions To Mark the index
			arr[4] = mark;
			invalid = false;
		}
		else if (choose == 5 && arr[5] == '5'){
			arr[5] = mark;
			invalid = false;
		}
		else if (choose == 6 && arr[6] == '6'){
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
			cout << "Invalid move *Press Enter*";
			invalid = true;
			cin.ignore();
			cin.get();
		}
			if(invalid != true){					// valid is checking whether wrong is given or not
			i = check_winner();
			count++;
				system("clear");	
				pfd3 = open("/tmp/myfifo", O_WRONLY);		// write to pipe for second user
				write(pfd3,arr,sizeof(arr));
				close(pfd3);
				
				}
				
	} while (i == -1);
	game_board();
	if (i == 1){
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

void winning_losing_function(string str,int holding_pointer){
	
	if(str == "Win")
	cout << "==>\aPlayer " << holding_pointer << str << " :)";
	else
	cout << "==>\aPlayer " << holding_pointer << str<< " :( ";

}

auto de_player(int holding_pointer,string str){

if(str == "dec"){
holding_pointer--;
}
else if (str == "inc")
{
 holding_pointer++; 
}
return holding_pointer;	
					// decrement in player
}

int input_number(int choose,int holding_pointer){

cout << "Player " << holding_pointer << ", enter a number:  ";
cin>>choose;
return choose;

}

int choose_player(){

	int r;
	srand(time(0));  		// Initialize random number generator.
    	r = (rand() % 3) -1;
	return r;

}

int select_player(int game_player){

game_player = 1;  				// thread selecting player turn randomly
return game_player;

}


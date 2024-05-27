#include <iostream>
#include <AdjacencyList.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//Function prototypes for different functionalities of the game.
void dice(int d);
void RollDice();
int jump(int score);
void displayBoard(int player1, int player2);

//Ladder and snake positions in the game board.
int LadderPos1[8] = { 1,4,9,21,28,51,71,80 };
int LadderPos2[8] = { 38,14,31,42,84,67,91,97 };
int SnakePos1[8] = { 17,54,62,64,87,93,95,98 };
int SnakePos2[8] = { 7,34,19,60,24,73,75,79 };

//Declaring the object of AdjacencyList globally so that each function can use it.
AdjacencyList Position(100);

int main()
{
	int choice;
	cout << "\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t|---------------SNAKES AND LADDERS GAME--------------|" << endl;
	cout << "\t\t\t|----------------------------------------------------|" << endl << endl;
	system("pause");
	cout << endl << "Menu" << endl;

	for (int i = 1;i <= 100;i++)
	{
		//Adding edges to those vertices from which ladder originates.
		if (i == 1 || i == 4 || i == 9 || i == 21 || i == 28 || i == 51 || i == 71 || i == 80)
		{
			//Adding edges.
			if (i == 1)
				Position.addEdge(1, 38);
			//Adding edges.
			else if (i == 4)
				Position.addEdge(4, 14);
			//Adding edges.
			else if (i == 9)
				Position.addEdge(9, 31);
			//Adding edges.
			else if (i == 21)
				Position.addEdge(21, 42);
			//Adding edges.
			else if (i == 28)
				Position.addEdge(28, 84);
			//Adding edges.
			else if (i == 51)
				Position.addEdge(51, 67);
			//Adding edges.
			else if (i == 71)
				Position.addEdge(71, 91);
			//Adding Edges.
			else
				Position.addEdge(80, 97);

		}

		//Adding edges to those vertices from which snake originates.
		else if (i == 17 || i == 54 || i == 62 || i == 64 || i == 87 || i == 93 || i == 95 || i == 98)
		{
			//Adding edges.
			if (i == 17)
				Position.addEdge(17, 7);
			//Adding edges.
			else if (i == 54)
				Position.addEdge(54, 34);
			//Adding edges.
			else if (i == 62)
				Position.addEdge(62, 19);
			//Adding edges.
			else if (i == 64)
				Position.addEdge(64, 60);
			//Adding edges.
			else if (i == 87)
				Position.addEdge(87, 24);
			//Adding edges.
			else if (i == 93)
				Position.addEdge(93, 73);
			//Adding edges.
			else if (i == 95)
				Position.addEdge(95, 75);
			//Adding edges.
			else if (i == 98)
				Position.addEdge(98, 79);
		}

		//Adding six edges to one vertice. Because when a dice rolls it can go to next 6 vertices maximum. If there are no ladder and snake on a vertice.
		else
		{
			for (int j = i;j <= i + 5 && j <= 100;j++)
				Position.addEdge(i, j + 1);
		}
	}
	//Calling the function to roll the dice.
	RollDice();
	return 0;
}

void RollDice()
{
	//Declaring variables for different purposes.
	string name1, name2;

	//Choice for Algorithm or roll dice.
	char choice;

	//Storing the scores of both players.
	int score1 = 0, score2 = 0;

	//Storing the previous scores in case some player's goes beyond 100.
	int prev1, prev2;
	int i;

	//Getting the names from the players.
	cout << "Enter name of player 1: ";
	getline(cin, name1);
	cout << "Enter name of player 2: ";
	getline(cin, name2);

	//Calling a function to show the game board.
	displayBoard(score1, score2);

	//Declared to detect the number of sixes for a player.
	int value1 = 0, value2 = 0, CountofSix1 = 0, CountofSix2 = 0;

	//Allowing players to roll the dice until one of them wins the game.
	while (true)
	{
		//Player's 1 turn to roll the dice.
		if (score1 != 100 && value2 != 6 && CountofSix1 != 3)
		{
			//Declaring condition that BFS can't be run if player's score=0.
			if (score2 != 0)
			{
				//Getting the key presses from the player 1.
				cout << endl << name1 << "'s turn,\n=> Press Key R to  to roll the die\n=> Press S to find the shortest path from the current vertex\n";

				//Getting the input.
				cin >> choice;
			}

			//Validating if user wants to trigger the algorithm.
			if (choice == 'S' || choice == 's' && score1 != 0)
			{
				Position.BFS(score1, LadderPos1, LadderPos2, SnakePos1);
			}


			if (true)
			{
				cout << endl;
				cout << "--------------------------------" << endl;
				cout << "   |Rolling The Dice For " << name1 << "|     " << endl;
				cout << "--------------------------------" << endl;
				//Generating a different random number with different seed number each time the program runs.
				srand(time(0));

				//Generating the random input from 1 to 6.
				value1 = rand() % 6 + 1;
				cout << "You rolled a " << value1 << endl;

				//Calling a function to show the user value.
				dice(value1);

				//Storing the previous scores in case some player's goes beyond 100.
				prev1 = score1;

				//Adding score.
				score1 += value1;

				//Giving another turn to the player if some player gets a six in his/her turn.
				if (value1 == 6)
				{
					cout << "Wow! you rolled a six you will get another turn.\n";

					//Showing that a player can't get more than 3 sixes.
					CountofSix1++;
					continue;
				}

				//Checking if some player has reached special vertices (Ladder and Snake).
				score1 = jump(score1);

				//Winning Condition: It means that player has reached the 100th vertex. So that, he will declare the winner.
				if (score1 == 100)
				{
					//Showing player 1 has won the game and the game will stop after showing these statements.
					cout << "\n\tPrevious Position of " << name1 << " is : " << prev1 << endl;
					cout << "\n\t" << name1 << " has crossed 100!" << endl;
					cout << name1 << " has won the game" << endl;
					cout << "Better luck next time " << name2 << endl;

					//Declaring a variable to ask user whether he/she wants to restart the game.
					char gameContinue;

					cout << "Press R to restart the game.\nPress E to exit the game.\n=>";
					cin >> gameContinue;

					//Terminating the game because some player 1 has won the game.
					if (gameContinue == 'E' || gameContinue == 'e')
						exit(0);
					//Restarting the game.
					else
						RollDice();
				}

				//If players goes beyond the 100th vertex then he/she will loose it's turn.
				else if (score1 > 100)
				{
					score1 = prev1;

					//Displaying overflow message.
					cout << "Ohh! you went beyond 100 your new position still remains the same which is : " << score1 << endl;
				}


				//Concluding the player's turn.
				cout << "\n\tPrevious Position of " << name1 << " is : " << prev1 << endl;
				cout << "\n\tCurrent Position Of " << name1 << " is : " << score1 << endl;

				//It will show the statement "Press any key to continue" By pressing any key you would able to move to the next state.
				system("pause");
			}

		}

		//Initialized again zero because player's turn is over.
		CountofSix1 = 0;

		//Player's 2 turn to roll the dice.
		if (score2 != 100 && value1 != 6 && CountofSix2 != 3)
		{
			//Declaring condition that BFS can't be run if player's score=0.
			if (score2 != 0)
			{
				//Getting the key presses from the player 1.
				cout << endl << name2 << "'s turn,\n=> Press Key R to  to roll the die\n=> Press S to find the shortest path from the current vertex\n";

				//Getting the input.
				cin >> choice;
			}

			//Validating if user wants to trigger the algorithm.
			if (choice == 'S' || choice == 's' && score2 != 0)
			{
				Position.BFS(score2, LadderPos1, LadderPos2, SnakePos1);
			}


			if (true)
			{
				cout << endl;
				cout << "--------------------------------" << endl;
				cout << "   |Rolling The Dice For " << name2 << "|     " << endl;
				cout << "--------------------------------" << endl;

				//Generating a different random number with different seed number each time the program runs.
				srand(time(0));

				//Generating the random input from 1 to 6.
				value2 = rand() % 6 + 1;
				cout << "You rolled a " << value2 << endl;

				//Calling a function to show the user value.
				dice(value2);

				//Storing the previous scores in case some player's goes beyond 100.
				prev2 = score2;

				//Adding scores.
				score2 += value2;

				//Giving another turn to the player if some player gets a six in his/her turn.
				if (value2 == 6)
				{
					cout << "Wow! you rolled a six you will get another turn.\n";

					//Showing that a player can't get more than 3 sixes.
					CountofSix2++;
					continue;
				}

				//Checking if some player has reached special vertices (Ladder and Snake).
				score2 = jump(score2);

				//Wining Condition: It means that player has reached the 100th vertex. So that, he will declare the winner.
				if (score2 == 100)
				{
					//Showing player 1 has won the game and the game will stop after showing these statements.
					cout << "\n\tPrevious Position of " << name2 << " is : " << prev2 << endl;
					cout << "\n\t" << name2 << " has crossed 100!" << endl;
					cout << name2 << " has won the game" << endl;
					cout << "Better luck next time " << name1 << endl;

					//Declaring a variable to ask user whether he/she wants to restart the game.
					char gameContinue;

					cout << "Press R to restart the game.\nPress E to exit the game.\n=>";
					cin >> gameContinue;

					//Terminating the game because some player 1 has won the game.
					if (gameContinue == 'E' || gameContinue == 'e')
						exit(0);

					//Restarting the game.
					else
						RollDice();
				}

				//If players goes beyond the 100th vertex then he/she will loose it's turn.
				else if (score2 > 100)
				{
					score2 = prev2;

					//Displaying overflow message.
					cout << "Ohh! you went beyond 100 your new position still remains the same which is : " << score2 << endl;
				}
				//Concluding the player's turn.
				cout << "\n\tPrevious Position of " << name2 << " is : " << prev2 << endl;
				cout << "\n\tCurrent Position Of " << name2 << " is : " << score2 << endl;

				//It will show the statement "Press any key to continue" By pressing any key you would able to move to the next state.
				system("pause");
			}
			//Initialized again zero because player's turn is over.
			CountofSix2 = 0;
		}

		//Calling a function to show the game board.
		displayBoard(score1, score2);

	}
}

void dice(int d)
{
	//If the dice shows one in some player's turn.
	if (d == 1)
	{
		cout << " ----- " << endl << "|     |" << endl << "|  O  |" << endl << "|     |" << endl << " ----- " << endl;
	}
	//If the dice shows two in some player's turn.
	else if (d == 2)
	{
		cout << " ----- " << endl << "|  O  |" << endl << "|     |" << endl << "|  O  |" << endl << " ----- " << endl;
	}
	//If the dice shows three in some player's turn.
	else if (d == 3)
	{
		cout << " ----- " << endl << "|  O  |" << endl << "|  O  |" << endl << "|  O  |" << endl << " ----- " << endl;
	}
	//If the dice shows four in some player's turn.
	else if (d == 4)
	{
		cout << " ----- " << endl << "|O   O|" << endl << "|     |" << endl << "|O   O|" << endl << " ----- " << endl;
	}
	//If the dice shows five in some player's turn.
	else if (d == 5)
	{
		cout << " ----- " << endl << "|O   O|" << endl << "|  O  |" << endl << "|O   O|" << endl << " ----- " << endl;
	}
	//If the dice shows six in some player's turn.
	else
	{
		cout << " ----- " << endl << "|O   O|" << endl << "|O   O|" << endl << "|O   O|" << endl << " ----- " << endl;
	}
}

int jump(int score)
{
	//Checking has some player reached the special vertice or not?
	for (int i = 0;i < 8;i++)
	{
		//If some player has reached the ladder vertex.
		if (score == LadderPos1[i])
		{
			cout << "You climbed a ladder to " << LadderPos2[i] << endl;
			score = LadderPos2[i];
			cout << "   " << score << "   " << endl;
			cout << "  |__|  " << endl;
			cout << "  |__|  " << endl;
			cout << "  |__|  " << endl;
			cout << "  |__|  " << endl;
			cout << "  |__|  " << endl;
			cout << "  |  |  " << endl;
			cout << " " << LadderPos1[i] << " ";
			break;
		}

		//If some player has reached the ladder vertex.
		else if (score == SnakePos1[i])
		{
			cout << "You were caught by a snake and were demoted to " << SnakePos2[i] << endl;
			score = SnakePos2[i];
			cout << "              **    **    **        " << endl;
			cout << "    " << SnakePos1[i] << " <<*  *   *  *  *  *  *  *>>  " << score << endl;
			cout << "          **     **    **    **     " << endl;
			break;

		}
	}
	//Returning score can be updated or not.
	return score;
}

void displayBoard(int player1, int player2)
{
	system("cls");  //Clearing screen to show the game board.

	cout << "\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t|--------- SNAKES AND LADDERS GAME BOARD  -----------|" << endl;
	cout << "\t\t\t|----------------------------------------------------|" << endl << endl;

	//Iterating a loop to show the game board.
	for (int row = 10; row >= 1; row--)
	{
		for (int col = 1; col <= 10; col++)
		{
			int square = (row - 1) * 10 + col;

			//Showing Position of the players on the game board.
			if (square == player1 && square == player2)
			{
				//Showing player's position when they are at same position on the game board.
				cout << "P1/P2\t";
			}

			//Player's one position.
			else if (square == player1)
			{
				//Showing player's position on the game board.
				cout << "P1\t";
			}

			//Player's two position.s
			else if (square == player2)
			{
				//Showing player's position on the game board.
				cout << "P2\t";
			}

			else
			{
				cout << square << "\t";
			}
		}
		cout << endl;
	}
}

# Snakes and Ladders Game

This project implements a command-line based "Snakes and Ladders" game in C++ using an adjacency list representation of the game board. The game allows two players to roll dice and move along the board, navigating through ladders and snakes. Additionally, players can trigger a BFS (Breadth First Search) algorithm to find the shortest path from their current position to the end.

## Features

- Two-player game
- Real-time dice rolling
- Game board contains snakes and ladders
- Players can find the shortest path using the BFS algorithm
- Randomized dice rolls for fair gameplay

## How the Game Works

1. **Game Setup**:
   - The board is represented using an adjacency list with 100 vertices (for each square on the board).
   - Ladders move players upwards, and snakes bring players downwards.
   - The game allows players to roll a dice and move forward based on the result.
   - If a player lands on a ladder's start, they are moved to the end of the ladder.
   - If a player lands on a snake's head, they are moved to the snake's tail.

2. **Rolling the Dice**:
   - Players take turns rolling the dice.
   - If a player rolls a 6, they get another turn.
   - The player’s score is updated based on the dice roll, but if the player exceeds 100, their position remains unchanged.
   
3. **BFS Algorithm**:
   - Players can trigger the BFS algorithm to calculate the shortest path to the last square (100) from their current position.
   - The algorithm finds the minimum number of dice rolls needed to reach the end.
   
4. **Game End**:
   - The game ends when a player reaches square 100, and the player is declared the winner.
   - The player can then choose to restart or exit the game.

## How to Play

1. **Start the Game**: 
   - Upon starting, enter the names of the two players.
   
2. **Rolling the Dice**:
   - On your turn, press 'R' to roll the dice.
   - You may also press 'S' to calculate the shortest path using the BFS algorithm if your score is greater than 0.

3. **Winning**:
   - The first player to reach square 100 wins the game.

4. **Snakes and Ladders Positions**:
   - **Ladders**: 
     - 1 -> 38
     - 4 -> 14
     - 9 -> 31
     - 21 -> 42
     - 28 -> 84
     - 51 -> 67
     - 71 -> 91
     - 80 -> 97
   - **Snakes**: 
     - 17 -> 7
     - 54 -> 34
     - 62 -> 19
     - 64 -> 60
     - 87 -> 24
     - 93 -> 73
     - 95 -> 75
     - 98 -> 79

## Compilation Instructions

To compile and run the program, use the following commands:

```bash
g++ -o SnakesAndLadders main.cpp AdjacencyList.cpp
./SnakesAndLadders
```

## Future Enhancements

- Add graphical interface for better user experience.
- Implement AI for single-player mode.
- Customize the number of players and board size.

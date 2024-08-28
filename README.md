# Mines-Bet-Game
## Overview
Mines-Bet-Game is a console-based betting game where you aim to uncover the most diamonds from a 5x5 grid without hitting any hidden bombs. The game is written in C++ using Object-Oriented Programming (OOP) principles, with robust user input validation to enhance the gameplay experience.

## Features
* 5x5 Grid: The game board is a 5x5 grid where diamonds and bombs are randomly placed.
* Betting System: Players place a bet before starting the game. The bet increases based on the number of diamonds uncovered without hitting a bomb.
* Random Bomb Placement: Five bombs are hidden within the grid, which players must avoid.
* Time-Trap: If a player takes more than 30 seconds to decide on their next move, they automatically lose.
* High-Bet Trap: If a player bets over 30,000 units and uncovers three diamonds, they will automatically lose on their next move.
* Statistics: Track your game history and view your best game in terms of winnings.
* User-Friendly Interface: The game provides clear instructions and feedback during gameplay.

## Gameplay Instructions
### Start the Game:

Enter your name and deposit an initial amount of money.
Create a new game and place your bet.
### Playing the Game:

Select a cell by entering the row and column numbers.
If the cell contains a diamond, your winnings increase based on a percentage.
If you uncover a bomb, you lose your bet.
You can withdraw your winnings at any time, provided you've uncovered at least three diamonds and your total winnings exceed a specific threshold.
### Traps:

* Time Trap: If you take longer than 30 seconds to make a move, a bomb will randomly move to your selected cell.
* High-Bet Trap: If your bet exceeds 30,000 units and you've uncovered three diamonds, the next move will result in a loss.

### End the Game:

You can view your game history, showing details such as wins, losses, and total earnings.
The game also tracks your best game with the highest earnings.
## How to Run
Compile the Program:
Ensure you have a C++ compiler installed.
Compile the source code using the following command:

 ```
g++ -o MinesBetGame ./input_utils.h ./Tablero.cpp ./Partida.cpp ./Jugador.cpp ./Minas.cpp ./main.cpp -w
 ```

## Run the Program:

Run the compiled program in your terminal:

 ```
./MinesBetGame
 ```

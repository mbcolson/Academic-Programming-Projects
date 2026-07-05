# Tic Tac Toe

A text-based Java implementation of the classic Tic Tac Toe game for two players.

## Features

* Two-player gameplay using `O` and `X`
* 3x3 game board displayed in the console
* Prompts players to enter row and column coordinates
* Validates row and column input
* Prevents players from choosing occupied spaces
* Detects winning combinations across:

  * Rows
  * Columns
  * Diagonals
* Detects a full board and ends the game in a draw

## Files

```text id="fk9q1p"
TicTacToe.java  # Main source file and game logic
README.md       # Project documentation
```

## Notes

* Board positions use zero-based coordinates: `0`, `1`, and `2`.
* Player `O` moves first.
* The game runs until a player wins or the board is full.
* Input is handled through the Java `Scanner` class.

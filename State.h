#pragma once

#include <array>
#include <vector>
#include <utility>
#include <iterator>
#include <string>
#include <iostream>
#include "Action.h"

enum Player {
	Black, White
};

Player opponent(Player player);

class Board {
public:
	Board();
	Board(char board[64]);
	Board(Board& const obj);

	void printBoard(Player player) const;
	char at(int x, int y) const;
	char at(int index) const;
	bool set(int x, int y, char piece);
	bool setOff(int x, int y, Player piece);
	bool canSetOff(int x, int y, Player piece) const;
	std::vector<std::pair<int, int>> getAvailable(Player who) const;
	bool takeAction(Action action);
private:
	std::array<char, 64> board;
	bool XYInRange(int x, int y) const;
	std::vector<std::pair<int, int>> directions = {
													{1, 0}, {1, 1} , {0, 1} ,{-1, 1} , 
													{-1, 0} ,{-1, -1} , {0, -1} , {1, -1}
													};
};

class State
{
public:
	State(Board board, Player player);
	State(State& obj);

public:
	Player player;
	Board board;
public:
	std::vector<Action> getAvailableActions();
	std::pair<bool, Player> getStateResult();
	State getNextState(Action action);
private:
};


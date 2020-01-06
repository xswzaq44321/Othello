#include "State.h"

Player opponent(Player player) {
	if (player == White) {
		return Black;
	}
	else if(player == Black) {
		return White;
	}
}

Board::Board()
{
	std::fill(board.begin(), board.end(), -1);
	board[27] = White;
	board[28] = Black;
	board[35] = Black;
	board[36] = White;
}

Board::Board(char board[64])
{
	std::copy(board, board + 64, std::begin(this->board));
}

Board::Board(Board& const obj)
{
	this->board = obj.board;
}

void Board::printBoard(Player player) const
{
	static const std::string wholeNumber[8] = { "¢¯", "¢°" , "¢±" , "¢²" , "¢³" , "¢´" , "¢µ" , "¢¶" };
	auto bar = getAvailable(player);
	std::cout << "¡@¡@¢¯¡@¢°¡@¢±¡@¢²¡@¢³¡@¢´¡@¢µ¡@¢¶¡@" << std::endl;
	std::cout << "¡@¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð" << std::endl;
	for (int y = 0; y < 8; ++y) {
		std::cout << wholeNumber[y];
		for (int x = 0; x < 8; ++x) {
			int index = y * 8 + x;
			if (board[index] == -1) {
				bool canSet = false;
				for (auto& const it : bar) {
					if (it.first == x && it.second == y) {
						canSet = true;
						break;
					}
				}
				std::cout << "¡U" << (canSet ? "¡D" : "¡@");
			}
			else if (board[index] == Black) {
				std::cout << "¡U¡³";
			}
			else if (board[index] == White) {
				std::cout << "¡U¡´";
			}
		}
		std::cout << "¡U" << std::endl;
		std::cout << "¡@¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð¡Ð" << std::endl;
	}
}

char Board::at(int x, int y) const
{
	int index = y * 8 + x;
	return board[index];
}

char Board::at(int index) const
{
	return board[index];
}

bool Board::set(int x, int y, char piece)
{
	if (!XYInRange(x, y)) {
		return false;
	}
	int index = y * 8 + x;
	board[index] = piece;
	return true;
}

bool Board::setOff(int x, int y, Player player)
{
	if (!XYInRange(x, y)) {
		return false;
	}
	int index = y * 8 + x;
	if (board[index] != -1 || !canSetOff(x, y, player)) {
		return false;
	}
	board[index] = player;
	for (std::pair<int, int> direction : directions) {
		int xx = x + direction.first, yy = y + direction.second;
		if (!XYInRange(xx, yy))
			continue;
		if (at(xx, yy) == opponent(player)) {
			while (XYInRange(xx, yy)) {
				if (at(xx, yy) == player) {
					int xxx = x + direction.first, yyy = y + direction.second;
					while (at(xxx, yyy) == opponent(player)) {
						set(xxx, yyy, player);
						xxx += direction.first;
						yyy += direction.second;
					}
				}
				xx += direction.first;
				yy += direction.second;
			}
		}
	}
	return true;
}

bool Board::canSetOff(int x, int y, Player player) const
{
	if (!XYInRange(x, y)) {
		return false;
	}
	for (std::pair<int, int> direction : directions) {
		int xx = x + direction.first, yy = y + direction.second;
		if (!XYInRange(xx, yy))
			continue;
		if (at(xx, yy) == opponent(player)) {
			while (XYInRange(xx, yy)) {
				if (at(xx, yy) == player)
					return true;
				xx += direction.first;
				yy += direction.second;
			}
		}
	}
	return false;
}

std::vector<std::pair<int, int>> Board::getAvailable(Player who) const
{
	std::vector<std::pair<int, int>> rtv;
	for (int x = 0; x < 8; ++x) {
		for (int y = 0; y < 8; ++y) {
			if (canSetOff(x, y, who))
				rtv.push_back(std::make_pair(x, y));
		}
	}
	return rtv;
}

bool Board::takeAction(Action action)
{
	return false;
}

bool Board::XYInRange(int x, int y) const
{
	if (x < 0 || x > 7 || y < 0 || y > 7) {
		return false;
	}
	return true;
}

State::State(Board board, Player player):
	board(board), player(player)
{
}

State::State(State& obj):
	board(obj.board), player(obj.player)
{
}

std::vector<Action> State::getAvailableActions()
{
	return std::vector<Action>();
}

std::pair<bool, Player> State::getStateResult()
{
	return std::pair<bool, Player>();
}

State State::getNextState(Action action)
{
	State rtv(*this);
	rtv.board.takeAction(action);
	return rtv;
}

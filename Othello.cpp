#include <iostream>
#include <random>
#include "State.h"

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());

int main()
{
    std::cout << "Who first? (0: player, 1: computer)\n";
	int turn = 0, temp;
	while (!turn) {
		std::cin >> temp;
		if (temp == 0) {
			turn = 1;
		}
		else if (temp == 1) {
			turn = -1;
		}
		else {
			std::cout << "Who first? (0: player, 1: computer)\n";
		}
	}
	Player player = Black;
	Board b;
	b.printBoard(player);
	int x, y;
	std::cout << "Black: ";
	while (true) {
		if (turn == 1) {
			std::cin >> x >> y;
		}
		else {
			x = 0;
			y = 0;
			std::cout << x << ' ' << y << std::endl;
		}
		if (b.setOff(x, y, player)) {
			player = opponent(player);
			b.printBoard(player);
		}
		else {
			std::cout << "Invalid move!!" << std::endl;
		}
		std::cout << (player == Black ? "Black: " : "White: ");
	}
}
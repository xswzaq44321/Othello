#pragma once

#include <random>
#include <vector>
#include <utility>
#include <cmath>
#include "State.h"
#include "Action.h"

extern std::random_device rd;
extern std::default_random_engine gen;


class Node
{
public:
	Node(State state, Node* parent);

public:
	State state;
	std::vector<Action> untriedActions;
	Node* parent;
	std::vector<Node*> children;
	double Q, N;

public:
	static Action getRandomAction(std::vector<Action> available_actions);
	double weightFunc(double C);
	std::pair<int, Node*> select(double C);
	Node* expand();
	void update(Player winner);
	Player rollout();
	bool isFullExpand();
	bool isRootNode();
};


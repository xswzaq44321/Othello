#include "Node.h"

Action Node::getRandomAction(std::vector<Action> available_actions) {
	std::uniform_int_distribution<int> dis(0, available_actions.size() - 1);
	return available_actions[dis(gen)];
}

Node::Node(State state, Node* parent = nullptr):
	state(state)
{
	this->untriedActions = state.getAvailableActions();
	this->parent = parent;
	this->Q = 0;
	this->N = 0;
}

double Node::weightFunc(double C)
{
	double w;
	if (N != 0) {
		w = -Q / N + C * sqrt(2 * log(parent->N) / N);
	}
	else {
		w = 0.0;
	}
	return w;
}

std::pair<int, Node*> Node::select(double C)
{
	int action = 0;
	int maxWeight = -1e8;
	for (int i = 0; i < children.size(); ++i) {
		auto childNode = children[i];
		if (childNode->weightFunc(C) > maxWeight) {
			maxWeight = childNode->weightFunc(C);
			action = i;
		}
	}
	return std::make_pair(action, children[action]);
}

Node* Node::expand()
{
	auto action = untriedActions.at(0);
	untriedActions.erase(untriedActions.begin());

	auto currentPlayer = state.player;

	auto nextBoard = state.board;
	nextBoard.takeAction(action);
	auto nextPlayer = opponent(currentPlayer);
	State state(nextBoard, nextPlayer); 
	Node* childNode = new Node(state, this);
	this->children.push_back(childNode);
	return childNode;
}

void Node::update(Player winner)
{
	N += 1;
	auto oppo = opponent(state.player);
	if (winner == state.player) {
		Q += 1;
	}
	else if (winner == oppo) {
		Q -= 1;
	}
	if (isRootNode()) {
		parent->update(winner);
	}
}

Player Node::rollout()
{
	auto currentState = this->state;
	Player winner;
	while (true) {
		auto result = currentState.getStateResult();
		bool isOver = result.first;
		winner = result.second;
		if (isOver)
			break;
		auto availableActions = currentState.getAvailableActions();
		auto action = Node::getRandomAction(availableActions);
		currentState = currentState.getNextState(action);
	}
	return winner;
}

bool Node::isFullExpand()
{
	return untriedActions.size() == 0;
}

bool Node::isRootNode()
{
	return parent == nullptr;
}

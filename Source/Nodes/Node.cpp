#include "Node.h"
#include "NodeEditor.h"

Node::Node(int numInputs) {
	this->numInputs = numInputs;
	for (int i = 0; i < numInputs; i++)
		inputs.push_back(nullptr);
}
Node::~Node() {
	disconnectAll();
	for (int i = 0; i < numInputs; i++)
		delete inputs[i];
	inputs.clear();
}
void Node::connectInput(int index, Node* other) {
	jassert(index < numInputs);
	inputs[index] = other;
}
void Node::disconnectInput(int index) {
	jassert(index < numInputs);
	inputs[index] = nullptr;
}
void Node::disconnectAll() {
	for (int i = 0; i < numInputs; i++)
		inputs[i] = nullptr;
}
int Node::getNumInputs() {
	return numInputs;
}
std::vector<Node*>& Node::getInputs() {
	return inputs;
}
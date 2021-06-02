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
void Node::initBuffer(int bufferSize) {
	buffer.reserve(bufferSize);
}
void Node::connectInput(int index, Node* other) {
	jassert(index < numInputs);
	inputs[index] = other;
}
void Node::disconnectInput(int index) {
	jassert(index < numInputs);
	inputs[index] = nullptr;
}
void Node::disconnectInput(Node* potentialInput) {
	for (int i = 0; i < numInputs; i++)
		if (inputs[i] == potentialInput)
			inputs[i] = nullptr;
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
bool Node::isMarked() {
	return editor->marked;
}
void Node::mark(bool marked = true) {
	editor->marked = marked;
}
int Node::getNumConnectedInputs() {
	int numConnectedInputs = 0;
	for (int i = 0; i < numInputs; i++)
		if (inputs[i])
			numConnectedInputs++;
	return numConnectedInputs;
}
int Node::getNumMarkedInputs() {
	int numMarkedInputs = 0;
	for (int i = 0; i < numInputs; i++)
		if (inputs[i] && inputs[i]->isMarked())
			numMarkedInputs++;
	return numMarkedInputs;
}
void Node::getInputInfo(int& getNumConnectedInputs, int& getNumMarkedInputs) {
	for (int i = 0; i < numInputs; i++)
		if (inputs[i]) {
			getNumConnectedInputs++;
			if (inputs[i]->isMarked())
				getNumMarkedInputs++;
		}
}
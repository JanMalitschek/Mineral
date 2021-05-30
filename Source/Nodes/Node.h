#ifndef NODE
#define NODE

#include "../Utility/simdFloat.h"
#include "../Utility/simdInt.h"
#include "../LookAndFeel/LookAndFeel.h"
#include <JuceHeader.h>
#include <vector>

using namespace juce;

enum NodeType {
	kDummy,
	kNumNodeTypes
};

class NodeEditor;

class Node {
public:
	Node(int numInputs);
	~Node();
	virtual void process(int numSamples) = 0;
	void connectInput(int index, Node* other);
	void disconnectInput(int index);
	void disconnectAll();
	int getNumInputs();
	std::vector<Node*>& getInputs();
	NodeEditor* editor;
protected:
	std::vector<Node*> inputs;
	int numInputs;
};

#endif
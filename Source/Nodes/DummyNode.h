#ifndef DUMMY_NODE
#define DUMMY_NODE

#include "Node.h"
#include "NodeEditor.h"

class DummyNode : public Node {
public:
	DummyNode();
	void process(int) override;
};

class DummyNodeEditor : public NodeEditor {
public:
	DummyNodeEditor(NodeGraphEditor* nge);
	void paint(Graphics&) override;
};

#endif
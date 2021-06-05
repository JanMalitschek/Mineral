#ifndef OUTPUT_NODE
#define OUTPUT_NODE

#include "Node.h"
#include "NodeEditor.h"

class OutputNode : public Node {
public:
	OutputNode();
	void process(int) override;
};

class OutputNodeEditor : public NodeEditor {
public:
	OutputNodeEditor(NodeGraphEditor* nge);
	void paint(Graphics&) override;
};

#endif
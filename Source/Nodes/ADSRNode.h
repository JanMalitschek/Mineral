#ifndef ASMR_NODE
#define ASMR_NODE

#include "Node.h"
#include "NodeEditor.h"

class ADSRNode : public Node {
public:
	ADSRNode();
	void process(int) override;
};

class ADSRNodeEditor : public NodeEditor {
public:
	ADSRNodeEditor(NodeGraphEditor* nge);
	void paint(Graphics&) override;
};

#endif
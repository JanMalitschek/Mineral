#include "NodeFactory.h"
#include "../Graphs/NodeGraphEditor.h"

#include "../DummyNode.h"
#include "../MIDIInputNode.h"
#include "../OutputNode.h"
#include "../ADSRNode.h"

void NodeFactory::createNodeInstance(NodeType type, std::vector<std::unique_ptr<NodeEditor>>& nodeEditors, NodeGraphEditor* nge) {
	switch (type) {
	case NodeType::kDummy:
		nodeEditors.push_back(std::unique_ptr<NodeEditor>(new DummyNodeEditor(nge)));
		break;
	case NodeType::kMIDINoteInput:
		nodeEditors.push_back(std::unique_ptr<NodeEditor>(new MIDINoteInputNodeEditor(nge)));
		break;
	case NodeType::kMIDIVelocityInput:
		nodeEditors.push_back(std::unique_ptr<NodeEditor>(new MIDIVelocityInputNodeEditor(nge)));
		break;
	case NodeType::kOutput:
		nodeEditors.push_back(std::unique_ptr<NodeEditor>(new OutputNodeEditor(nge)));
		break;
	case NodeType::kADSR:
		nodeEditors.push_back(std::unique_ptr<NodeEditor>(new ADSRNodeEditor(nge)));
		break;
	default:
		nodeEditors.push_back(std::unique_ptr<NodeEditor>(new DummyNodeEditor(nge)));
		break;
	}
}
String NodeFactory::nodeTypeToName(NodeType type) {
	switch (type) {
	case NodeType::kDummy: return "DUMMY NODE";
	case NodeType::kMIDINoteInput: return "MIDI Note In";
	case NodeType::kMIDIVelocityInput: return "MIDI Vel In";
	case NodeType::kOutput: return "Output";
	case NodeType::kADSR: return "ADSR Envelope";
	default: return "DUMMY NODE";
	}
}
void NodeFactory::displayAddNodeMenu(NodeGraphEditor* nge) {
	PopupMenu menu;
	for (int i = 0; i < (int)NodeType::kNumNodeTypes; i++)
		menu.addItem(i + 1, nodeTypeToName((NodeType)i));
	int choice = menu.show();
	if (choice > 0)
		nge->addNode((NodeType)(choice - 1));
}
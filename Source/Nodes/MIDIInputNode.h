#ifndef MIDI_INPUT_NODE
#define MIDI_INPUT_NODE

#include "Node.h"
#include "NodeEditor.h"

class MIDINoteInputNode : public Node {
public:
	MIDINoteInputNode();
	void process(int) override;
};

class MIDINoteInputNodeEditor : public NodeEditor {
public:
	MIDINoteInputNodeEditor(NodeGraphEditor* nge);
	void paint(Graphics&) override;
	void resized() override;
private:
	ScopedPointer<Drawable> midiIcon;
};

class MIDIVelocityInputNode : public Node {
public:
	MIDIVelocityInputNode();
	void process(int) override;
};

class MIDIVelocityInputNodeEditor : public NodeEditor {
public:
	MIDIVelocityInputNodeEditor(NodeGraphEditor* nge);
	void paint(Graphics&) override;
	void resized() override;
private:
	ScopedPointer<Drawable> midiIcon;
};

#endif
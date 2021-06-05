#ifndef NODE_GRAPH_PROCESSOR
#define NODE_GRAPH_PROCESSOR

#include "../Node.h"
#include <JuceHeader.h>
#include <vector>

using namespace juce;

class NodeGraphProcessor {
public:
	int currentMIDINote = -1;
	float currentMIDIVelocity = 0.0f;
	int maxSIMDBufferSize = 120;
	int sizeof_buffer;
public:
	NodeGraphProcessor();
	~NodeGraphProcessor();
	void addProcessor(Node* processor);
	void removeProcessor(Node* processor);
	void setBufferSize(int numSamples);
	void compile();
	void process(juce::AudioBuffer<float>& buffer, int numSamples);
private:
	std::vector<Node*> nodeProcessors;
	std::vector<Node*> processingQueue;
};

#endif
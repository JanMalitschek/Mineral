#ifndef NODE_GRAPH_PROCESSOR
#define NODE_GRAPH_PROCESSOR

#include "../Node.h"
#include <JuceHeader.h>
#include <vector>
#include "../OutputNode.h"

using namespace juce;

class NewProjectAudioProcessor;

class NodeGraphProcessor {
public:
	int currentMIDINote = 69;
	float currentMIDIVelocity = 0.0f;
	int maxSIMDBufferSize = 120;
	int sizeof_buffer;
	NewProjectAudioProcessor* pluginProcessor;
public:
	NodeGraphProcessor();
	~NodeGraphProcessor();
	void addProcessor(Node* processor);
	void removeProcessor(Node* processor);
	void setBufferSize(int numSamples);
	void compile();
	void recompile();
	void process(juce::AudioBuffer<float>& buffer, int numSamples);
	__forceinline bool hasOutput() const;
private:
	std::vector<Node*> nodeProcessors;
	std::vector<Node*> processingQueue;
	OutputNode* output = nullptr;
	bool needsRecompiling = false;
};

#endif
#include "NodeGraphProcessor.h"
#include "../../PluginProcessor.h"

NodeGraphProcessor::NodeGraphProcessor(){
	currentMIDINote = 69;
	currentMIDIVelocity = 0.0f;
	maxSIMDBufferSize = 120;
	sizeof_buffer = sizeof(SIMDFloat) * maxSIMDBufferSize;
	
	nodeProcessors = std::vector<Node*>();
	processingQueue = std::vector<Node*>();
	output = nullptr;
	needsRecompiling = false;
}
NodeGraphProcessor::~NodeGraphProcessor() {
	for (int i = 0; i < nodeProcessors.size(); i++)
		delete nodeProcessors[i];
	nodeProcessors.clear();
	processingQueue.clear();
}
void NodeGraphProcessor::addProcessor(Node* processor) {
	processor->ngp = this;
	processor->initBuffer(maxSIMDBufferSize);
	processor->ngp = this;
	nodeProcessors.push_back(processor);
	if (OutputNode* out = dynamic_cast<OutputNode*>(processor))
		output = out;
	recompile();
}
void NodeGraphProcessor::removeProcessor(Node* processor) {
	if (dynamic_cast<OutputNode*>(processor))
		output = nullptr;
	for(int i = 0; i < nodeProcessors.size(); i++)
		if (nodeProcessors[i] == processor) {
			nodeProcessors.erase(nodeProcessors.begin() + i);
			goto removed;
		}
	removed:
	recompile();
}
void NodeGraphProcessor::setBufferSize(int numSamples) {
	maxSIMDBufferSize = (int)ceil((float)numSamples / 4.0f);
	sizeof_buffer = sizeof(SIMDFloat) * maxSIMDBufferSize;
}
void NodeGraphProcessor::recompile() {
	needsRecompiling = true;
}
void NodeGraphProcessor::compile() { //Not super efficient but it does the job
	DBG("Compiling");
	processingQueue.clear();
	int leftOverNodes = nodeProcessors.size();
	while (leftOverNodes > 0) {
		for (int i = 0; i < nodeProcessors.size(); i++) {
			if (nodeProcessors[i]->isMarked())
				continue;
			int numConnectedInputs = 0, numMarkedInputs = 0;
			nodeProcessors[i]->getInputInfo(numConnectedInputs, numMarkedInputs);
			if (numConnectedInputs == 0 || numConnectedInputs == numMarkedInputs) {
				processingQueue.push_back(nodeProcessors[i]);
				nodeProcessors[i]->mark();
				leftOverNodes--;
			}
		}
	}
	for (int i = 0; i < nodeProcessors.size(); i++)
		nodeProcessors[i]->mark(false);
	DBG("Finished Compiling");
}
void NodeGraphProcessor::process(juce::AudioBuffer<float>& buffer, int numSamples) {
	if (needsRecompiling) {
		DBG("Recompile");
		compile();
		needsRecompiling = false;
	}
	//Unpack SIMD Buffer
	if (output) {
		for (int i = 0; i < processingQueue.size(); i++)
			processingQueue[i]->process(numSamples);
		for (int c = 0; c < buffer.getNumChannels(); c++) {
			float* writePtr = buffer.getWritePointer(c);
			for (int i = 0; i < numSamples; i += 4)
				for (int s = 0; s < 4 && i + s < numSamples; s++)
					writePtr[i + s] = output->buffer[i / 4].get(s);
		}
	}
	else {
		for (int c = 0; c < buffer.getNumChannels(); c++) {
			float* writePtr = buffer.getWritePointer(c);
			for (int i = 0; i < numSamples; i++)
				writePtr[i] = 0.0f;
		}
	}
}
bool NodeGraphProcessor::hasOutput() const {
	return output;
}
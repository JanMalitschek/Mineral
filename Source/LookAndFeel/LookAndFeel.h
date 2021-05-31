#ifndef LOOK_AND_FEEL
#define LOOK_AND_FEEL

#include "../JuceLibraryCode/JuceHeader.h"

using namespace juce;

class LookAndFeelMain : public LookAndFeel_V4 {
	Font boldFont = Font(Typeface::createSystemTypefaceFor(BinaryData::Bebas_ttf, (size_t)BinaryData::Bebas_ttfSize));

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override;
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override;
};

class LookAndFeelInputs : public LookAndFeel_V4 {
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override;
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override;
};
class LookAndFeelOutputs : public LookAndFeel_V4 {
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override;
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override;
};

class LookAndFeelHeader : public LookAndFeel_V4 {
	Font titleFont = Font(Typeface::createSystemTypefaceFor(BinaryData::Bahnschrift_ttf, (size_t)BinaryData::Bahnschrift_ttfSize));

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override;
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override;
};

#endif
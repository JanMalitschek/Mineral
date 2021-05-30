#ifndef LOOK_AND_FEEL
#define LOOK_AND_FEEL

#include "../JuceLibraryCode/JuceHeader.h"
#include "Colors.h"
using namespace juce;

class LookAndFeelMain : public LookAndFeel_V4 {
	Font boldFont = Font(Typeface::createSystemTypefaceFor(BinaryData::Bebas_ttf, (size_t)BinaryData::Bebas_ttfSize));

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override {
		float diameter = jmin(width, height);
		float radius = diameter / 2;
		float centerX = width / 2, centerY = height / 2;
		float valueRadius = radius - 2;
		float railRadius = radius - 6;
		float tickRadius = radius - 18;
		float labelRadius = radius - 22;
		float angleDifference = rotaryEndAngle - rotaryStartAngle;

		Path rail_arc;
		rail_arc.addCentredArc(centerX, centerY, railRadius, railRadius, 0.0f, -3.1415f, 3.1415f, true);
		Path value_arc;
		value_arc.addCentredArc(centerX, centerY, valueRadius, valueRadius, 0.0f, rotaryStartAngle, rotaryStartAngle + angleDifference * sliderPos, true);

		PathStrokeType stroke = PathStrokeType(4.0f, PathStrokeType::JointStyle::curved, PathStrokeType::EndCapStyle::butt);

		g.setColour(HEADER_COLOR);
		g.strokePath(rail_arc, stroke);
		g.setColour(MAIN_COLOR_1);
		g.strokePath(value_arc, stroke);

		Path tick;
		tick.addEllipse(-2.0f, -2.0f, 4.0f, 4.0f);
		g.setColour(HEADER_COLOR);
		g.strokePath(tick, stroke, AffineTransform::translation(0.0f, -tickRadius).rotated(rotaryStartAngle + angleDifference * sliderPos).translated(centerX, centerY));

		/*g.setFont(boldFont);
		g.drawFittedText(slider.getName(), centerX - labelRadius, centerY - labelRadius, labelRadius * 2.0f, labelRadius * 2.0f, Justification::centred, 2);*/
	}

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override {}
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) {
		Rectangle<int> bounds = button.getBounds();
		int width = bounds.getWidth(), height = bounds.getHeight();
		int centerX = width / 2, centerY = height / 2;

		g.setFont(boldFont);
		g.setFont(15.0f);
		if (isMouseOverButton) {
			g.setColour(BACKGROUND_COLOR.brighter(0.2f));
			if (isButtonDown)
				g.setColour(BACKGROUND_COLOR.brighter(0.4f));
		}
		else
			g.setColour(BACKGROUND_COLOR);
		g.drawText(button.getButtonText(), 0, 0, width, height, Justification::centred);
	}
};

class LookAndFeelInputs : public LookAndFeel_V4 {
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override {
		Rectangle<int> bounds = button.getBounds();
		int width = bounds.getWidth(), height = bounds.getHeight();
		int centerX = width / 2, centerY = height / 2;

		g.setColour(SOCKET_CENTER_COLOR);
		g.fillEllipse(centerX - 3, centerY - 3, 6, 6);

		if (isMouseOverButton) {
			g.setColour(MAIN_COLOR_1.brighter(0.2f));
			if (isButtonDown)
				g.setColour(MAIN_COLOR_1.brighter(0.4f));
		}
		else
			g.setColour(MAIN_COLOR_1);
		g.drawEllipse(centerX - 7, centerY - 7, 14, 14, 3);
		g.drawLine(0, centerY, centerX - 7, centerY, 3);
	}
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) {}
};
class LookAndFeelOuputs : public LookAndFeel_V4 {
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override {
		Rectangle<int> bounds = button.getBounds();
		int width = bounds.getWidth(), height = bounds.getHeight();
		int centerX = width / 2, centerY = height / 2;

		g.setColour(SOCKET_CENTER_COLOR);
		g.fillEllipse(centerX - 3, centerY - 3, 6, 6);

		if (isMouseOverButton) {
			g.setColour(MAIN_COLOR_1.brighter(0.2f));
			if (isButtonDown)
				g.setColour(MAIN_COLOR_1.brighter(0.4f));
		}
		else
			g.setColour(MAIN_COLOR_1);
		g.drawEllipse(centerX - 7, centerY - 7, 14, 14, 3);
		g.drawLine(centerX + 7, centerY, width, centerY, 3);
	}
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) {}
};

class LookAndFeelHeader : public LookAndFeel_V4 {
	Font titleFont = Font(Typeface::createSystemTypefaceFor(BinaryData::Bahnschrift_ttf, (size_t)BinaryData::Bahnschrift_ttfSize));

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColor, bool isMouseOverButton, bool isButtonDown) override {
		Rectangle<int> bounds = button.getBounds();
		int width = bounds.getWidth(), height = bounds.getHeight();

		if (isMouseOverButton) {
			g.setColour(HEADER_COLOR.darker(0.1f));
			if (isButtonDown)
				g.setColour(HEADER_COLOR.darker(0.2f));
		}
		else
			g.setColour(HEADER_COLOR);
		Path header;
		header.addRoundedRectangle(0, 0, width, height, 5, 5, true, true, false, false);
		g.fillPath(header);

		g.setColour(SHADOW);
		g.fillRect(0, height - 2, width, 2);
	}
	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) {
		Rectangle<int> bounds = button.getBounds();
		int width = bounds.getWidth(), height = bounds.getHeight();

		g.setColour(MAIN_COLOR_1);
		g.setFont(titleFont);
		g.setFont(15);
		g.drawText(button.getButtonText(), 3, 0, width - 6, height, Justification::centredLeft, false);
	}
};

#endif
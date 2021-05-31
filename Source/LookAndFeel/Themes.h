#ifndef THEMES
#define THEMES

#include <JuceHeader.h>
#include <vector>

using namespace juce;

struct Theme {
	static Theme* current;
	static std::vector<Theme*> themes;
	String name;

	Colour backgroundColor;
	Colour nodeBackgroundColor;
	Colour socketCenterColor;
	Colour headerColor;

	Colour mainColor1;
	Colour mainColor2;
	Colour mainColor3;

	const Colour shadowColor = Colour(0.0f, 0.0f, 0.0f, 0.2f);
	const Colour highlightColor = Colour(0.0f, 0.0f, 1.0f, 0.2f);
	const Colour clearColor = Colour(0.0f, 0.0f, 0.0f, 0.0f);

	Theme();
	Theme(String name);

	static void createStandardThemes();
	static void deleteThemes();
	static void setTheme(String name);
	static std::vector<String> getThemeNames();
	static Colour getRandomMainColor();
	
};

#endif
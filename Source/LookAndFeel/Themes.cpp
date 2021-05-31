#include "Themes.h"

Theme* Theme::current = nullptr;
std::vector<Theme*> Theme::themes;

Theme::Theme() { name = "New Theme"; }
Theme::Theme(String name) { this->name = name; }

void Theme::createStandardThemes() {
	Theme* darkTheme = new Theme("Dark (Default)");
	darkTheme->backgroundColor = Colour(34, 34, 34);
	darkTheme->nodeBackgroundColor = Colour(51, 51, 51);
	darkTheme->socketCenterColor = Colour(128, 128, 128);
	darkTheme->headerColor = Colour(253, 253, 251);
	darkTheme->mainColor1 = Colour(71, 159, 172);
	darkTheme->mainColor2 = Colour(221, 54, 14);
	darkTheme->mainColor3 = Colour(255, 189, 0);
	themes.push_back(darkTheme);

	setTheme("Dark (Default)");
}
void Theme::deleteThemes() {
	current = nullptr;
	delete current;
	for (int i = 0; i < themes.size(); i++)
		delete themes[i];
	themes.clear();
}
void Theme::setTheme(String name) {
	for (int i = 0; i < themes.size(); i++)
		if (themes[i]->name == name)
			current = themes[0];
}
std::vector<String> Theme::getThemeNames() {
	std::vector<String> themeNames;
	for (int i = 0; i < themes.size(); i++)
		themeNames.push_back(themes[i]->name);
	return themeNames;
}
Colour Theme::getRandomMainColor() {
	int choice = rand() % 3;
	switch (choice) {
	case 0: return current->mainColor1;
	case 1: return current->mainColor2;
	case 2: return current->mainColor3;
	}
}
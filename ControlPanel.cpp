#include "ControlPanel.h"
#include <algorithm>
#include <cctype>
#include <cassert>

ControlPanel::ControlPanel() {
	_buttonPanel.resize(BUTTONFLOOR);
	for (unsigned short i = 1; i <= BUTTONFLOOR; ++i) {
		_buttonPanel[i - 1] = { false, std::to_string(i) };
	}

	_buttonPanel.emplace_back(false, "D");
	_buttonPanel.emplace_back(false, "O");
	_buttonPanel.emplace_back(false, "C");
	_button = Button::NOTHING;
}

ControlPanel::~ControlPanel() = default;

void ControlPanel::setButtonState(Button button) {
	_button = button;
}

Button ControlPanel::getButton() const {
	return _button;
}

const std::vector < std::pair<bool, std::string>>& ControlPanel::getButtons() const {
	return _buttonPanel;
}

bool ControlPanel::pressButton(const std::string& button) {
	unsigned short nbutton = getButtonIndex(button);
	assert(nbutton < MAXBUTTON);
	_buttonPanel[nbutton].first = true;
	return true;
}

void ControlPanel::unpressButton(unsigned short button) {
	assert(button < MAXBUTTON);
	_buttonPanel[button].first = false;
}

bool ControlPanel::isButtonPressed(unsigned short button) const {
	assert(button < MAXBUTTON);
	return _buttonPanel[button].first;
}

unsigned short ControlPanel::getButtonIndex(const std::string& button) {
	if (std::isdigit(button[0])) {
		unsigned short index = std::stoi(button);
		assert(index >= 1 && index <= BUTTONFLOOR);
		return index - 1;
	}
	else if (button == "D") return DISPETCHER;
	else if (button == "O") return OPEN;
	else if (button == "C") return CLOSE;
	else throw std::invalid_argument("Invalid button");
}
#include "ControlPanel.h"
#include <algorithm>
#include <cctype>

ControlPanel::ControlPanel() {
    // Initialize floor buttons
    _buttonPanel.resize(BUTTONFLOOR);
    for (unsigned short i = 1; i <= BUTTONFLOOR; ++i) {
        _buttonPanel[i - 1] = std::make_pair(false, std::to_string(i));
    }


    _buttonPanel.push_back(std::make_pair(false, "D")); // Dispatcher
    _buttonPanel.push_back(std::make_pair(false, "O")); // Open
    _buttonPanel.push_back(std::make_pair(false, "C")); // Close
}

ControlPanel::~ControlPanel() {
    _buttonPanel.clear();
}

const std::vector<std::pair<bool, std::string>>& ControlPanel::getButtons() const {
    return _buttonPanel;
}

bool ControlPanel::pressButton(const std::string& button) {
    unsigned short nbutton = getButtonIndex(button);
    if (nbutton >= MAXBUTTON) throw std::out_of_range("Invalid button");
    _buttonPanel[nbutton].first = true;  
    return true;
}

void ControlPanel::unpressButton(unsigned short button) {
    if (button >= MAXBUTTON) throw std::out_of_range("Invalid button");
    _buttonPanel[button].first = false;
}

bool ControlPanel::isButtonPressed(unsigned short button) const {
    if (button >= MAXBUTTON) throw std::out_of_range("Invalid button");
    return _buttonPanel[button].first;
}

unsigned short ControlPanel::getButtonIndex(const std::string& button) {
    if (std::isdigit(button[0])) {
        unsigned short index = std::stoi(button);
        if (index < 1 || index > BUTTONFLOOR) throw std::out_of_range("Invalid floor button");
        return index - 1;
    }
    else if (button == "D") return DISPETCHER;
    else if (button == "O") return OPEN;
    else if (button == "C") return CLOSE;
    else throw std::invalid_argument("Invalid button");
}

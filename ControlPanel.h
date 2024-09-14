#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#define BUTTONFLOOR 20
#define BUTTONSERVICE 3
#define MAXBUTTON (BUTTONFLOOR + BUTTONSERVICE)

#include <vector>
#include <string>
#include <stdexcept>

enum Button {
    NUMBER = 0,
    DISPETCHER = BUTTONFLOOR, 
    CLOSE,
    OPEN
};

class ControlPanel {
private:
    std::vector<std::pair<bool, std::string>> _buttonPanel;
protected:
    ControlPanel();
    ~ControlPanel();

    bool isButtonPressed(unsigned short button) const; // Check if a button is pressed
    static unsigned short getButtonIndex(const std::string& button);
public:
    bool pressButton(const std::string& button);   // Press any button
    void unpressButton(unsigned short button);     // Unpress a button after action
    const std::vector<std::pair<bool, std::string>>& getButtons() const;
};

#endif // CONTROLPANEL_H

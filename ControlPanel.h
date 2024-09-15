#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#define BUTTONFLOOR 20  // Number of floor buttons (from 1 to 20)
#define BUTTONSERVICE 3  // Number of service buttons (Dispatcher, Close Door, Open Door)
#define MAXBUTTON (BUTTONFLOOR + BUTTONSERVICE)  // Total number of buttons

#include <vector>
#include <string>
#include <stdexcept>

// Enum representing different buttons available in the control panel
enum Button {
    NUMBER = 0,                    // Floor buttons (1 to 20)
    DISPETCHER = BUTTONFLOOR,       // Dispatcher button
    CLOSE,                          // Close door button
    OPEN,                           // Open door button
    NOTHING                         // No button pressed
};

class ControlPanel {
private:
    std::vector<std::pair<bool, std::string>> _buttonPanel; // Stores the state of each button (pressed or not) and its label
    Button _button;                                         // The currently pressed button (if any)

protected:
    // Constructor initializes the control panel and sets up all buttons
    ControlPanel();

    // Destructor for clean-up (if needed)
    ~ControlPanel();

    // Set the current button state (pressed or not pressed)
    void setButtonState(Button button);

    // Get the current button being pressed
    Button getButton() const;

    // Check if a specific button is pressed based on its index
    bool isButtonPressed(unsigned short button) const;

    // Get the index of the button in the panel based on the button's label (e.g., "1", "OPEN")
    static unsigned short getButtonIndex(const std::string& button);

public:
    // Press a button by providing its label (e.g., "5", "DISPETCHER", "OPEN")
    bool pressButton(const std::string& button);

    // Unpress the button after its action is performed
    void unpressButton(unsigned short button);

    // Get the entire list of buttons and their states
    const std::vector<std::pair<bool, std::string>>& getButtons() const;
};

#endif // CONTROLPANEL_H
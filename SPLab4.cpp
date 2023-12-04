#include <iostream>
#include <string>

using namespace std;

class Window {
protected:
    static int nextId;
    int id;
    int height;
    int width;
    int memoryNeeded;
    bool areAdministratorRightsGranted;
    bool isShown;

public:
    Window(int windowHeight, int windowWidth, bool adminRights)
        : id(++nextId), height(windowHeight), width(windowWidth),
        areAdministratorRightsGranted(adminRights), isShown(false),
        memoryNeeded(windowHeight* windowWidth) {}

    // Метод для изменения значения memoryNeeded
    void doWork() {
        cout << "Window " << id << " is changing needed memory value." << endl;
        memoryNeeded += 100;
        cout << "Value of needed memory is now " << memoryNeeded << "." << endl;
    }

    // Метод для отображения или скрытия окна
    void showOrHide() {
        isShown = !isShown;
        std::cout << "Window " << id << " is " << (isShown ? "shown." : "hidden.") << std::endl;
    }
};

class Settings {
public:
    Settings(int maxFPS, string colorTheme, int brightness, bool fullscreen, double volume)
        : maxFPS(maxFPS), colorTheme(colorTheme), brightness(brightness), 
        fullscreen(fullscreen), volume(volume) {}

    int getMaxFPS() const { return maxFPS; }
    string getColorTheme() const { return colorTheme; }
    int getBrightness() const { return brightness; }
    bool isFullscreen() const { return fullscreen; }
    double getVolume() const { return volume; }

    void setMaxFPS(int newMaxFPS) { maxFPS = newMaxFPS; }
    void setColorTheme(const string& newColorTheme) { colorTheme = newColorTheme; }
    void setBrightness(int newBrightness) { brightness = newBrightness; }
    void setFullscreen(bool newFullscreen) { fullscreen = newFullscreen; }
    void setVolume(double newVolume) { volume = newVolume; }

private:
    int maxFPS;
    string colorTheme;
    int brightness;
    bool fullscreen;
    double volume;
};

//Добавляет к окну настройки и абстрактный метод, который будет определен в потомках.
class GameWindow : public Window {
protected:
    Settings settings;

public:
    GameWindow(int windowHeight, int windowWidth, bool adminRights, const Settings& windowSettings)
        : Window(windowHeight, windowWidth, adminRights), settings(windowSettings) {}

    const Settings& getSettings() const { return settings; }

    // Абстрактный метод
    virtual void doAction() = 0;

    //ЗАЩИТА
    //Добавляем метод для вывода информации, который дополним в классах-наследниках
    virtual void displaySettings() {
        cout << "Welcome! Believe it or not, you are playing a game!" << endl;
        cout << "Current Settings:" << endl;
        cout << "Max FPS: " << settings.getMaxFPS() << endl;
        cout << "Color Theme: " << settings.getColorTheme() << endl;
        cout << "Brightness: " << settings.getBrightness() << endl;
        cout << "Fullscreen: " << (settings.isFullscreen() ? "Yes" : "No") << endl;
        cout << "Volume: " << settings.getVolume() << endl;
    }

    virtual void changeSettings() {
        int choice;
        do {
            cout << "\nChange Settings:\n";
            cout << "1. Max FPS\n";
            cout << "2. Color Theme\n";
            cout << "3. Brightness\n";
            cout << "4. Fullscreen\n";
            cout << "5. Volume\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            string newColorTheme;
            switch (choice) {
            case 1:
                cout << "Enter new Max FPS: ";
                int newMaxFPS;
                cin >> newMaxFPS;
                settings.setMaxFPS(newMaxFPS);
                break;
            case 2:
                cout << "Enter new Color Theme: ";
                cin.ignore();
                getline(cin, newColorTheme);
                settings.setColorTheme(newColorTheme);
                break;
            case 3:
                cout << "Enter new Brightness: ";
                int newBrightness;
                cin >> newBrightness;
                settings.setBrightness(newBrightness);
                break;
            case 4:
                cout << "Enter new Fullscreen (1 for true, 0 for false): ";
                bool newFullscreen;
                cin >> newFullscreen;
                settings.setFullscreen(newFullscreen);
                break;
            case 5:
                cout << "Enter new Volume: ";
                double newVolume;
                cin >> newVolume;
                settings.setVolume(newVolume);
                break;
            case 6:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }
};

//Настройки для окна камень-ножницы-бумага. Добавляются две дополнительные настройки.
class RockPaperScissorsSettings : public Settings {
public:
    RockPaperScissorsSettings(int maxFPS, string colorTheme, int brightness,
        bool fullscreen, double volume, bool isClassic, int maxNumOfRounds)
        : Settings(maxFPS, colorTheme, brightness, fullscreen, volume), classicRockPaperScissors(isClassic),
        maxNumOfRounds(maxNumOfRounds) {}

    // Дополнительные настройки
    bool classicRockPaperScissors;
    int maxNumOfRounds;
};

//Окно камень-ножницы-бумага. Переопределяется метод doAction() для изменения значения memoryNeeded,
//в т.ч. используя настройки, уникальные для данного класса.
class RockPaperScissorsGameWindow : public GameWindow {
public:
    RockPaperScissorsGameWindow(int windowHeight, int windowWidth,
        bool adminRights, const RockPaperScissorsSettings& windowSettings)
        : GameWindow(windowHeight, windowWidth, adminRights, windowSettings), gameSettings(windowSettings) {}

    RockPaperScissorsSettings gameSettings;

    // Переопределение абстрактного метода
    void doAction() override {
        cout << "RockPaperScissorsGameWindow is working." << endl;
        GameWindow::doWork();
        // Использование дополнительных настроек для вычисления memoryNeeded
        if (!gameSettings.classicRockPaperScissors) {
            cout << "Because you are playing a non-vanilla rock-paper-scissors, memory usage increases (+200)." << endl;
            memoryNeeded += 200;
        }
    }

    void displaySettings() override {
        GameWindow::displaySettings();
        cout << "Classic Rock-Paper-Scissors: " << (gameSettings.classicRockPaperScissors ? "Yes" : "No") << endl;
        cout << "Max Number of Rounds: " << gameSettings.maxNumOfRounds << endl;
    }

    void changeSettings() override {
        int choice;
        do {
            cout << "\nChange RockPaperScissors Game Settings:\n";
            cout << "1. Classic Rock-Paper-Scissors\n";
            cout << "2. Max Number of Rounds\n";
            cout << "3. Go to base settings\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter new value for Classic Rock-Paper-Scissors (1 for true, 0 for false): ";
                bool newClassicRockPaperScissors;
                cin >> newClassicRockPaperScissors;
                gameSettings.classicRockPaperScissors = newClassicRockPaperScissors;
                break;
            case 2:
                cout << "Enter new value for Max Number of Rounds: ";
                int newMaxNumOfRounds;
                cin >> newMaxNumOfRounds;
                gameSettings.maxNumOfRounds = newMaxNumOfRounds;
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);

        //Добавить базовые настройки к имплементации специфических настроек
        GameWindow::changeSettings();
    }
};

// Второй класс-наследник класса Settings.
class ChessSettings : public Settings {
public:
    ChessSettings(int maxFPS, string colorTheme, int brightness,
        bool fullscreen, double volume, int maxTime)
        : Settings(maxFPS, colorTheme, brightness, fullscreen, volume), timeForOneGameInSec(maxTime) {}

    // Доп. настройка
    int timeForOneGameInSec;
};

// Второй класс-наследник для GameWindow
class ChessGameWindow : public GameWindow {
public:
    ChessGameWindow(int windowHeight, int windowWidth,
        bool adminRights, const ChessSettings& windowSettings)
        : GameWindow(windowHeight, windowWidth, adminRights, windowSettings), chessSettings(windowSettings) {}

    ChessSettings chessSettings;

    void doAction() override {
        cout << "ChessGameWindow is working." << endl;
        GameWindow::doWork();
        memoryNeeded += chessSettings.timeForOneGameInSec * 10;
    }

    void displaySettings() override {
        GameWindow::displaySettings();
        cout << "Amount of time for one game: " << chessSettings.timeForOneGameInSec << endl;
    }

    void changeSettings() override {
        int choice;
        do {
            cout << "\nChange Chess Game Settings:\n";
            cout << "1. Time for One Game (in seconds)\n";
            cout << "2. Go to base settings\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter new value for Time for One Game (in seconds): ";
                int newTimeForOneGame;
                cin >> newTimeForOneGame;
                chessSettings.timeForOneGameInSec = newTimeForOneGame;
                break;
            case 2:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 2);

        GameWindow::changeSettings();
    }
};

//Третий класс для Settings по аналогии... 
class RPGSettings : public Settings {
public:
    RPGSettings(int maxFPS, string colorTheme, int brightness,
        bool fullscreen, double volume, int maxAmountOfPlayers)
        : Settings(maxFPS, colorTheme, brightness, fullscreen, volume), maxPlayers(maxAmountOfPlayers) {}

    int maxPlayers;
};

//Третий класс для GameWindow
class RPGGameWindow : public GameWindow {
public:
    RPGGameWindow(int windowHeight, int windowWidth,
        bool adminRights, const RPGSettings& windowSettings)
        : GameWindow(windowHeight, windowWidth, adminRights, windowSettings), rpgGameSettings(windowSettings) {}

    RPGSettings rpgGameSettings;

    void doAction() override {
        cout << "RPGGameWindow is working." << endl;
        GameWindow::doWork();
        if (rpgGameSettings.maxPlayers > 4) {
            memoryNeeded += 500;
        }
    }

    void displaySettings() override {
        GameWindow::displaySettings();
        cout << "Max amount of players: " << rpgGameSettings.maxPlayers << endl;
    }

    void changeSettings() override {
        int choice;
        do {
            cout << "\nChange RPG Game Settings:\n";
            cout << "1. Max Players\n";
            cout << "2. Go to base settings\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter new value for Max Players: ";
                int newMaxPlayers;
                cin >> newMaxPlayers;
                rpgGameSettings.maxPlayers = newMaxPlayers;
                break;
            case 2:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 2);

        GameWindow::changeSettings();
    }
};

//Для защиты

//Четвертный класс, который наследуется от одного из ранее созданных классов-наследников,
//в котором определяется дополнительный параметр
class MMORPGSettings : public RPGSettings {
public:
    MMORPGSettings(int maxFPS, string colorTheme, int brightness,
        bool fullscreen, double volume, int maxAmountOfPlayers, bool isOpenWorld)
        : RPGSettings(maxFPS, colorTheme, brightness, fullscreen, volume, maxAmountOfPlayers), openWorld(isOpenWorld) {}

    bool openWorld;
};

//Класс-внук (GameWindow приходится ему бабушкой)
class MMORPGGameWindow : public RPGGameWindow {
public:
    MMORPGGameWindow(int windowHeight, int windowWidth,
        bool adminRights, const MMORPGSettings& windowSettings)
        : RPGGameWindow(windowHeight, windowWidth, adminRights, windowSettings), mmorpgGameSettings(windowSettings) {}

    MMORPGSettings mmorpgGameSettings;

    void doAction() override {
        cout << "MMORPGGameWindow is working." << endl;
        GameWindow::doWork();
        if (mmorpgGameSettings.openWorld) {
            memoryNeeded += 2000;
        }
    }

    void displaySettings() override {
        RPGGameWindow::displaySettings();
        cout << "Open World: " << (mmorpgGameSettings.openWorld ? "Yes" : "No") << endl;
    }

    void changeSettings() override {
        int choice;
        do {
            cout << "\nChange MMORPG Game Settings:\n";
            cout << "1. Max Players\n";
            cout << "2. Open World\n";
            cout << "3. Go to base settings\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter new value for Max Players: ";
                int newMaxPlayers;
                cin >> newMaxPlayers;
                mmorpgGameSettings.maxPlayers = newMaxPlayers;
                break;
            case 2:
                cout << "Enter new value for Open World (1 for true, 0 for false): ";
                bool newOpenWorld;
                cin >> newOpenWorld;
                mmorpgGameSettings.openWorld = newOpenWorld;
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 3);

        GameWindow::changeSettings();
    }
};

int Window::nextId = 0;



void displayMenu(GameWindow* window) {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display current settings\n";
        cout << "2. Change settings\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            window->displaySettings();
            break;
        case 2:
            window->changeSettings();
            break;
        case 3:
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

int main() {
    RockPaperScissorsSettings rpsSettings(60, "Classic", 50, true, 0.8, true, 5);
    RockPaperScissorsGameWindow rpsWindow(800, 600, true, rpsSettings);

    ChessSettings chessSettings(30, "Wooden", 70, false, 0.6, 32);
    ChessGameWindow chessWindow(1024, 768, false, chessSettings);

    RPGSettings rpgSettings(120, "Dark", 80, true, 0.9, 16);
    RPGGameWindow rpgWindow(1920, 1080, true, rpgSettings);

    MMORPGSettings mmorpgSettings(120, "Fantasy", 90, true, 0.9, 32, true);
    MMORPGGameWindow mmorpgWindow(1920, 1080, true, mmorpgSettings);

    int gameChoice;
    do {
        cout << "\nChoose a game window to configure:\n";
        cout << "1. RockPaperScissorsGameWindow\n";
        cout << "2. ChessGameWindow\n";
        cout << "3. RPGGameWindow\n";
        cout << "4. MMORPGGameWindow\n";
        cout << "5. Run 3 derived classes\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> gameChoice;

        GameWindow* selectedWindow = nullptr;

        switch (gameChoice) {
        case 1:
            selectedWindow = &rpsWindow;
            break;
        case 2:
            selectedWindow = &chessWindow;
            break;
        case 3:
            selectedWindow = &rpgWindow;
            break;
        case 4:
            selectedWindow = &mmorpgWindow;
            break;
        case 5: 
            rpsWindow.doAction();
            chessWindow.doAction();
            rpgWindow.doAction();
            break;
        case 6:
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        if (selectedWindow != nullptr) {
            displayMenu(selectedWindow);
        }

    } while (gameChoice != 6);

    return 0;
}

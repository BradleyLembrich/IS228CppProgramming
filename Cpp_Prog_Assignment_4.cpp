// Inheritance game assignment
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<thread>
using namespace std;


class Mode {
public:
    std::vector <int> sequence;
    //std::string userInput;
    //std::string clearCommand;
    int pauseTime;
    int maxNum;
    //int sequenceLength = 1;
    int wins = 0;

    // Constructor
    Mode(int m, int p){
        maxNum = m;
        pauseTime = p;
        // Seed random number generator
        srand(time(0));
    }

    // Virtual function to be overridden
    virtual void play() = 0;

    // Clear screen based on OS
    void clearScreen(){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void generateSequence(){
            sequence.push_back(rand() % maxNum);
    }

    void displaySequence(){
        clearScreen();
        for (int i = 0; i < sequence.size(); i++) {
            cout << sequence[i] << std::flush;;
            std::this_thread::sleep_for(std::chrono::milliseconds(pauseTime));
            clearScreen();
            cout << "" << std::flush;;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            clearScreen();
        }
    }

    std::string getUserInput() {
        std::string userInput;
        cout << "Type the sequence and press Enter: ";
        cin >> userInput;
        return userInput;
    }

    bool checkUserInput(std::string userInput){
        std::string generatedSequence;
        // Create string from sequence vector
        for (int i = 0; i < sequence.size(); i++){
            generatedSequence.append(std::to_string(sequence[i]));
        }
        // Compare strings
        return userInput == generatedSequence;
    }
};

class EasyMode : public Mode {
public: 

    EasyMode() : Mode(4,1000){}

    void play() {
        cout << "Get ready..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        while (true) {
            generateSequence();
            displaySequence();
            std::string userInput = getUserInput();
            if (!checkUserInput(userInput)){
                break;
            }
            wins++;
        }
        cout << "Game over. Final score: " << wins;
    }
};

class HardMode : Mode {
public: 

HardMode() : Mode(9,500){}

    void play() {
        cout << "Get ready..." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        while (true) {
            generateSequence();
            displaySequence();
            std::string userInput = getUserInput();
            if (!checkUserInput(userInput)){
                break;
            }
            wins++;
        }
        cout << "Game over. Final score: " << wins;
    }
};


int main() {

    int selection; 
    cout << "Welcom to Simon. Select a game mode: " << endl << "1. Easy" 
    << endl << "2. Hard "<< endl << "3. Extreme" << endl;
    cin >> selection;
   
    switch(selection) {
    case 1: {
        EasyMode easyGame;
        easyGame.play();
        break;
    }
    case 2: {
        HardMode hardGame;
        hardGame.play();
        break;
    }
    case 3:
        cout << "Hard mode not yet implemented";
        break;
    default: 
        cout << "Invalid selection";
        return 0;
   }

   return 0;
}


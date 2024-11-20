#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
class Wordle {
private:
    T secretWord;
    int maxAttempts;
    int currentAttempt;

public:
    Wordle(T word, int attempts) : secretWord(word), maxAttempts(attempts), currentAttempt(0) {}

    void play() {
        // Display instructions
        cout << "Welcome to Wordle!\n";
        cout << "Guess the 5-letter secret word within " << maxAttempts << " attempts.\n";
        cout << "Feedback Guide:\n";
        cout << " - Correct letter in the correct position: Letter displayed as-is.\n";
        cout << " - Correct letter in the wrong position: Displayed as '?'.\n";
        cout << " - Incorrect letter: Displayed as '_'.\n";
        cout << "Note: Your input will be treated as uppercase.\n";
        cout << "Let's begin!\n\n";

        while (currentAttempt < maxAttempts) {
            currentAttempt++;
            string guess;
            cout << "Attempt " << currentAttempt << "/" << maxAttempts << ": Enter your guess: ";
            cin >> guess;

            // Convert guess to uppercase
            transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

            if (guess.length() != secretWord.length()) {
                try {
                    throw invalid_argument("Guess length must match the secret word length.");
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                    currentAttempt--; // Allow retry for invalid input
                    continue;
                }
            }

            if (guess == secretWord) {
                cout << "Congratulations! You guessed the word!\n";
                return;
            } else {
                cout << "Feedback: ";
                for (size_t i = 0; i < secretWord.length(); i++) {
                    if (guess[i] == secretWord[i])
                        cout << guess[i]; // Correct position
                    else if (secretWord.find(guess[i]) != string::npos)
                        cout << '?'; // Correct letter, wrong position
                    else
                        cout << '_'; // Incorrect letter
                }
                cout << "\n";
            }
        }
        cout << "Game Over! The secret word was: " << secretWord << "\n";
    }
};

int main() {
    string secret = "APPLE";
    int attempts = 5;

    Wordle<string> game(secret, attempts);
    game.play();

    return 0;
}


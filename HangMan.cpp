#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void setcursor(bool visible, DWORD size);
void drawIntroduction();
char menu();
void aboutUs();
void instruction();
char mode(string category);
string category();
void startGame();
string getRandomWord(const string &fileName);
void displayGameState(const string &displayWord, int tries);
char getGuess();
void updateDisplayWord(const string &word, string &displayWord, char guess);
void displayGameResult(const string &word, const string &displayWord);

int main()
{
    setcursor(0, 0);
    drawIntroduction();
    char dummy = getch();
    do
    {
        system("cls");
        char choice;
        choice = menu();
        switch (choice)
        {
        case '1':
            system("cls");
            startGame();
            break;
        case '2':
            system("cls");
            instruction();
            break;
        case '3':
            system("cls");
            aboutUs();
            break;
        case '4':
            system("cls");
            exit(0);
            break;
        default:
            do
            {
                system("cls");
                choice = menu();
            } while (choice != '1' && choice != '2' && choice != '3' && choice != '4');
            break;
        }
    } while (1);

    return 0;
}

void setcursor(bool visible, DWORD size)
{
    if (size == 0)
        size = 50;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawIntroduction()
{
    cout << "\n*****************************" << endl;
    cout << "*  WELCOME TO HANGMAN GAME  *" << endl;
    cout << "*****************************" << endl;
    cout << endl;
    cout << "_______________" << endl;
    cout << "| /      |     " << endl;
    cout << "|/       O     " << endl;
    cout << "|       /|\\   " << "  Press any key to continue" << endl;
    cout << "|       / \\   " << endl;
    cout << "|              " << endl;
    cout << "|              " << endl;
    cout << "|______________" << endl;
}

char menu()
{
    char choice;
    cout << "********************" << endl;
    cout << "******* MENU *******" << endl;
    cout << "********************" << endl;
    cout << endl;
    cout << "     1. START GAME " << endl;
    cout << "     2. INSTRUCTION " << endl;
    cout << "     3. ABOUT US " << endl;
    cout << "     4. QUIT GAME " << endl;
    cout << endl;
    cout << "Choose Option: ";

    choice = getch();

    return choice;
}

void startGame()
{
    string chosenCategory = category();
    char chosenMode = mode(chosenCategory);

    int tries;
    if (chosenMode == '1')
        tries = 15;
    else if (chosenMode == '2')
        tries = 12;
    else if (chosenMode == '3')
        tries = 8;
    else if (chosenMode == '4')
        tries = 5;

    string word = getRandomWord(chosenCategory);
    string displayWord(word.length(), '_');

    while (tries > 0 && displayWord != word)
    {
        displayGameState(displayWord, tries);
        char guess = getGuess();
        updateDisplayWord(word, displayWord, guess);

        if (word.find(guess) == string::npos)
        {
            tries--;
        }
    }

    displayGameResult(word, displayWord);
}

char mode(string category)
{
    char difficulty;
    cout << " CHOOSE GAME MODE - " << category << "\n"
         << endl;
    cout << " 1. Easy - 15 Tries. " << endl;
    cout << " 2. Medium - 12 Tries. " << endl;
    cout << " 3. Hard - 8 Tries. " << endl;
    cout << " 4. Insane - 5 Tries. " << endl;
    cout << "Choose Option: ";
    difficulty = getch();
    return difficulty;
}

string category()
{
    char category;
    string fileName;

    cout << "CHOOSE CATEGORY OF WORDS \n"
         << endl;
    cout << " 1. Animals     2. Food       3. Jobs      4. Countries  5. Body\n";
    cout << " 6. Stationery  7. Colors     8. Numbers   9. Computer   a. Sports\n";
    cout << " b. Cars        c. Subjects   d. Clothes   e. Home       f. Transport\n";
    category = getch();

    switch (category)
    {
    case '1':
        fileName = "animals.txt";
        break;
    case '2':
        fileName = "food.txt";
        break;
    case '3':
        fileName = "jobs.txt";
        break;
    case '4':
        fileName = "countries.txt";
        break;
    case '5':
        fileName = "body.txt";
        break;
    case '6':
        fileName = "stationery.txt";
        break;
    case '7':
        fileName = "colors.txt";
        break;
    case '8':
        fileName = "numbers.txt";
        break;
    case '9':
        fileName = "computer.txt";
        break;
    case 'a':
        fileName = "sports.txt";
        break;
    case 'b':
        fileName = "cars.txt";
        break;
    case 'c':
        fileName = "subjects.txt";
        break;
    case 'd':
        fileName = "clothes.txt";
        break;
    case 'e':
        fileName = "home.txt";
        break;
    case 'f':
        fileName = "transport.txt";
        break;
    }

    return fileName;
}

string getRandomWord(const string &fileName)
{
    ifstream file(fileName);
    vector<string> words;

    if (file.is_open())
    {
        string word;
        while (getline(file, word))
        {
            words.push_back(word);
        }
        file.close();
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, words.size() - 1);

    return words[dis(gen)];
}

void displayGameState(const string &displayWord, int tries)
{
    system("cls");
    cout << "Current Word: " << displayWord << endl;
    cout << "Tries left: " << tries << endl;
}

char getGuess()
{
    char guess;
    cout << "Enter a guess: ";
    cin >> guess;
    return guess;
}

void updateDisplayWord(const string &word, string &displayWord, char guess)
{
    for (size_t i = 0; i < word.length(); ++i)
    {
        if (word[i] == guess)
        {
            displayWord[i] = guess;
        }
    }
}

void displayGameResult(const string &word, const string &displayWord)
{
    system("cls");
    cout << "The word was: " << word << endl;
    if (displayWord == word)
    {
        cout << "Congratulations! You won!" << endl;
    }
    else
    {
        cout << "Sorry! You lost. Better luck next time!" << endl;
    }

    cout << "Press any key to go back to MENU" << endl;
    getch();
    system("cls");
}
void instruction()
{
    cout << "      INSTRUCTIONS  " << endl << endl;
    cout << " WELCOME TO HANGMAN. TO CONTINUE PLAYING CHOOSE FIRST OPTION IN MENU" << endl;
    cout << "THEN CHOOSE WHICH CATEGORY WORDS DO YOU WANT TO PLAY WITH (PRESS AN APPROPRIATE KEY)" << endl;
    cout << "AFTER STARTING TO PLAY, YOU HAVE TO GUESS THE LETTERS BY CHANCE AND SOME LUCK TO" << endl;
    cout << "FILL THE EMPTY SPACE, EACH TIME YOU CHOOSE WRONG LETTER HANGMAN WILL HAVE LESS CHANCE" << endl;
    cout << "OF SURVIVING, AS WELL AS YOU LOSS CHANCES. BY CHOOSING EASY, MEDIUM, HARD OR INSANE" << endl;
    cout << "MODES ACCORDINGLY YOU WILL HAVE 15, 12, 8 AND 5 CHANCES RESPECTIVELY. " << endl;
    cout << "   IF YOU EXCEED THE ALLOWED CHANCES, THE HANGMAN WILL BE COMPLETE, AND YOU LOSE." << endl;
    cout << "   MAKE YOUR GUESSES WISELY! GOOD LUCK!" << endl << endl;
    cout << "Press any key to go back to MENU\n" << endl;

    getch(); system("cls"); 
}
void aboutUs()
{
    cout << "     ABOUT DEVELOPERS " << endl << endl;
    cout << " This game was developed and released by: Giorgi Chkhikvadze." << endl;
    cout << "\nDon't U know how To contact me? Got U,\n here is an email adress:  cpmgeoo@gmail.com \n " << endl;
    cout << "Press any key to go back to MENU\n" << endl;

    getch(); system("cls");
}
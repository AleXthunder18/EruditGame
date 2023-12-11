#include <iostream>
#include <ctime>
#include <fstream>
#include <set>

using namespace std;
int readNum(int min, int max)
{
    bool isIncorrect;
    int num;

    do
    {
        isIncorrect = true;
        cin >> num;
        if (cin.fail() || (cin.get() != '\n'))
        {
            cout << "Некорректный ввод! Введите значение еще раз:" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        else
        {
            if (num < min || num > max)
            {
                cout << "Недопустимое значение! Введите значение еще раз:" << endl;
            }
            else
            {
                isIncorrect = false;
            }
        }
    }
    while (isIncorrect);

    return num;
}
set<string> createPossibleVocabulary() {

    set<string> vocabulary = {};
    string path = "C:\\Users\\Рустамчик\\Desktop\\опишка\\input.txt";
    string word = "";

    ifstream fin(path);
    if (!fin.is_open()) {
        printf("Какая-то ошибка с файлом.");
    }
    else {
        while (fin >> word) {
            vocabulary.insert({ word });
        }
    }
    fin.close();

    return vocabulary;

}
string getLetterBank()
{
    string letterBank = "QQQQWWWWEEEEEEEERRRRTTTTYYYYYYYYUUUUUUUUIIIIIIIIOOOOOOOOPPPPAAAAAAAASSSSDDDDFFFFGGGGHHHHJJJJKKKKLLLLZZZZXXXXCCCCVVVVBBBBNNNNMMMM";
    return letterBank;
}
string getPlayersLetterSet(string &bankLetters) {
    string playerSet;
    int position;
    for (int i = 0; i < 10; i++) {
        position = rand() % bankLetters.length();
        playerSet = playerSet + bankLetters[position];
        bankLetters.erase(position,1);
    }
    return playerSet;
}
string* getPlayersBank(string& letterBank, int quantityPlayers)
{
    string* giveLetters = new string[quantityPlayers];

    for (int i = 0; i < quantityPlayers; i++)
        giveLetters[i] = getPlayersLetterSet(letterBank);

    return giveLetters;
}
void outputPlayersBank(string* playersBank, int ammountPlayers)
{
    for (int i = 0; i < ammountPlayers; i++)
    {
        cout << "Банк букв " << i + 1 << " игрока: " << playersBank[i] << endl;
    }

}

bool checkStringInput(const string& str) {
    for (char c : str) {

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}
bool checkIsWordCorrect(string& playerWord, string* playersBank, int playersNumber) {
    bool isCorrect;
    string workingString;
    int lengthStr, counter;

    counter = 0;

    workingString = playersBank[playersNumber];

    for (int i = 0; i < playerWord.length(); i++) {
        isCorrect = false;
        for (int j = 0; j < playerWord.length(); j++)
            if (playerWord[i] == workingString[j]) {
                isCorrect = true;
                workingString.erase(j, 1);
                break;
            }
        if (isCorrect)
            counter++;

    }
    if (counter == playerWord.length()) {
        for (int i = 0; i < playerWord.length(); i++)
            for (int j = 0; j < playersBank[playersNumber].length(); j++);
    }
}

int main() {
    srand(time(0));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
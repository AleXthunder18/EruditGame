#include <iostream>
#include <ctime>
#include <fstream>
#include <set>

using namespace std;

int readNum(int min, int max);
int getPlayersCount();
void addNewWord(const bool englishLanguage, set<string>& vocalbulary, string word);
string readPlayersString(const bool englishLanguage);
bool voiting(const bool englishLanguage, const int ammountPlayers, const string word, set<string>& vocabulary);
bool compareWordAndVocabulary(const bool englishLanguage, const int playersCount, set<string>& vocabulary, const string word);

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

int getPlayersCount()
{
    cout << "Введите количество игроков" << endl;
    int playersCount = readNum(2, 6);
    return playersCount;
}

void addNewWord(const bool englishLanguage, set<string>& vocalbulary,string word)
{
    vocalbulary.insert(word);
}

string readPlayersString(const bool englishLanguage) {
    bool isStrCorrect;
    string str;
    do
    {
        isStrCorrect = true;
        cout << "Введите слово" << endl;
        getline(cin,str);
        if (englishLanguage)
        {
            for (char c : str)
            {

                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                    continue;
                else
                {
                    isStrCorrect = false;
                    cout << "Ошибка ввода, попробуйте снова" << endl;
                    break;
                }
            }
        }
        else
        {
            for (char c : str)
            {

                if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я'))
                    continue;
                else
                {
                    isStrCorrect = false;
                    cout << "Ошибка ввода, попробуйте снова" << endl;
                    break;
                }
            }
        }
    } while (!isStrCorrect);
    return str;
}

void subtractScoreCount(int*& playersScore, int numPlayer, string word)
{
    playersScore[numPlayer] += word.length();
}

bool voiting(const bool englishLanguage , const int ammountPlayers,const string word, set<string>& vocabulary)
{
    int yesCount = 0;
    int noCount = 0;
    for (int i = 0; i < ammountPlayers; i++)
    {
        cout << i + 1 << "игрок" << "проголосуйте/n" << "0.Нет/n" << "1.Да" << endl;
        int choice = readNum(0,1);
        if (choice)
            yesCount++;
        else
            noCount++;
    }
    if (yesCount >= noCount)
    {
        addNewWord(englishLanguage, vocabulary, word);
        return true;
    }
    else
        return false;

}

bool compareWordAndVocabulary(const bool englishLanguage, const int playersCount,set<string>& vocabulary,const string word)
{
    bool isWordReal;
    if (vocabulary.count(word) > 0)
        isWordReal = true;
    else
        isWordReal = voiting(englishLanguage, playersCount, word, vocabulary);
    return isWordReal;
}

void initializeScoreCount(int*& playersScore, int ammountPlayers)
{
    for (int i = 0; i < ammountPlayers; i++)
        playersScore[i] = 0;
}

bool isFirstLettersSame(string& prevWord, string& nowWord)
{
    bool solution;

    solution = (prevWord[0] == nowWord[0]);

    return solution;
}

void addScoreCount(int*& playersScore, int numPlayer, string& nowWord, string& prevWord)
{
    if (isFirstLettersSame(prevWord, nowWord))

        playersScore[numPlayer] += 2 * nowWord.length();

    else

        playersScore[numPlayer] += nowWord.length();

}

bool compareWordAndLettersBank(string& newWord, string*& playersBank, int numPlayer, bool& englishLanguage)
{
    string workString;
    bool isCorrect, solution;
    int counter;

    counter = 0;
    workString = playersBank[numPlayer];

    for (int i = 0; i < newWord.length(); i++)
    {
        isCorrect = false;
        for (int j = 0; j < workString.length(); j++)
            if (newWord[i] == workString[j])
            {
                isCorrect = true;
                workString.erase(j, 1);
                break;
            }

        if (isCorrect)
            counter++;
    }

    if (counter == newWord.length())
        solution = true;
    else
        solution = false;

    return solution;
}

bool isLettersCountInPlayersBankMoreThanFive(string* playersBank, int numPlayer)
{
    bool solution;

    solution = (playersBank[numPlayer].length() > 5);

    return solution;
}

bool isPlayersBankNotEmpty(string* playersBank, int numPlayer)
{
    bool solution;

    solution = (playersBank[numPlayer].length() > 0);

    return solution;
}

void deleteLettersFromPlayersBank(string word, string* playersBank, int numPlayer)
{
    for (int i = 0; i < word.length(); i++)
        for (int j = 0; j < playersBank[numPlayer].length(); j++)
            if (word[i] == playersBank[numPlayer][j])

            {
                playersBank[numPlayer].erase(j, 1);

            }
}

set<string> createPossibleVocabulary(bool& englishLanguage) {

    string path;
    set<string> vocabulary = {};

    if (englishLanguage) {
        path = "..\\..\\englishvocabulary.txt";
    }
    else {
        path = "..\\..\\russianvocabulary.txt";
    }

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

void addNewWord(string line, set<string>& vocabulary, bool& englishLanguage) {

    string path;
    string word = "";

    if (englishLanguage) {
        path = "..\\..\\englishvocabulary.txt";
    }
    else {
        path = "..\\..\\russianvocabulary.txt";
    }

    ofstream fout(path, fstream::app);
    fout << "\n" << line;
    fout.close();

    vocabulary.insert({ line });

}

void lowcase(string& word) {
    for (char& c : word) {
        c = tolower(c);
    }
}
string getLetterBank()
{
    string letterBank = "QQQQWWWWEEEEEEEERRRRTTTTYYYYYYYYUUUUUUUUIIIIIIIIOOOOOOOOPPPPAAAAAAAASSSSDDDDFFFFGGGGHHHHJJJJKKKKLLLLZZZZXXXXCCCCVVVVBBBBNNNNMMMM";
    return letterBank;
}
/*string getPlayersLetterSet(string& bankLetters) {
    string playerSet;
    int position;
    for (int i = 0; i < 10; i++) {
        position = rand() % bankLetters.length();
        playerSet = playerSet + bankLetters[position];
        bankLetters.erase(position,1);
    }
    return playerSet;
}*/

void getPlayersLetterSet(string& bankLetters, string& playerSet) {
    int position, getLetterCount;
    getLetterCount = 10 - playerSet.length();
    for (int i = 0; (i < getLetterCount) && (bankLetters.length() != 0); i++) {
        position = rand() % bankLetters.length();
        playerSet = playerSet + bankLetters[position];
        bankLetters.erase(position, 1);
    }
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

void enterGameLanguage(bool &englishLanguage)
{
    int choice;
    cout << "Выберите язык игры:\n0 - русский\n1 - английский" << endl;
    choice = readNum(0,1);
    englishLanguage = choice;
}


int main() {
    int playersCount, numPlayer;
    bool englishLanguage;
    string letterBank, nowWord, prevWord;
    string* playersBank;
    int* playersScore;
    set<string> possibleVocabulary;

    srand(time(0));

    printCondition();// вывели условие (нужно прописать, что есть возможность юзать 50\50 по команде ... и помощь друга по команде ...)
    enterGameLanguage(englishLanguage);// установили язык игры
    possibleVocabulary = createPossibleVocabulary(englishLanguage);//загрузили словарь на языке игры
    letterBank = getLetterBank(englishLanguage);//создали общий банк букв
    playersCount = getPlayersCount(); // ввели количество игроков
    playersScore = new int[playersCount];//создали массив со счетчиком очков каждого игрока
    playersBank = new string[playersCount];//создали массив с личным банком букв каждого игрока
    initializeScoreCount(playersScore, playersCount); //занулили счетчик очков
    playersBank = getPlayersBank(letterBank, playersCount); //заполнили личный банк букв каждого игрока
    outputPlayersBank(playersBank, playersCount);//вывели текущее состояние банков букв каждого игрока
    //ход игры
    for (int i = 0; i < playersCount; i++)
    {

    }



    return 0;
}
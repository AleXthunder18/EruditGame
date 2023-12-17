#include <iostream>
#include <ctime>
#include <fstream>
#include <set>
#include <cctype>
#include <windows.h>//D:\Программы С++\ConsoleApplication5\ConsoleApplication5\ConsoleApplication5.cpp4
#include <string>

using namespace std;

//void changeFiveLetters(string& playerBank, string& letterBank, string& changedLetters);
//int readNum(int min, int max);
//int getPlayersCount();
//string readPlayersString(const bool englishLanguage);
//void subtractScoreCount(int*& playersScore, int numPlayer, string nowWord);
//bool voiting(const bool englishLanguage, const int ammountPlayers, const string word, set<string>& vocabulary);
//bool compareWordAndVocabulary(const bool englishLanguage, const int playersCount, set<string>& vocabulary, const string word);
//void initializeScoreCount(int*& playersScore, int ammountPlayers);
//bool isFirstLettersSame(string& prevWord, string& nowWord);
//void addScoreCount(int*& playersScore, int numPlayer, string& nowWord, string& prevWord);
//bool compareWordAndLettersBank(string& newWord, string*& playersBank, int numPlayer, bool& englishLanguage);
//void deleteLettersFromPlayersBank(string word, string*& playersBank, int numPlayer);
//set <string> createPossibleVocabulary(bool& englishLanguage);
//void addNewWord(bool englishLanguage, set<string>& vocabulary, string line);
//void lowcase(string& word);
//void lowcaseRussian(string& word);
//string getLetterBank(const bool englishLanguage);
//void getPlayersLetterSet(string& bankLetters, string& playerSet);
//void getPlayersBank(string*& playersBank, string& letterBank, int quantityPlayers);
//void outputPlayersBank(string* playersBank, int ammountPlayers);
//void enterGameLanguage(bool& englishLanguage);
//void outputPlayersScore(int* playersScore, int ammountPlayers);
//void outputLetterWithSpace(string lettersBank);

void addNewWord(bool englishLanguage, set<string> &vocabulary, string line) {

    string path;
    string word = "";

    if (englishLanguage) {
        path = "..\\englishvocabulary.txt";
    } else {
        path = "..\\russianvocabulary.txt";
    }

    ofstream fout(path, fstream::app);
    fout << "\n" << line;
    fout.close();

    vocabulary.insert({line});

}

void changeFiveLetters(string &playerBank, string &letterBank, string &changedLetters) {
    int position;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < playerBank.length(); j++)
            if (changedLetters[i] == playerBank[j]) {
                playerBank.erase(j, 1);
                break;
            }
    for (int i = 0; i < 5; i++) {
        position = rand() % letterBank.length();
        playerBank = playerBank + letterBank[position];
        letterBank.erase(position, 1);
    }
}

int readNum(int min, int max) {
    bool isIncorrect;
    int num;

    do {
        isIncorrect = true;
        cin >> num;
        if (cin.fail() || (cin.get() != '\n')) {
            cout << "Некорректный ввод! Введите значение еще раз:" << endl;
            cin.clear();
            while (cin.get() != '\n');
        } else {
            if (num < min || num > max) {
                cout << "Недопустимое значение! Введите значение еще раз:" << endl;
            } else {
                isIncorrect = false;
            }
        }
    } while (isIncorrect);

    return num;
}

int getPlayersCount() {
    cout << "Введите количество игроков от 2 до 6" << endl;
    int playersCount = readNum(2, 6);
    return playersCount;
}

void subtractScoreCount(int *&playersScore, int numPlayer, string nowWord) {
    cout << "Количество очков уменьшено на " << nowWord.length() << endl;
    playersScore[numPlayer] -= nowWord.length();
}

bool voiting(const bool englishLanguage, const int ammountPlayers, const string word, set<string> &vocabulary,
             int numPlayers) {
    int yesCount = 0;
    int noCount = 0;
    for (int i = 0; i < ammountPlayers; i++) {
        if (i == numPlayers)
            continue;
        cout << "Игрок " << i + 1 << " проголосуйте\n" << "0 - Нет\n" << "1 - Да" << endl;
        int choice = readNum(0, 1);
        if (choice)
            yesCount++;
        else
            noCount++;
    }
    if (yesCount >= noCount) {
        addNewWord(englishLanguage, vocabulary, word);
        return true;
    } else return false;

}

bool compareWordAndVocabulary(set<string> &vocabulary, const string word) {
    bool isWordReal;
    if (vocabulary.count(word) > 0)
        isWordReal = true;
    else
        isWordReal = false;
    return isWordReal;
}

void initializeScoreCount(int *&playersScore, int ammountPlayers) {
    for (int i = 0; i < ammountPlayers; i++)
        playersScore[i] = 0;
}

bool isFirstLettersSame(string &prevWord, string &nowWord) {
    bool solution;

    solution = (prevWord[prevWord.length() - 1] == nowWord[0]);

    return solution;
}

void addScoreCount(int *&playersScore, int numPlayer, string &nowWord, string &prevWord) {
    if (isFirstLettersSame(prevWord, nowWord)) {
        cout << "Очки удваиваются! Количество очков увеличено на " << 2 * nowWord.length() << endl;
        playersScore[numPlayer] += 2 * nowWord.length();
    } else {
        cout << "Количество очков увеличено на " << nowWord.length() << endl;
        playersScore[numPlayer] += nowWord.length();
    }
}

bool compareWordAndLettersBank(string &newWord, string *&playersBank, int numPlayer, bool &englishLanguage) {
    string workString;
    bool isCorrect, solution;
    int counter;

    counter = 0;
    workString = playersBank[numPlayer];

    for (int i = 0; i < newWord.length(); i++) {
        isCorrect = false;
        for (int j = 0; j < workString.length(); j++)
            if (newWord[i] == workString[j]) {
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

void deleteLettersFromPlayersBank(string word, string *&playersBank, int numPlayer) {
    for (int i = 0; i < word.length(); i++)
        for (int j = 0; j < playersBank[numPlayer].length(); j++)
            if (word[i] == playersBank[numPlayer][j]) {
                playersBank[numPlayer].erase(j, 1);
                break;
            }
}

set<string> createPossibleVocabulary(bool &englishLanguage) {

    string path;
    set<string> vocabulary = {};

    if (englishLanguage) {
        path = "..\\englishvocabulary.txt";
    } else {
        path = "..\\russianvocabulary.txt";
    }

    string word = "";


    ifstream fin(path);
    if (!fin.is_open()) {
        printf("Какая-то ошибка с файлом.");
    } else {
        while (fin >> word) {
            vocabulary.insert({word});
        }
    }
    fin.close();

    return vocabulary;

}

void lowcase(string &word) {
    for (char &c : word) {
        c = tolower(c);
    }
}

void lowcaseRussian(string &word) {
    for (char &c : word) {
        if ((c < -32) && (c > -65)) {
            c = c + 32;
        }

        if (c == -88) {
            c = -72;
        }
    }
}

string getLetterBank(const bool englishLanguage) {
    string LetterBank;
    if (englishLanguage)
        LetterBank = "eeeeeeeeeeeettttttttttaaaaaaaaaooooooooiiiiiiinnnnnnnnsssssssshhhhhhhhrrrrrrrdddddllllccccuuuummmmwwwwffffggggyyyyppppbbbbvvvvkkkkjjjxxxqqqzzz";
    else
        LetterBank = "оооооооооаааааааааееееееееееииииииииннннннннттттттррррррссссссллллллвввввккккккппппппмммммууууудддддяяяяыыыьььзззззбббббггггйййчччююююхххжжжшшшцццщщщфффээъъ";
    return LetterBank;
}

void getPlayersLetterSet(string &bankLetters, string &playerSet) {
    int position, getLetterCount;
    getLetterCount = 10 - playerSet.length();
    for (int i = 0; (i < getLetterCount) && (bankLetters.length() != 0); i++) {
        position = rand() % bankLetters.length();
        playerSet = playerSet + bankLetters[position];
        bankLetters.erase(position, 1);
    }
}

void getPlayersBank(string *&playersBank, string &letterBank, int quantityPlayers) {
    for (int i = 0; i < quantityPlayers; i++)
        getPlayersLetterSet(letterBank, playersBank[i]);
}

void enterGameLanguage(bool &englishLanguage) {
    int choice;
    cout << "Выберите язык игры:\n0 - русский\n1 - английский" << endl;
    choice = readNum(0, 1);
    englishLanguage = choice;
}

int determineWinner(int *playersScore, int playersCount) {
    int imax = 0;
    for (int i = 1; i < playersCount; i++) {
        if (playersScore[i] > playersScore[imax])
            imax = i;
    }
    return imax;
}

void outputLettersBankWithSpace(string lettersBank) {
    cout << "Банк букв содержит символы: ";
    for (int i = 0; i < lettersBank.length(); i++)
        cout << lettersBank[i] << " ";
    cout << endl;
}

void outputLettersSetWithSpace(string lettersBank, int playersNum) {
    cout << "Набор букв " << playersNum + 1 << " игрока: ";
    for (int i = 0; i < lettersBank.length(); i++)
        cout << lettersBank[i] << " ";
    cout << endl;
}

void outputPlayersLettersSet(string *playersBank, int ammountPlayers) {
    for (int i = 0; i < ammountPlayers; i++) {
        outputLettersSetWithSpace(playersBank[i], i);
    }
    cout << endl;
}

void outputOnePlayerScore(int score, int playersNum) {
    cout << "Количество очков игрок " << playersNum + 1 << ": ";
    cout << score << endl;
}

void outputPlayersScore(int *playersScore, int ammountPlayers) {
    for (int i = 0; i < ammountPlayers; i++) {
        outputOnePlayerScore(playersScore[i], i);
    }
    cout << endl;
}

void useFiftyFiftyBonus(string *&playersBank, int numPlayer, string &letterBank, bool englishLanguage) {
    string changedLetters;
    bool isNotCorrect;
    outputLettersSetWithSpace(playersBank[numPlayer], numPlayer);
    cout << "Введите 5 букв, которые хотите заменить (в строку, без пробелов):\n";
    do {
        isNotCorrect = false;
        getline(cin, changedLetters);

        if (changedLetters.length() == 5) {
            if (englishLanguage) {
                for (int i = 0; i < 5; i++)
                    changedLetters[i] = tolower(changedLetters[i]);
            } else {
                lowcaseRussian(changedLetters);
            }

            if (compareWordAndLettersBank(changedLetters, playersBank, numPlayer, englishLanguage)) {
                changeFiveLetters(playersBank[numPlayer], letterBank, changedLetters);
            } else {
                cout << "В вашем наборе нет такой комбинации букв. Повторите ввод." << endl;
                isNotCorrect = true;
            }
        } else {
            cout << "Вы должны ввести 5 букв! Повторите ввод:" << endl;
            isNotCorrect = true;
        }
    } while (isNotCorrect);
}


void replaceLetter(string *playersBank, int numPlayer, bool englishLanguage, int playersCount) {
    int number;
    bool isNotCorrect;
    string letter, secondLetter;
    outputLettersSetWithSpace(playersBank[numPlayer], numPlayer);
    // выбор заменяемой буквы
    do {
        cout << "Введите букву, которую вы хотите заменить" << endl;
        isNotCorrect = false;
        getline(cin, letter);
        if (letter.length() == 1) {
            if (englishLanguage) {
                letter[0] = tolower(letter[0]);
            } else
                lowcaseRussian(letter);
        } else {
            cout << "Вы должны ввести 1 букву! Повторите ввод:\n";
            isNotCorrect = true;
        }
        if (!isNotCorrect) {

            isNotCorrect = !compareWordAndLettersBank(letter, playersBank, numPlayer, englishLanguage);

            if (isNotCorrect) {
                cout << "В вашем наборе нет такой буквы. Повторите ввод:\n";
            }
        }
    } while (isNotCorrect);

    //вывод наборов букв других игроков
    for (int i = 0; i < playersCount; i++) {
        if (i == numPlayer) continue;
        else outputLettersSetWithSpace(playersBank[i], i);
    }
    // выбор номера игрока
    do {
        cout << "Введите номер игрока, с которым вы хотите обменяться" << endl;
        number = readNum(1, playersCount);

        if (number - 1 == numPlayer)
            cout << "Нельзя обменяться с самим собой" << endl;
        else if (playersBank[number - 1].empty()) cout << "Набор игрока " << number << "не содержит букв" << endl;

    } while (number - 1 == numPlayer || playersBank[number - 1].empty());

    // выбор понравившейся буквы
    do {
        cout << "Введите букву,на которую вы хотите заменить свою" << endl;
        isNotCorrect = false;
        getline(cin, secondLetter);
        if (secondLetter.length() == 1) {

            if (englishLanguage) {
                secondLetter[0] = tolower(secondLetter[0]);
            } else
                lowcaseRussian(secondLetter);
        } else {
            cout << "Вы должны ввести 1 букву! Повторите ввод:\n";
            isNotCorrect = true;
        }
        if (!isNotCorrect) {

            isNotCorrect = !compareWordAndLettersBank(secondLetter, playersBank, number - 1, englishLanguage);

            if (isNotCorrect) {
                cout << "В наборе игрока нет такой буквы. Повторите ввод:\n";
            }
        }
    } while (isNotCorrect);

    //обновление наборов
    for (int i = 0; i < playersBank[numPlayer].length(); i++)
        if (playersBank[numPlayer][i] == letter[0]) {
            playersBank[numPlayer][i] = secondLetter[0];
            break;
        }

    for (int i = 0; i < playersBank[number - 1].length(); i++)
        if (playersBank[number - 1][i] == secondLetter[0]) {
            playersBank[number - 1][i] = letter[0];
            break;
        }

}

string readPlayersString(const bool englishLanguage) {
    bool isStrCorrect;
    string str;
    do {
        isStrCorrect = true;
        getline(cin, str);

        if (str == "/fifty") {
            return "/fifty";
        } else if (str == "/helpme") {
            return "/helpme";
        } else if (str == "/score") {
            return "/score";
        } else if (str == "/bank") {
            return "/bank";
        } else if (str == "/set") {
            return "/set";
        }


        if (englishLanguage) {
            lowcase(str);

            for (char c : str) {

                if ((c >= 'a') && (c <= 'z'))
                    continue;

                else {
                    isStrCorrect = false;
                    cout << "Ошибка ввода, попробуйте снова" << endl;
                    break;
                }
            }
        } else {
            lowcaseRussian(str);

            for (char c : str) {

                if ((c >= -32) && (c <= -1) || (c == -72))
                    continue;

                else {
                    isStrCorrect = false;
                    cout << "Ошибка ввода, попробуйте снова" << endl;
                    break;
                }
            }
        }
    } while (!isStrCorrect);
    return str;
}

void printCondition() {

    cout << "Игра ЭРУДИТ" << endl;
    cout << "Количество игроков - от 2 до 6" << endl;
    cout << "В начале игры для каждого игрока формируется персональный набор из 10 случайных букв" << endl;
    cout << "Задача игроков - составить из этих букв слово" << endl;
    cout << endl;
    cout << "Если слово правильное - игроку будет добавлено столько очков, сколько букв в его слове" << endl;
    cout << "Если при этом первые буквы введенного слова и последняя буква слова предыдущего игрока совпадают - начисляемые очки удваиваются" << endl;
    cout << "Если слово не состоит из букв набора игрока - количество очков игрока уменьшается на количество букв в веденном слове" << endl;
    cout << "Если слово не найдено в словаре - будет проведен опрос, знают ли ваши соперники это слово" << endl;
    cout << endl;
    cout << "Игрок может воспользоваться 2 бонусами за игру:" << endl;
    cout << "Бонус \"Помощь друга\" (команда /helpme) - игрок может заменить свою букву на любую букву из набора другого игрока" << endl;
    cout << "Бонус \"50/50\" (команда /fifty) - игрок может заменить 5 выбранных букв своего набора на 5 случайных букв из банка букв, при этом игрок теряет 2 очка" << endl;
    cout << endl;
    cout << "Если игрок не может придумать слово - он может пропустить ход, нажав клавишу ENTER" << endl;
    cout << "Игра ведется до тех пор, пока все игроки не пропустят ход" << endl;
    cout << endl;
    cout << "Полезные команды:" << endl;
    cout << "Команда /score - выведет статистику по набранным очкам" << endl;
    cout << "Команда /bank - выведет содержание банка букв" << endl;
    cout << "Команда /set - выведет набор букв каждого игрока" << endl;
    cout << endl;
    cout << "Победителем считается игрок, набравший наибольшее положительное количество очков" << endl;
}

void initializeUsedBonus(int *&usedBonus, int ammountPlayers) {
    for (int i = 0; i < ammountPlayers; i++)
        usedBonus[i] = 11;
}

int main() {
    int playersCount, skipCount;
    bool englishLanguage;
    string lettersBank;
    string *playersBank;
    int *playersScore, *usedBonus;
    set<string> possibleVocabulary;

    SetConsoleOutputCP(CP_UTF8);
    //system("chcp 1251 > nul");
    srand(time(0));


    printCondition();// вывели условие (нужно прописать, что есть возможность юзать 50\50 по команде ... и помощь друга по команде ...)
    enterGameLanguage(englishLanguage);// установили язык игры
    cout << "загрузка словаря..." << endl;
    possibleVocabulary = createPossibleVocabulary(englishLanguage);//загрузили словарь на языке игры
    lettersBank = getLetterBank(englishLanguage);//создали общий банк букв
    playersCount = getPlayersCount(); // ввели количество игроков
    playersScore = new int[playersCount];//создали массив со счетчиком очков каждого игрока
    playersBank = new string[playersCount];//создали массив с личным банком букв каждого игрока
    usedBonus = new int[playersCount];//создали массив с неиспользованными бонусами каждого игрока
    initializeScoreCount(playersScore, playersCount); //занулили счетчик очков
    initializeUsedBonus(usedBonus, playersCount); //занулили использованные бонусы
    getPlayersBank(playersBank, lettersBank, playersCount); //заполнили личный банк букв каждого игрока

    //ход игры
    string nowWord, prevWord = ".";
    skipCount = 0;
    do {
        for (int i = 0; i < playersCount && skipCount < playersCount; i++) {
            cout << endl;
            outputLettersSetWithSpace(playersBank[i], i);//вывели текущее состояние набора букв игрока

            bool specialCmd;
            do {
                specialCmd = false;
                cout << "Игрок " << i + 1 << ", введите ваше слово:" << endl;
                nowWord = readPlayersString(englishLanguage);//ввод слова игроком

                if (nowWord == "/fifty") {
                    specialCmd = true;
                    if (usedBonus[i] / 10 == 0) {
                        cout << "Вы уже использовали бонус 50/50" << endl;
                        continue;
                    }
                    if (lettersBank.length() < 5) {
                        cout << "Банк содержит меньше 5 букв, вы не можете использовать этот бонус" << endl;
                        continue;
                    }
                    if (playersBank[i].length() >= 5) {
                        cout << "Бонус 50/50!" << endl;
                        useFiftyFiftyBonus(playersBank, i, lettersBank, englishLanguage);
                        cout << "обновление набора букв..." << endl;
                        outputLettersSetWithSpace(playersBank[i], i);
                        cout << "Количество очков уменьшено на 2" << endl;
                        playersScore[i] -= 2;
                        usedBonus[i] -= 10;
                    } else {
                        cout << "У вас осталось меньше 5 букв, вы не можете использовать этот бонус" << endl;
                    }
                } else if (nowWord == "/helpme") {
                    specialCmd = true;
                    if (usedBonus[i] % 10 == 0) {
                        cout << "Вы уже использовали бонус Помощь друга" << endl;
                        continue;
                    }
                    if (playersBank[i].length() > 0) {
                        cout << "Бонус Помощь друга!" << endl;
                        replaceLetter(playersBank, i, englishLanguage, playersCount);
                        cout << "обновление набора букв..." << endl;
                        outputLettersSetWithSpace(playersBank[i], i);
                        usedBonus[i] -= 1;
                    } else {
                        cout << "Ваш набор букв не содержит ни одной буквы, вы не можете использовать этот бонус"
                             << endl;
                    }
                } else if (nowWord == "/score") {
                    specialCmd = true;
                    outputPlayersScore(playersScore, playersCount);
                } else if (nowWord == "/bank") {
                    specialCmd = true;
                    outputLettersBankWithSpace(lettersBank);
                } else if (nowWord == "/set") {
                    specialCmd = true;
                    outputPlayersLettersSet(playersBank, playersCount);
                }
            } while (specialCmd);

            if (nowWord.empty()) {
                cout << "Пропуск хода" << endl;
                skipCount++;
                continue;
            } else skipCount = 0;

            //начисление очков
            if (compareWordAndLettersBank(nowWord, playersBank, i, englishLanguage)) {
                if (compareWordAndVocabulary(possibleVocabulary, nowWord)) {
                    addScoreCount(playersScore, i, nowWord, prevWord);
                    deleteLettersFromPlayersBank(nowWord, playersBank, i);
                    getPlayersBank(playersBank, lettersBank, playersCount);
                } else {
                    cout << "Такого слова нет в словаре" << endl;
                    cout << "Будет проведен опрос, знают ли ваши соперники это слово" << endl;
                    if (voiting(englishLanguage, playersCount, nowWord, possibleVocabulary, i)) {
                        cout << "Слово добавлено в словарь" << endl;
                        addNewWord(englishLanguage, possibleVocabulary, nowWord);
                        addScoreCount(playersScore, i, nowWord, prevWord);
                        deleteLettersFromPlayersBank(nowWord, playersBank, i);
                        getPlayersBank(playersBank, lettersBank, playersCount);
                    } else {
                        subtractScoreCount(playersScore, i, nowWord);
                    }
                }
            } else {
                cout << "В слове присутствуют буквы, которых нет в вашем наборе букв" << endl;
                subtractScoreCount(playersScore, i, nowWord);
            }
            prevWord = nowWord;

            outputOnePlayerScore(playersScore[i], i);
        }
    } while (skipCount < playersCount);

    cout << endl << "ИГРА ОКОНЧЕНА" << endl;
    outputPlayersScore(playersScore, playersCount);
    int winnerNum = determineWinner(playersScore, playersCount);

    if (playersScore[winnerNum] > 0) {
        cout << "ПОБЕДИТЕЛИ:" << endl;
        for (int i = 0; i < playersCount; i++) {
            if (playersScore[i] == playersScore[winnerNum]) {
                cout << "ИГРОК " << i + 1 << " --- ";
                cout << "КОЛИЧЕСТВО ОЧКОВ - " << playersScore[i]  << "!" << endl;
            }
        }
    }
    else cout << "Никто из участников не набрал больше 0 очков, попробуйте сыграть еще раз!" << endl;
    return 0;
}
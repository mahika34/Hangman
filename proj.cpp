#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int word_check(string str,string randomWord)
{
    if(randomWord==str)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
string selectRandomWordFromFile(const string &filename) 
{
    ifstream file(filename);
    vector<string> words;
    string word;
    if (file.is_open()) 
    {
        while (file >> word) 
        {
            words.push_back(word);
        }
        file.close();
        if (!words.empty()) 
        {
            srand(static_cast<unsigned int>(time(nullptr)));
            int randomIndex = rand() % words.size();
            return words[randomIndex];
        } 
        else 
        {
            cerr << "File is empty." << endl;
        }
    } 
    else 
    {
        cerr << "Unable to open the file." << endl;
    }
    return ""; 
}
int main() 
{
    string randomWord = selectRandomWordFromFile("words.txt");
    if (!randomWord.empty()) 
    {
        cout << "Random word selected: " << randomWord << endl;
    }
    cout << "WELCOME TO HANGMAN" << endl;
    int tr = 7, option,res;
    string word;
    char letter;
    string guessedWord(randomWord.length(), '_'); 
    while (tr != 0) 
    {
        cout << "you have  " << tr << "  tries" << endl;
        cout << "Word: ";
        for (char c : guessedWord) 
        {
            cout << c << " ";
        }
        cout << endl;
        cout << "1. GUESS THE WORD   2. GUESS THE LETTER" << endl;
        cin >> option;
        switch (option) 
        {
            case 1: {
                    cout<<"GUESS THE WORD"<<endl;
                    cin>>word;
                    res=word_check(word,randomWord);
                    if(res==0)
                    {
                        cout<<"Sorry wrong guess!"<<endl;
                    }
                    tr--;
                    break;
                    }
            case 2: {
                        cout << "GUESS THE LETTER" << endl;
                        cin >> letter;
                        size_t found = randomWord.find(letter);
                        if (found != string::npos) 
                        {
                            cout << "Correct guess!" << endl;
                            while (found != string::npos) 
                            {
                                guessedWord[found] = letter;
                                found = randomWord.find(letter, found + 1);
                            }
                        } 
                        else 
                        {
                            cout << "Incorrect guess!" << endl;
                            
                        }
                        tr--;
                        break;
                    }
            default:cout << "TRY AGAIN" << endl;
        } 
        if (guessedWord == randomWord || res==1) 
        {
            cout << "Congratulations! You guessed the word!" << endl;
            break;
            //tr = 0;
        }
    }
    if(tr==0)
    {
        cout << "You ran out of tries! Game Over!" << endl;
    }
    cout << "The word was: " << randomWord << endl;
    cout << endl;
    cout << "EXITING THE GAME" << endl;
    cout << ".................." << endl;
    cout << "THANK YOU FOR PLAYING" << endl;
    return 0;
}
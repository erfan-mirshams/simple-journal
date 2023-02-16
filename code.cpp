#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdio>

#define COMMANDSIZE 4
#define POSWORDSFILE "positive-words.txt"
typedef struct date date;
typedef struct diary diary;

using namespace std;

struct date {
    int year;
    int month;
    int day;
};

struct diary{
    date d;
    string content;
    int pos_count;
};

string word_from_position(string::iterator &it, string &line){
    while(isspace(*(it++)));
    --it;
    string::iterator i = it;
    for (; i != line.end(); ++i) {
        if(isspace(*i)){
            break;
        }
    }
    swap(i, it); /*because it is a reference*/
    return line.substr(i - line.begin(), it - i);
}

void read_positive_words(vector<string> &pos){
    ifstream f(POSWORDSFILE);
    string tmp = "";
    while(f.peek() != EOF){
        getline(f, tmp);
        pos.push_back(tmp);
    }
}

int main(){
    string line = "", current_journal = "";
    string commands[COMMANDSIZE] = {"start_day", "show_day", "show_the_longest_day", "show_the_best_day"};

    vector<string> pos;
    read_positive_words(pos);

    vector<diary> diaries;
    diary tmp_diary;
    while (cin.peek() != EOF) {
        getline(cin, line);
    }
    return 0;
}

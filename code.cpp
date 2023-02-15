#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#define COMMANDSIZE 4
typedef struct date date;

using namespace std;

struct date {
    int year;
    int month;
    int day;
};

string first_word_from_pos(string::iterator &it, string &line){
    while(isspace(*(it++)));
    --it;
    string::iterator i = it;
    for (; i != line.end(); ++i) {
        if(isspace(*i)){
            break;
        }
    }
    swap(i, it);
    return line.substr(i - line.begin(), it - i);
}

int main(){
    string line = "", current_journal = "";
    string commands[COMMANDSIZE] = {"start_day", "show_day", "show_the_longest_day", "show_the_best_day"};
    while (cin.peek() != EOF) {
        getline(cin, line);
    }
    return 0;
}

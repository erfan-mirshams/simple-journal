#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <cctype>
#include <cstdio>

#define COMMANDSIZE 4
#define POSWORDSFILE "positive-words.txt"

using namespace std;

int is_good_word(string word, vector<string> pos){
    return (find(pos.begin(), pos.end(), word) != pos.end());
}

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

class date {
    public:
        date(string date_str);
        string to_string();
        bool operator==(const date &b){return (year == b.year && month == b.month && day == b.day);}
        bool operator!=(const date &b){return !(*this == b);}
        bool operator<=(const date &b){return make_pair(make_pair(year, month), day) <= make_pair(make_pair(b.year, b.month), b.day);}
    private:
        int year;
        int month;
        int day;
};

date::date(string date_str){
    sscanf(date_str.c_str(), "%d/%d/%d", &day, &month, &year);
}

string date::to_string(){
    char ch[100];
    sprintf(ch, "%d/%d/%d", day, month, year);
    return string(ch);
}


class diary{
    public:
        diary(string date_str, string content, vector<string> pos);
        void print_full(){printf("%s", content.c_str());}
        void print_summary();
        date get_date() {return d;}
        string get_content() {return content;}
        int get_pos_count() {return pos_count;}
    private:
        date d;
        string content;
        int pos_count;
};


diary::diary(string date_str, string content, vector<string> pos)
    :d(date_str)
{
    this -> content = content;
    this -> pos_count = 0;
    string::iterator it = content.begin();
    while(it != content.end()){
        pos_count += is_good_word(word_from_position(it, content), pos);
    }
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
    string content_temp = "";
    string date_str_temp = "";
    while (cin.peek() != EOF) {
        getline(cin, line);
        line.push_back('\n'); /*apparently endline counts as a character*/

        string::iterator it = line.begin();
        string first_word = word_from_position(it, line);

        int i;
        for (i = 0; i < COMMANDSIZE; i++) {
            if (!first_word.compare(commands[i])) {
                break;
            }
        }

        if (i == COMMANDSIZE) {
            content_temp.append(line);
        }
        else {
            if (date_str_temp.compare("")) {
                diaries.push_back(diary(date_str_temp, content_temp, pos));
            }
            content_temp.clear();
        }

        switch (i) {
            case 0:{
                date_str_temp = word_from_position(it, line);
            }
                break;
            case 1:{
                vector<diary>::iterator diary_it = find_if(diaries.begin(), diaries.end(), [&](diary cur){return cur.get_date() == date(date_str_temp);});
                diary_it -> print_full();
            }
                break;
            case 2:{

            }
                break;
        }

    }
    return 0;
}

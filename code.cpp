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

string word_from_position(string::iterator &it, string::iterator fn){
    while(isspace(*(it++)));
    --it;
    string::iterator i = it;
    string res = "";
    for (; i != fn; ++i) {
        if(isspace(*i)){
            break;
        }
        res.push_back(*i);
    }
    swap(i, it); /*because it is a reference*/
    return res;
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
        void append_content(string content){this -> content.append(content);}
        date get_date() {return d;}
        string get_content() {return content;}
        int get_content_size() {return (int)content.size();}
        int get_pos_count() {return pos_count;}
    private:
        date d;
        string content;
        int pos_count;
};

void diary::print_summary(){
    printf("%s\n", d.to_string().c_str());
    if (content.size() > 20) {
        printf("%s...\n", content.substr(0, 20).c_str());
    }
    else{
        printf("%s", content.c_str());
    }
}

diary::diary(string date_str, string content, vector<string> pos)
    :d(date_str)
{
    this -> content = content;
    this -> pos_count = 0;
    string::iterator it = content.begin();
    while(it != content.end()){
        pos_count += is_good_word(word_from_position(it, content.end()), pos);
    }
}

vector<diary>::iterator find_diary_with_highest_val(vector<diary>::iterator st, vector<diary>::iterator fn, int (diary::*get_val)()){
    vector<diary>::iterator diary_it, ind = st;
    for (diary_it = st; diary_it != fn; ++diary_it) {
        int mx = (*ind.*get_val)(), sz = (*diary_it.*get_val)();
        date d = ind -> get_date(), td = diary_it -> get_date();
        if (sz > mx || (sz == mx && td <= d)) {
            ind = diary_it;
        }
    }
    return ind;
}

vector<diary>::iterator find_diary_from_date_string(vector<diary>::iterator st, vector<diary>::iterator fn, string date_str){
    return find_if(st, fn, [&](diary cur){return cur.get_date() == date(date_str);});
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
        string first_word = word_from_position(it, line.end());

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
                vector<diary>::iterator diary_it = find_diary_from_date_string(diaries.begin(), diaries.end(), date_str_temp);
                if (diary_it == diaries.end()) {
                    diaries.push_back(diary(date_str_temp, content_temp, pos));
                }
                else{
                    diary_it -> append_content(content_temp);
                }
            }
            content_temp.clear();
        }

        switch (i) {
            case 0:{
                date_str_temp = word_from_position(it, line.end());
            }
                break;
            case 1:{
                vector<diary>::iterator diary_it = find_diary_from_date_string(diaries.begin(), diaries.end(), word_from_position(it, line.end()));
                diary_it -> print_full();
            }
                break;
            case 2:{
                vector<diary>::iterator diary_it = find_diary_with_highest_val(diaries.begin(), diaries.end(), &diary::get_content_size);
                diary_it -> print_summary();
            }
                break;
            case 3:{
                vector<diary>::iterator diary_it = find_diary_with_highest_val(diaries.begin(), diaries.end(), &diary::get_pos_count);
                diary_it -> print_summary();
            }
                break;
        }

    }
    return 0;
}

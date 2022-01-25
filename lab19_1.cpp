#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    int i = 0, a, b, c;
    string textline, format;
    char allname[100];
    ifstream fin(filename);
    while(getline(fin, textline)){
        format = "%[^:]: %i %i %i";
        sscanf(textline.c_str(), format.c_str(), allname, &a, &b, &c);
        names.push_back(allname);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(scores[i]));
        i++;
    }
}

void getCommand(string &command,string &key)
{
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "NAME" || toUpperStr(command) == "GRADE")
    {
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> &names,vector<int> &scores,vector<char> &grades, string &key)
{
    int len = names.size(), find = 0;
    cout << "---------------------------------" << endl;
    for(int i = 0; i < len; i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            find ++;
        }
    }
    if(find == 0){
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int len = grades.size(), find = 0;
    cout << "---------------------------------" << endl;
    for(int i = 0; i < len; i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
            find ++;
        }
    }
    if(find == 0)
    {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
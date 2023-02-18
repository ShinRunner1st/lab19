#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<cstring>

using namespace std;

char score2grade(int score)
{
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x)
{
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades)
{
    ifstream file;
    file.open(filename);
    string textline;
    char nam[100];
    int a,b,c;
    char format[] = "%[^:]: %d %d %d";
    while (getline(file,textline))
    {
        sscanf(textline.c_str(),format,&nam,&a,&b,&c);
        names.push_back(nam);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
    file.close();
    
}

void getCommand(string &command, string &key)
{
    string inputtext;
    cout << "Please input your command: ";

    getline(cin,inputtext);
    int start = 0;
    command = inputtext.substr(start,inputtext.find_first_of(" "));
    start = inputtext.find_first_of(" ")+1;
    key = inputtext.substr(start,inputtext.size());
    if(toUpperStr(command) == "EXIT") return;
    else if(toUpperStr(command) != "EXIT" && toUpperStr(command) != "GRADE" && toUpperStr(command) != "NAME") return;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key)
{
    bool Isfound = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++)
    {
        if(toUpperStr(key) == toUpperStr(names[i]))
        {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            Isfound = true;
        }
    }
    if(!Isfound) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key)
{
    bool Isfound = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < grades.size(); i++)
    {
        string s{grades[i]};
        if(toUpperStr(key) == toUpperStr(s))
        {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            Isfound = true;
        }
    }
    if(!Isfound) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
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

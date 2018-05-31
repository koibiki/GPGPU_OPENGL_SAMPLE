#include<iostream>
#include<vector>
#include<set>
#include<string.h>
#include<algorithm>

using namespace std;
struct student{
    char name[10];
    int score;
    int age;
};

bool comp(const student &a, const student &b){
    if (a.score > b.score)
        return true;
    else if (a.score == b.score  && a.age > b.age)
        return true;
    else
        return false;
}
int main(){
    vector<student> vectorStudents;
    int n = 6;
    while (n--){
        student oneStudent;
        string name;
        int score;
        int age;
        cin >> name >> score>>age;
        strcpy(oneStudent.name, name.c_str());
        oneStudent.score = score;
        oneStudent.age = age;
        vectorStudents.push_back(oneStudent);
    }
    cout << "===========排序前================" << endl;
    for (vector<student>::iterator it = vectorStudents.begin(); it != vectorStudents.end(); it++){
        cout << "name: " << it->name << " score: " << it->score << " age: "<<it->age<<endl;
    }
    vectorStudents.begin();
    sort(vectorStudents.begin(), vectorStudents.end(), comp);
    //sort(setStudents.begin(), setStudents.end());
    cout << "===========排序后================" << endl;
    for (vector<student>::iterator it = vectorStudents.begin(); it != vectorStudents.end(); it++){
        cout << "name: " << it->name << " score: " << it->score << " age: " << it->age << endl;
    }
    return 0;
}
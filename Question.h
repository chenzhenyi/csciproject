#ifndef QUESTION_H
#define	QUESTION_H

#include <string>
#include <vector>

using namespace std;

class Question {
public:
    Question();
    Question(const Question& orig);
    virtual ~Question();
    
    void SetMarks(int marks);
    int GetMarks() const;
    void SetAnswer(char answer);
    char GetAnswer() const;
    void SetOptions(vector<string> options);
    vector<string> GetOptions() const;
    void SetQuestion(string question);
    string GetQuestion() const;
private:
    string question;
    vector<string> options;
    char answer;
    int marks;
};

#endif	/* QUESTION_H */


#ifndef QUESTION_H
#define	QUESTION_H

#include <string>
#include <vector>

using namespace std;

class Question {
public:
    Question();
    Question(string question, vector<string> options, char answer, int marks);
    
    virtual ~Question();
    
    void SetMarks(int marks);
    int GetMarks() const;
    void SetAnswer(char answer);
    char GetAnswer() const;
    void SetOptions(vector<string> options);
    vector<string> GetOptions() const;
    void SetQuestion(string question);
    string GetQuestion() const;
    
    /**
        Check the answer from user agaisnt the given answer from lecturer.

        @param answer the choice.
        @return true if the answer is correct, false otherwise.
    */
    bool CheckAnswer(char answer);
    
    /**
        Pretty print the question.
    */
    void Print();
    void SetId(int id);
    int GetId() const;
private:
    int id;
    string question;
    vector<string> options;
    char answer;
    int marks;
};

#endif	/* QUESTION_H */


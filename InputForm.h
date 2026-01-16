#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>
#include <locale>

class InputForm
{
private:
    // timereg, id, +++
    // values.push_back(std::make_pair("timereg",""));
    // values.push_back(std::make_pair("id",""));
    // values.push_back(std::make_pair("object",""));
    // values.push_back(std::make_pair("indicator",""));
    // values.push_back(std::make_pair("period",""));
    // values.push_back(std::make_pair("value",""));
    std::vector<std::pair<std::string, std::string>> values;
    std::vector<std::pair<std::string, std::string>> inValues;
    struct Field
    {
        int sKeyY=0;
        int sKeyX=0;
        int sValY=0;
        int sValX=0;        
    };
    std::vector<Field> fields;

    WINDOW* stdscr;

public:
    // InputForm();
    // ~InputForm();

    int importKeys(std::vector<std::pair<std::string, std::string>> inVal);

    void definingFields();

    void updateFields(int activeField);

    int runInputForm(std::vector<std::pair<std::string, std::string>> inVal);

    void saveValues();

    void printValues();

    std::vector<std::pair<std::string, std::string>> getValues();

};
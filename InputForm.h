#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>
#include <locale>

class InputForm
{
private:
    std::vector<std::pair<std::string, std::string>> values;
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

    int importKeys(std::vector<std::pair<std::string, std::string>> inValues);

    void definingFields();

    void updateFields(int activeField);

    int runInputForm(std::vector<std::pair<std::string, std::string>> inValues);

    void printValues();

    std::vector<std::pair<std::string, std::string>> getValues();

};
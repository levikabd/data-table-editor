#include <vector>
#include <string>
#include <iostream>

#include "InputForm.h"

int main() {


    std::vector<std::pair<std::string, std::string>> values;

    values.push_back(std::make_pair("id",""));
    values.push_back(std::make_pair("object",""));
    values.push_back(std::make_pair("indicator",""));
    values.push_back(std::make_pair("period",""));
    values.push_back(std::make_pair("value",""));

    InputForm myForm;
    int retVal = myForm.runInputForm(values);
    if (retVal != 0){ return retVal;};

    myForm.printValues();

    return 0;
};


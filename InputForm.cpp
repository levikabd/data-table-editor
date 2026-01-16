#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>
#include <locale>

#include "InputForm.h"
#include "date-time-str.h"

// class InputForm
// {
// private:
    // timereg, id, ++++
    // values.push_back(std::make_pair("timereg",""));
    // values.push_back(std::make_pair("id",""));
    // values.push_back(std::make_pair("object",""));
    // values.push_back(std::make_pair("indicator",""));
    // values.push_back(std::make_pair("period",""));
    // values.push_back(std::make_pair("value",""));
//     std::vector<std::pair<std::string, std::string>> values;
//     std::vector<std::pair<std::string, std::string>> inValues;
    // struct Field
    // {
    //     int sKeyY=0;
    //     int sKeyX=0;
    //     int sValY=0;
    //     int sValX=0;
    // };
    // std::vector<Field> fields;    
        //  box                         0
        //  header                      0
        //  ----------------------------1
        //  column names "key", "value" 2
        // -----------------------------3
        //  key "ESC", "SAVE",                // lines - 1
        // -----------------------------   // lines
        // + each field * 2

        //WINDOW* stdscr;

// public:
//     InputForm(/* args */);
//     ~InputForm();

    int InputForm::importKeys(std::vector<std::pair<std::string, std::string>> inVal)
    {
        values=inVal;
        inValues=inVal;
        return 0;
    };

    void InputForm::definingFields()
    {
        //  box                         0
        //  header                      0
        //  ----------------------------1
        //  column names "key", "value" 2
        // -----------------------------3
        //  key "ESC", "SAVE"                // lines - 1
        // -----------------------------   // lines
        // + each field * 2
        //size_t i = 0; +4

        attron(COLOR_PAIR(5));
        mvaddstr(0, 20,  "  DATA ENTRY FORM  ");
        mvaddstr(2, 4,  "   key");
        mvaddstr(2, 20, "   value");

        //attron(COLOR_PAIR(3));
        for (size_t x = 4; x < 70; x++)
        {
            mvwaddch(stdscr, 1, x, ACS_HLINE);  // Horizontal line
            mvwaddch(stdscr, 3, x, ACS_HLINE);  // Horizontal line
        };

        mvwaddch(stdscr, 2,  3, ACS_VLINE);  // The vertical line on the left 
        mvwaddch(stdscr, 2, 19, ACS_VLINE);  // The vertical line in the middle 
        mvwaddch(stdscr, 2, 70, ACS_VLINE);  // The vertical line on the right
        mvwaddch(stdscr, 3,  3, ACS_VLINE);  // The vertical line on the left 
        mvwaddch(stdscr, 3, 19, ACS_VLINE);  // The vertical line in the middle 
        mvwaddch(stdscr, 3, 70, ACS_VLINE);  // The vertical line on the right

        // The positions of the input fields
        size_t i = 0;
        for ( i = 0; i <= inValues.size(); i++)
        {
            Field nField;
            nField.sKeyY=i*2 + 4;
            nField.sKeyX=4;
            nField.sValY=i*2 + 4;
            nField.sValX=20;
            fields.push_back(nField);
        };
        // int idY        =  6, idX        = 20;
        
        size_t y = 0;
        for ( y = 0; y < inValues.size(); y++)
        {
            for (size_t x = 4; x < 70; x++)
            {
                mvwaddch(stdscr, fields.at(y).sKeyY+1, x, ACS_HLINE);  // Horizontal line
            };
        };

        y = 0;
        for ( y = 0; y < inValues.size()-1; y++)
        {
            mvwaddch(stdscr, fields.at(y).sKeyY,  3, ACS_VLINE);  // The vertical line on the left 
            mvwaddch(stdscr, fields.at(y).sKeyY, 19, ACS_VLINE);  // The vertical line in the middle 
            mvwaddch(stdscr, fields.at(y).sKeyY, 70, ACS_VLINE);  // The vertical line on the right
            mvwaddch(stdscr, fields.at(y).sKeyY+1, 3, ACS_VLINE);  // The vertical line on the left
            mvwaddch(stdscr, fields.at(y).sKeyY+1,19, ACS_VLINE);  // The vertical line in the middle
            mvwaddch(stdscr, fields.at(y).sKeyY+1,70, ACS_VLINE);  // The vertical line on the right
        };
        mvwaddch(stdscr, fields.at(y).sKeyY,  3, ACS_VLINE);  // The vertical line on the left 
        mvwaddch(stdscr, fields.at(y).sKeyY, 19, ACS_VLINE);  // The vertical line in the middle 
        mvwaddch(stdscr, fields.at(y).sKeyY, 70, ACS_VLINE);  // The vertical line on the right

        mvwaddch(stdscr, 1, 3, ACS_ULCORNER);
        mvwaddch(stdscr, 1, 70, ACS_URCORNER);
        mvwaddch(stdscr, fields.at(y).sKeyY+1,  3, ACS_LLCORNER);
        mvwaddch(stdscr, fields.at(y).sKeyY+1, 70, ACS_LRCORNER);
        attroff(COLOR_PAIR(5));
    };

    void InputForm::updateFields(int activeField)
    {
        mvaddstr(0, 1, getTimeHM().c_str());
        //  box                         0
        //  header                      0
        //  ----------------------------1
        //  column names "key", "value" 2
        // -----------------------------3
        //  key "ESC", "SAVE"              // lines - 1
        // -----------------------------   // lines

        size_t i = 0;
        for ( i = 0; i < inValues.size(); i++)
        {
            mvaddstr(fields.at(i).sKeyY, fields.at(i).sKeyX, inValues.at(i).first.c_str());
            if ((inValues.at(i).first=="timereg")){
                inValues.at(i).second=getDTime();
            };
            if ((inValues.at(i).first=="timereg") || (inValues.at(i).first=="id")){
                mvprintw(fields.at(i).sValY, fields.at(i).sValX, "%s", inValues.at(i).second.c_str());
            };
        };

        i = 0;
        for ( i = 2; i < values.size(); i++)
        {              
            if (i==activeField)
            {
                attron(COLOR_PAIR(7));
                mvaddstr(fields.at(i).sValY, fields.at(i).sValX, "                                                  ");  // clearing the field
                mvprintw(fields.at(i).sValY, fields.at(i).sValX, "%s", inValues.at(i).second.c_str());   //         
                attroff(COLOR_PAIR(7));  
            }else{
                attron(COLOR_PAIR(8));
                    mvaddstr(fields.at(i).sValY, fields.at(i).sValX, "                                                  ");  // clearing the field
                    mvprintw(fields.at(i).sValY, fields.at(i).sValX, "%s", inValues.at(i).second.c_str());   //         
                attroff(COLOR_PAIR(8));
            };
        };        

        attron(COLOR_PAIR(8));
        mvaddstr(fields.at(i).sValY,  4, "<DON'T SAVE(ESC)>");  //  "<  CANCEL(ESC)  >"
        mvaddstr(fields.at(i).sValY, 23, "< SAVE+EXIT (OK)>");  //  "<      SAVE     >"
        // mvaddstr(fields.at(i).sValY, 42, "<     OTHER     >");
        attroff(COLOR_PAIR(8));

        size_t x = 3;
        // char sChar= ' ', rChar=' ';     
        //for (size_t count = 0; count < 3; count++)
        for (size_t count = 0; count < 2; count++)
        {
            if (activeField!=inValues.size()+count)
            {
                mvwaddch(stdscr, fields.at(i).sValY, x, ' ');
                mvwaddch(stdscr, fields.at(i).sValY, x+18, ' ');
                for (size_t xKey = 0; xKey < 18; xKey++)
                {
                    mvwaddch(stdscr, fields.at(i).sValY+1, x+xKey, ' ');
                };            
                mvwaddch(stdscr, fields.at(i).sValY+1,  x, ' ');
                mvwaddch(stdscr, fields.at(i).sValY+1, x+18, ' ');
            };

            if (activeField==inValues.size()+count)
            {
                // sChar='_';// sChar=ACS_HLINE;
                // rChar='|'; // rChar=ACS_VLINE;
            // }else if (activeField==values.size()+1)
            // {
                // mvwaddch(stdscr, fields.at(i).sValY+1, x, rChar);
                // mvwaddch(stdscr, fields.at(i).sValY+1, x+19, rChar);                
                attron(COLOR_PAIR(7));
                mvwaddch(stdscr, fields.at(i).sValY, x, ACS_VLINE);
                mvwaddch(stdscr, fields.at(i).sValY, x+18, ACS_VLINE);
                for (size_t xKey = 0; xKey < 18; xKey++)
                {
                    mvwaddch(stdscr, fields.at(i).sValY+1, x+xKey, ACS_HLINE);
                };            
                mvwaddch(stdscr, fields.at(i).sValY+1,  x, ACS_LLCORNER);
                mvwaddch(stdscr, fields.at(i).sValY+1, x+18, ACS_LRCORNER);
                attroff(COLOR_PAIR(7));
            };

            x+=19;
        };
        
    };

    int InputForm::runInputForm(std::vector<std::pair<std::string, std::string>> inVal)
    {
        importKeys(inVal);

        //setlocale(LC_ALL, "ru_RU.UTF-8") ; 
        setlocale(LC_ALL, "") ; 
        stdscr = initscr();            
        
        int height, width;
        getmaxyx(stdscr, height, width);
        
        int reqHeight= inValues.size()*2 + 7;
        if (reqHeight>height)
        {
            std::cout << "This form requires a large window height (units" << reqHeight << ").\n";
            std::cout << "Current window height: " << height << ".\n";

            curs_set(1);
            refresh();
            clear();        
            endwin();         

            return -1;
        };        

        cbreak();            // no buffering mode
        raw();               // raw mode for correct input
        noecho();           // do not display the entered characters
        curs_set(0);        // hide the cursor
        keypad(stdscr, TRUE); // enable key processing

        // if (!has_colors()) {
        //     endwin();
        //     printf("The terminal does not support colors!\n");
            
            start_color();      // init color

            //Available colors:
            // COLOR_BLACK
            // COLOR_RED
            // COLOR_GREEN
            // COLOR_YELLOW
            // COLOR_BLUE
            // COLOR_CYAN
            // COLOR_WHITE

            // init_pair(1, COLOR_GREEN, COLOR_BLACK); // COLOR_GREEN text on a black background
            // init_pair(2, COLOR_BLUE, COLOR_BLACK); // COLOR_BLUE text on a black background
            // init_pair(3, COLOR_CYAN, COLOR_BLACK); // COLOR_CYAN text on a black background
            // init_pair(4, COLOR_RED, COLOR_BLACK);  // COLOR_RED text on a black background
            init_pair(5, COLOR_WHITE, COLOR_BLUE); // COLOR_WHITE text on a BLUE background,    background
            // init_pair(6, COLOR_WHITE, COLOR_GREEN); // COLOR_WHITE text on a GREEN background,   not
            init_pair(7, COLOR_WHITE, COLOR_BLACK); // COLOR_WHITE text on a black background,   the input field
            init_pair(8, COLOR_BLACK, COLOR_CYAN); // keys and fields

        //     //return 1;
        // };

        attron(COLOR_PAIR(5));
        box(stdscr, ACS_VLINE, ACS_HLINE);
        //box(stdscr, 0, 0);             
        mvwaddch(stdscr, 0, 0, ACS_ULCORNER);
        mvwaddch(stdscr, 0, COLS-1, ACS_URCORNER);
        mvwaddch(stdscr, LINES-1, 0, ACS_LLCORNER);
        mvwaddch(stdscr, LINES-1, COLS-1, ACS_LRCORNER);
        attroff(COLOR_PAIR(5));

        wbkgd(stdscr, COLOR_PAIR(5) | ' ');     // Setting the window background

        //wrefresh(stdscr)
        //refresh();

        definingFields();        
        
        // Current active field
        int activeField = 2; // 0 - timereg, 1 - id, 2 - object, 3 - indicator ... (values + 2, esc/save) 
        
        // The main input processing cycle
        while (true) {

            updateFields(activeField);
            wrefresh(stdscr);
            refresh();
            
            int ch = getch();  // We get a pressed key
            
            if (ch==KEY_DOWN)
            {
                activeField ++;
                if (activeField>(inValues.size()+1))
                {
                    activeField=2;
                };
            }else if (ch==KEY_UP)
            {
                activeField = (activeField - 1) % (inValues.size()+1);    // +3
            };
            if (activeField ==-1){ activeField= inValues.size()+1;};                
            if (activeField == 0){ activeField= inValues.size()+1;};                
            if (activeField == 1){ activeField= inValues.size()+1;};                
            
            if (ch==10)   // the Enter key
            {

                if (activeField==inValues.size())
                {
                    ch=27;
                };

                if (activeField==inValues.size()+1)
                {
                    curs_set(1);
                    clear();
                    refresh();
                    endwin();

                    saveValues();
                    break;
                };
                
                // if (activeField==values.size()+2)
                // {
                //     runOk();
                // };    
                
                if (activeField<inValues.size())
                {
                    activeField ++;
                };
           };

            if (ch == KEY_BACKSPACE || ch == 127) {  // the Backspace   key
                if (activeField<inValues.size()) {
                    std::string value=inValues.at(activeField).second;
                    if (!value.empty()){
                        value.pop_back();
                        inValues.at(activeField).second=value;
                    };
                };
            };
    
            if (isprint(ch)) {  // If the print key is pressed
                if (activeField<inValues.size()) {
                    std::string value=inValues.at(activeField).second;
                    value += ch;
                    inValues.at(activeField).second=value;
                };
            };

            if (ch == 27) {  // the Esc key
                curs_set(1);
                clear();
                refresh();
                endwin();
                break;
            };
        };

        curs_set(1);
        refresh();
        clear();        
        endwin();         
        return 0;
    };

    void InputForm::saveValues()
    {
        values = inValues;
    };

    void InputForm::printValues()
    {
        std::cout << "Input result: \n";
        for (size_t i = 0; i < values.size(); i++)
        {            
            std::cout << values.at(i).first << ": " << values.at(i).second << "\n";            
        };
        std::cout << "------------------------------\n";
    };

    std::vector<std::pair<std::string, std::string>> InputForm::getValues()
    {
        return values;
    };
//};

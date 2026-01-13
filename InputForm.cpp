#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>
#include <locale>

#include "InputForm.h"

// class InputForm
// {
// private:
//     std::vector<std::pair<std::string, std::string>> values;
    // struct Field
    // {
    //     int sKeyY=0;
    //     int sKeyX=0;
    //     int sValY=0;
    //     int sValX=0;
    // };
    // std::vector<Field> fields;    
            //  box                         1
        //  header                      2
        //  ----------------------------3
        //  column names "key", "value" 4
        // -----------------------------5
        //  key "OK", "ESC"                // lines - 1
        // -----------------------------   // lines
        // + each field * 2

        //WINDOW* stdscr;

// public:
//     InputForm(/* args */);
//     ~InputForm();

    int InputForm::importKeys(std::vector<std::pair<std::string, std::string>> inValues)
    {
        values=inValues;
        return 0;
    };

    void InputForm::definingFields()
    {
        //  box                         1
        //  header                      2
        //  ----------------------------3
        //  column names "key", "value" 4
        // -----------------------------5
        //  key "OK", "ESC"             6   // lines - 1
        // -----------------------------7   // lines
        // + each field * 2
        //size_t i = 0; +6

        attron(COLOR_PAIR(5));
        //mvaddstr(2, 20,  "DATA ENTRY FORM");
        mvaddstr(0, 20,  "  DATA ENTRY FORM  ");
        mvaddstr(2, 4,  "   key");
        mvaddstr(2, 20, "   value");

        //attron(COLOR_PAIR(3));
        for (size_t x = 4; x < 70; x++)
        {
            mvwaddch(stdscr, 1, x, ACS_HLINE);  // Горизонтальная линия 
            mvwaddch(stdscr, 3, x, ACS_HLINE);  // Горизонтальная линия 
        };

        mvwaddch(stdscr, 2,  3, ACS_VLINE);  // Вертикальная линия слева
        mvwaddch(stdscr, 2, 19, ACS_VLINE);  // Вертикальная линия в середине
        mvwaddch(stdscr, 2, 70, ACS_VLINE);  // Вертикальная линия справа
        mvwaddch(stdscr, 3,  3, ACS_VLINE);  // Вертикальная линия слева
        mvwaddch(stdscr, 3, 19, ACS_VLINE);  // Вертикальная линия в середине
        mvwaddch(stdscr, 3, 70, ACS_VLINE);  // Вертикальная линия справа

        // // Позиции полей ввода
        size_t i = 0;
        for ( i = 0; i <= values.size(); i++)
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
        for ( y = 0; y < values.size(); y++)
        {
            for (size_t x = 4; x < 70; x++)
            {
                mvwaddch(stdscr, fields.at(y).sKeyY+1, x, ACS_HLINE);  // Горизонтальная линия снизу
            };
        };

        y = 0;
        for ( y = 0; y < values.size()-1; y++)
        {
            mvwaddch(stdscr, fields.at(y).sKeyY,  3, ACS_VLINE);  // Вертикальная линия слева
            mvwaddch(stdscr, fields.at(y).sKeyY, 19, ACS_VLINE);  // Вертикальная линия в середине
            mvwaddch(stdscr, fields.at(y).sKeyY, 70, ACS_VLINE);  // Вертикальная линия справа
            mvwaddch(stdscr, fields.at(y).sKeyY+1, 3, ACS_VLINE);  // Вертикальная линия слева
            mvwaddch(stdscr, fields.at(y).sKeyY+1,19, ACS_VLINE);  // Вертикальная линия в середине
            mvwaddch(stdscr, fields.at(y).sKeyY+1,70, ACS_VLINE);  // Вертикальная линия справа
        };
        mvwaddch(stdscr, fields.at(y).sKeyY,  3, ACS_VLINE);  // Вертикальная линия слева
        mvwaddch(stdscr, fields.at(y).sKeyY, 19, ACS_VLINE);  // Вертикальная линия в середине
        mvwaddch(stdscr, fields.at(y).sKeyY, 70, ACS_VLINE);  // Вертикальная линия справа

        mvwaddch(stdscr, 1, 3, ACS_ULCORNER);
        mvwaddch(stdscr, 1, 70, ACS_URCORNER);
        mvwaddch(stdscr, fields.at(y).sKeyY+1,  3, ACS_LLCORNER);
        mvwaddch(stdscr, fields.at(y).sKeyY+1, 70, ACS_LRCORNER);
        attroff(COLOR_PAIR(5));
    };

    void InputForm::updateFields(int activeField)
    {
        //  box                         1
        //  header                      2
        //  ----------------------------3
        //  column names "key", "value" 4
        // -----------------------------5
        //  key "OK", "ESC"                // lines - 1
        // -----------------------------   // lines

        size_t i = 0;
        for ( i = 0; i < values.size(); i++)
        {
            mvaddstr(fields.at(i).sKeyY, fields.at(i).sKeyX, values.at(i).first.c_str());
        };
            
        i = 0;
        for ( i = 0; i < values.size(); i++)
        {           
            if (i==activeField)
            {
                attron(COLOR_PAIR(7));
                mvaddstr(fields.at(i).sValY, fields.at(i).sValX, "                                                  ");  // Очищаем место под ID
                mvprintw(fields.at(i).sValY, fields.at(i).sValX, "%s", values.at(i).second.c_str());   //         
                attroff(COLOR_PAIR(7));  
            }else{
                attron(COLOR_PAIR(5));
                mvaddstr(fields.at(i).sValY, fields.at(i).sValX, "                                                  ");  // Очищаем место под ID
                mvprintw(fields.at(i).sValY, fields.at(i).sValX, "%s", values.at(i).second.c_str());   //         
                attroff(COLOR_PAIR(5));  
            };
            

        };        

        attron(COLOR_PAIR(8));
        mvaddstr(fields.at(i).sKeyY, fields.at(i).sKeyX, "< OK (ENTER) >"  );
        mvaddstr(fields.at(i).sValY, fields.at(i).sValX, "< CANCEL(ESC) >");
        attroff(COLOR_PAIR(8));
    };



    int InputForm::runInputForm(std::vector<std::pair<std::string, std::string>> inValues)
    {
        importKeys(inValues);

        //setlocale(LC_ALL, "ru_RU.UTF-8") ; 
        setlocale(LC_ALL, "") ; 
        stdscr = initscr();            // инициализация ncurses
        // Получаем размеры окна
        int height, width;
        getmaxyx(stdscr, height, width);
        int reqHeight= values.size()*2 + 7;
        if (reqHeight>height)
        {
            std::cout << "This form requires a large window height (units" << reqHeight << ").\n";
            std::cout << "Current window height: " << height << ".\n";
            return -1;
        };        

        cbreak();            // режим без буферизации
        raw();               // режим raw для корректного ввода
        noecho();           // не отображать вводимые символы
        curs_set(0);        // скрыть курсор
        keypad(stdscr, TRUE); // включить обработку клавиш

        start_color();      // инициализация цветов
        // init_pair(1, COLOR_GREEN, COLOR_BLACK); // зеленый текст на черном фоне
        // init_pair(2, COLOR_BLUE, COLOR_BLACK); // Синий
        // init_pair(3, COLOR_CYAN, COLOR_BLACK); // Голубой
        // init_pair(4, COLOR_RED, COLOR_BLACK);  // Красный
        init_pair(5, COLOR_WHITE, COLOR_BLUE); // белый текст на синем ФОН
        init_pair(6, COLOR_WHITE, COLOR_GREEN); // белый текст на зеленом
        init_pair(7, COLOR_WHITE, COLOR_BLACK); // белый текст на черном  ПОЛЯ 
        init_pair(8, COLOR_BLACK, COLOR_CYAN); // КНОПКИ

        attron(COLOR_PAIR(5));
        box(stdscr, ACS_VLINE, ACS_HLINE);
        //box(stdscr, 0, 0);             // рамка вокруг окна
        mvwaddch(stdscr, 0, 0, ACS_ULCORNER);
        mvwaddch(stdscr, 0, COLS-1, ACS_URCORNER);
        mvwaddch(stdscr, LINES-1, 0, ACS_LLCORNER);
        mvwaddch(stdscr, LINES-1, COLS-1, ACS_LRCORNER);
        attroff(COLOR_PAIR(5));

        wbkgd(stdscr, COLOR_PAIR(5) | ' ');     // Установка фона окна

        //wrefresh(stdscr)
        //refresh();

        definingFields();        
        
        // Текущее активное поле
        int activeField = 0; // 0 - ID, 1 - Name, 2 - Age
        
        // Основной цикл обработки ввода
        while (true) {

            updateFields(activeField);
            wrefresh(stdscr);
            refresh();
            
            // for (size_t i = 0; i < fields.size(); i++)
            // {
            //     attron(COLOR_PAIR(1));  // Включаем зеленый цвет
            //     if (i==activeField)
            //     {
            //         mvaddch(fields.at(i).sValY, fields.at(i).sValX - 2, '>');  // Помечаем стрелкой
            //     }else{
            //         mvaddch(fields.at(i).sValY, fields.at(i).sValX - 2, ' ');  // Помечаем стрелкой
            //     };
            //     attroff(COLOR_PAIR(1));  // Отключаем цвет                
            // };                        
            // refresh();  // Обновляем экран
            
            int ch = getch();  // Получаем нажатую клавишу
            
            if (ch==KEY_DOWN)
            {
                activeField = (activeField + 1) % fields.size();
            }else if (ch==KEY_UP)
            {
                activeField = (activeField - 1) % fields.size();
            };
            
            if (ch==10)   // Обработка нажатия Enter
            {
                
            };

            if (ch == KEY_BACKSPACE || ch == 127) {  // Обработка Backspace
                if (activeField<values.size()) {
                    std::string value=values.at(activeField).second;
                    if (!value.empty()){
                        value.pop_back();
                        values.at(activeField).second=value;
                    };
                };
            };
    
            if (isprint(ch)) {  // Если нажата печатная клавиша
                if (activeField<values.size()) {
                    std::string value=values.at(activeField).second;
                    value += ch;
                    values.at(activeField).second=value;
                };
            };

            if (ch == 27) {  // handle Esc
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

    void InputForm::printValues()
    {
        std::cout << "Input result: \n";
        for (size_t i = 0; i < values.size(); i++)
        {            
            std::cout << values.at(i).first << ": " << values.at(i).second << "\n";            
        };        
        //std::cout << "result: ID: " << idStr << ", Object: " << objectStr << ", Indicator: " << indicatorStr << ", Period: " << periodStr << ", Value: " << valueStr << ".\n";
        std::cout << "------------------------------\n";
    };

    std::vector<std::pair<std::string, std::string>> InputForm::getValues()
    {
        return values;
    };
//};

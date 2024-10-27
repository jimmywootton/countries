#include <iostream>
#include <string>
#include <ncurses.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype> // for isalpha


using namespace std;

int main() 
{
    ifstream countriesInput("countries.txt");
    ifstream capitalsInput("capitals.txt");
    string countryString;
    string capitalString;
    vector<string> countries;
    vector<string> capitals;
    while (getline(countriesInput, countryString)) 
    {
        getline(capitalsInput, capitalString);
        countries.push_back(countryString);
        capitals.push_back(capitalString);
    }
    countriesInput.close();
    capitalsInput.close();



    initscr(); // Initialize ncurses
    cbreak(); // Line buffering disabled, Pass on everything to me
    noecho(); // Don't echo() while we do getch
    keypad(stdscr, TRUE);

    while (!countries.empty())
    {
        printw(countries.front().c_str());
        string capitalLowerCase = capitals.front();
        capitalLowerCase.at(0) = tolower(capitalLowerCase.at(0));
        printw("\n");
        string input;
        bool stay = true;
        while (stay) 
        {
            int ch = getch(); // Get a character
            if (ch == 127) 
            { // If Backspace is pressed (ASCII value 8 or 127)
                if (!input.empty()) 
                {
                    input.pop_back(); // Remove last character
                    printw("\b \b"); // Move cursor back, erase character, move cursor back again
                    refresh();
                }
            } 
            if (isalpha(ch))
            {
                input += ch;
                printw("%c", ch); // Print the typed character
                refresh();
            }
            
            if (input == capitalLowerCase)
            {
                countries.erase(countries.begin());
                capitals.erase(capitals.begin());
                stay = false;
            }
            
            if (ch == KEY_RIGHT)
            {
                rotate(countries.begin(), countries.begin() + 1, countries.end());
                rotate(capitals.begin(), capitals.begin() + 1, capitals.end());
                stay = false;
            }
            if (ch == KEY_LEFT)
            {
                rotate(countries.rbegin(), countries.rbegin() + 1, countries.rend());
                rotate(capitals.rbegin(), capitals.rbegin() + 1, capitals.rend());
                stay = false;
            }
            if (ch == KEY_UP || ch == KEY_DOWN)
            {
                swap(countries, capitals);
                stay = false;
            }
        }
        move(getcury(stdscr) - 1, 0); // Move to the line with "Country"
        clrtoeol(); // Clear that line
        move(getcury(stdscr) - 1, 0); // Move to the line with "Type the capital"
        clrtoeol(); // Clear that li
        clear();
    }

    endwin(); // End ncurses mode
    return 0;
}

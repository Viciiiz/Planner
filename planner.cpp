#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

/**
 * A simple program to build a planner for the day. The user will enter the hours and their plan for the day,
 * and the program will write to a file and format a planner for the day.
 */


/**
 * Create a .txt file in the project folder.
 */
void fileCreator()
{
    fstream file;
    file.open("Planner.txt",ios::out);
    if(!file){
        cout << "Error in creating Planner.txt file." << endl;
    }
}


/**
 * Write (append) to a file.
 * @param s is the string that will be added to the file.
 */
void fileWriter(string s)
{
    fstream file;
    file.open("Planner.txt",ios::app);
    file << s;
}


/**
 * Read data from a file. 
 * @return the data from the file in a string
 */
string dataInFile()
{
    fstream file;
    file.open("Planner.txt",ios::in);
    string data = "";
    file >> data;
    return data;
}


/**
 * Separate a string by line and store each element in a vector.
 * @param s is the string to be separated.
 */
vector<string> list(string s)
{
    vector<string> output;
    auto str = std::stringstream {s};
    for (string line; std::getline(str, line, '\n');)
        output.push_back(line);

    return output;
}





int main ()
{
// create a file
// ask user input
// write the user input in the file


    return 0;
}
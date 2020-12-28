#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

/**
 * A simple program to build a planner for the day. The user will enter their plans for each hour of the day,
 * and the program will write to a file and format a planner for the day.
 * The user can: 
 * 1/ Create a new file
 * 2/ edit an existing file
 */


/**
 * Create a .txt file in the project folder.
 * @return the created file
 */
ofstream fileCreator()
{
    ofstream file;
    file.open("Planner.txt",ios::out);
    if(!file){
        cout << "Error in creating Planner.txt file." << endl;
    }
    return file;
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
    ifstream file;
    file.open("Planner.txt");
    string data;
    string output = "";
    
    while (!file.eof()){
        getline(file,data);
        if (data.length()>0){
            output.append(data + "\n");
        } 
    }
    file.close();
    return output;
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


/**
 * Vector containing the empty schedule
 * @return a vector containing a sample empty schedule
 */
vector<string> emptySchedule(){
    vector<string> empty;

    // AM time
    for (int i = 0; i < 12; i++){
        
        string from;
        if (i < 10){
            from = "From 0";
        } else {
            from = "From ";
        }

        string to;
        if (i + 1 < 10){
            to = "to 0";
        } else {
            to = "to ";
        }
        
        string am;
        if (i == 11){
            am = to_string(i) + ":59 AM => ";
        } else {
            am = to_string(i+1) + ":00 AM => ";
        }
        
        string currentTime = from + to_string(i) + ":00 " + to + am;
        empty.push_back(currentTime);
    }

    // PM time
    empty.push_back("From 12:00 to 01:00 PM => ");
    for (int i = 1; i < 11; i++){
        string from;
        if (i < 10){
            from = "From 0";
        } else {
            from = "From ";
        }
        string to;
        if (i + 1 < 10){
            to = "to 0";
        } else {
            to = "to ";
        }
        string currentTime = from + to_string(i) + ":00 " + to + to_string(i+1) + ":00 PM => ";
        empty.push_back(currentTime);
    }
    empty.push_back("From 11:00 to 11:59 PM => ");

    return empty;
}



// MAIN
int main ()
{
 
    // UI: create new schedule or not
    bool end = false;
    while (!end){
        cout << "New schedule? (yes / no / edit plan / quit)" << endl;
        string answer;
        getline(cin, answer);
        
        if (answer == "no" || answer == "quit")
        {
            cout << "--------end of program.-------";
            end = true;
        }
        else 
        {

            if (answer == "yes")
            {
                // create a new file
                ofstream file = fileCreator();
                
                // add header to file 
                fileWriter("TODAY'S SCHEDULE:\n\n");

                // ask what time the user starts their day
                cout << "\nStart time: (the first hour of your schedule) [enter a number from 1 to 24]: ";
                int startTime;
                cin >> startTime;
                
                // ask user's plan for each hour of the day, from the time they start to the end (24 hours plan).
                cout << "\nEnter plan: \n" << endl;
                vector<string> sample = emptySchedule(); // create sample empty schedule
                for (int i = 0 ; i < 24; i++){
                    cout << sample[startTime%24] + " " ;
                    string currentSchedule;

                    // append to file. Plan cannot be empty.
                    while (!currentSchedule.length()>0){
                        getline(cin, currentSchedule);
                    }
                    fileWriter(sample[startTime%24] + currentSchedule + "\n\n");
                    startTime++;

                }

                // add footer to file 
                fileWriter("\n\n~~~~END OF SCHEDULE~~~~\n"); 
                
                file.close();
                end = true;
            }
            // if the user wished to edit an existing file
            else if (answer == "edit plan")
            {
                // check if file exists
                ifstream file;
                file.open("Planner.txt");
                if(!file) 
                {
                    cout << "File doesn't exist" << endl;
                } else 
                {
                    cout << "File exists." << endl;

                    // read data from file
                    string dataFromFile = dataInFile();
                    vector<string> data = list(dataFromFile);
                    vector<string> empty = emptySchedule();

                    // ask user which hour they want to change
                    int input;
                    string index;
                    while (index != "100")
                    {
                        index = ""; 
                        cout << "\nWhich hour do you wish to edit ? [enter a number from 0 to 24] [enter '100' to exit]" << endl;
                        while (index.length()==0)
                        {
                            cin >> index;
                        }
                        input = stoi(index);
                        
                        // if valid input (other than '100')
                        if (input < 25 && input >= 0){
                            // first hour in the schedule
                            int firstHour = stoi(data[1].substr(5,2));
                            // find the hour that the user wishes to edit
                            input = (24 - firstHour + input)%25;
                
                            string toChange = data[input+1];
                            cout << "\nCurrent: " << toChange << endl;
                            cout << "New: " << empty [stoi(index)] << " ";
                            string newPlan;
                            while (newPlan.length() <= 0)
                            {
                                getline(cin, newPlan);
                            }
                            // change data in file
                            data[input+1] = data[input+1].substr(0,26);
                            data[input+1].append(newPlan); 

                        }
                        // if invalid input
                        else if (input != 100){
                            cout << "\nInvalid input" << endl;
                        }
                    } // end of while loop

                    // put everything back in the file
                    fileCreator(); // to overwrite
                    fileWriter("TODAY'S SCHEDULE:\n\n");
                    for (int i = 1 ; i < 25; i++)
                    {
                        fileWriter(data[i] + "\n\n");
                    }
                    fileWriter("\n\n~~~~END OF SCHEDULE~~~~\n");
                    
                }
            }
            else 
            {
                cout << "Invalid input\n" << endl;
            }
            
        }
    } // end of while loop 

} // main
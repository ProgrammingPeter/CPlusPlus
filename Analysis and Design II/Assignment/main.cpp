/************************************************************************
 Title         : main.cpp
 Author        : Peter Kamaris
 Created on    : February 13 2013
 Description   : Program is created to organize muscles and complete
		 action, strength, or diagnostic inquiries.
 Purpose       : Assignment1
 Build with    : g++ main.cpp
 *************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#include "Body.h"

string option();
//Menu
void choices();
//checks choices with user input
string lowercase(string user_input);
//Converts words to lowercase
void diagnostic();
//Pre Condition : Designed to take no values and be accessed when user wants a diagnosis
//Post Condition: Works out the entire diagnosis and returns nothing
void action();
//Pre : Designed to take no values and be accessed when user inquires about muscle actions
//Post : Asks the user what action of the muscle and works everything out and returns nothing
void strength();
//Pre : Designed to take no values and be accessed when user inquires about strength
//Post : Asks the user what muscles to strengthen and prints out the muscles

Body token; //Decided to make a global class of Body to be accessed in the functions.

using namespace std;

int main(int argc, char* argv[])
{
  vector <string> variables;
  //Vector of variables to be stored when reading the file
  string line;
  //Just a string to hold the incoming lines

ifstream thefile("muscles.csv"); //Opening the file with variable thefile

if (thefile.is_open()) //Attempting to open the file
{
    getline(thefile,line); //This line is inserted to skip the first line in the csv and save space

        while(thefile.good()) //Attempting to see if file works if opened
        {
            getline(thefile,line); //Intaking lines to string line from thefile
            int x = 0; //initialized at zero to start at the beginning of string and
                        //also changed back to zero for each loop not to have previous value
            int value; //this will take the number spot of where the comma is
            int counter = 0; //Same reason for x and to only take 5 variables from the first line

                while(counter <= 4)
                    {

                        value = line.find_first_of(","); //Finds spot of first comma and sends # to value
                        variables.push_back(line.substr(x, value)); //the variables vector is storing each word
                        line.erase(x, value+1); //This is to take the original line and delete what was stored
                        counter++;

                        if(variables.size()  == 5) //Once variables have taken the five words
                        {                          //They are inserted one by one to their respective sections
                            int i = 0; //The same reason for x

                                while(i < 5)
                                {
                                    if(i == 0)
                                    {
                                        token.set_muscle(variables[i]);
                                    }
                                    if(i == 1)
                                    {
                                        token.set_origin(variables[i]);
                                    }
                                    if(i == 2)
                                    {
                                        token.set_deep(variables[i]);
                                    }
                                    if(i == 3)
                                    {
                                        token.set_location(variables[i]);
                                    }
                                    if(i == 4)
                                    {
                                        token.set_action(variables[i]);
                                    }
                                    i++;
                                }
                            variables.clear(); //Cleared for the next line
                        }

                    }

        }
        thefile.close(); //closing file
}

    else cout << "Unable to open file" << endl; //self explanatory

choices();

return 0;
}
string option()
{
    string response;
    cout << "Which field would you like to inquire about?" << endl;
    cout << "\n";
    cout << "Action, Strength, or Diagnostic?" <<  endl;
    cout << "\n";
    cout << "If you would like to quit please enter Q or q" << endl;
    getline(cin, response);
    response = lowercase(response);//Convert response to lowercase
    return response;

}
void choices()
{

    bool verify = false;
    bool verify1 = false;

    do
    {
        string response = option();
        //Checks answer for one of the three options and the possibility of nothing
        if(response == "strength")
        {
            verify = true; //Changed to true if it enter this if statement
            strength();
        }

        if(response == "action")
        {
            verify = true;
            action();
        }

        if(response == "diagnostic")
        {
            verify = true;
            diagnostic();

        }
        if(response == "q")
        {
            verify1 = true; //for some reason whenever I choose to quit after calling one
            cout << "Goodbye." << endl;   //of the above functions it keeps returning to the previous function.
        }
        else if(verify == false || response.empty()) //If it hasnt entered either of the statements this will print
        {
            cout << "Your input was not recognized. Please check spelling." << "\n" << endl;
        }

    }while(verify1 == false);
}
string lowercase(string user_input)
{
    //This function was inteded for input purposes. If a user inputs something in capital
    //letters the program wont be able to recognize it. So I decided to make them all lower case
    for(int i = 0; i < user_input.size(); i++)
    {
        user_input[i] = tolower(user_input[i]); //Simply takes each spot of the word/s and converts them
    }
    //Since all the words in the .csv are lower case its better to change all inputs
    //to lowercase for comparison
    return user_input;
}
void diagnostic()
{
    string thatmuscle;
    bool test; //Created to see if input was equal to anything and if not to print error
    cout << "What muscle would you like to check?" << endl;
    getline(cin,thatmuscle);
    thatmuscle = lowercase(thatmuscle);

    for(int m = 0; m < token.get_muscle_size(); m++)
    {
         if(thatmuscle == token.get_muscle(m) )
         {
            test = 1; //Entire for loop is to check if anything is equal for the error print
         }
    }

    if(test == 0) //first checks if its an error and if not it proceeds to next for loop
    {
        cout << "Sorry your input was not recognized" << endl;
    }

    else
        for(int m = 0; m < token.get_muscle_size(); m++)
        {
            if(thatmuscle == token.get_muscle(m) )
            {
                if(token.get_deep(m) == "both") //simply being checked for grammatical purposes
                {
                    cout << "Possible pain for " << token.get_deep(m) << " " << token.get_location(m) << "s." << endl;
                }

                else
                cout << "Possible " << token.get_deep(m) << " " << token.get_location(m) << " pain." << endl; //Just for grammer
            }

        }

    cout << "\n" << endl;
}
void action()
{
            string thataction;
            bool tester = false;
            cout << "What action is involved?" << endl;
            getline(cin,thataction);
            thataction = lowercase(thataction);

            if(thataction.empty()) //Checking to see if user entered anything
            {
                cout << "Your input was not recognized." << endl;
            }

            for(int x = 0; x < token.get_action_size(); x++)
            {
                string tokenjr = token.get_action(x); //Inserts line to token
                int y = tokenjr.find_first_of(" "); //Takes number spot of where space
                int z = thataction.find_first_of(" "); //Same as above
                string compare1 = thataction.substr(0,z); //Taking substring from beginning to space
                string compare2 = tokenjr.substr(0,y); //Same as above

                if(compare1 < compare2) //Checks if the users input is shorter for imperative checking
                {
                    int difference = (compare2.length() - compare1.length()); //takes the difference

                    if(compare1 == compare2.substr(0,(compare2.length()- difference))) //To then make a substring and see if the words are the same
                    {
                        compare2 = token.get_action(x); //Takes the full entry
                        compare1 = thataction.substr(z+1, thataction.length()); //gets the next difference to compare
                        difference = (compare2.length() - compare1.length());

                        if(thataction.substr(z+1, thataction.length()) == compare2.substr(y+1,(compare2.length()- difference))) //Doing the same as before but now with both words
                        {
                            cout << "The " << token.get_muscle(x) << " muscle is involved." << endl;
                            tester = true; //Tester for error message
                        }
                    }
                }

                if(compare1 == compare2) //comparing the words to see if they are equal to move onto the next step
                {
                        if(thataction == token.get_action(x) ) //Since the first words equal it checks the entire line
                        {
                            cout << "The " << token.get_muscle(x) << " muscle is involved." << endl;
                            tester = true; //Tester for error message
                        }
                }
            }

            if(tester == false) //Mentioned above
            {
                cout << "Sorry there is no match." << endl;
            }

     cout << "\n";
}
void strength()
{
        string strengthen;
        cout << "Which muscle would you like to strengthen?" << endl;
        getline(cin,strengthen);
        strengthen = lowercase(strengthen);

        int space_begin; //To store the spot of first space
        space_begin = strengthen.find_first_of(" ");
        strengthen = strengthen.substr(space_begin+1, strengthen.length()); //takes substring from word after space to the end

        int thecounter = 0;
        string sentence;
        for(int place = 0; place < token.get_location_size(); place++)
        {
            if(strengthen == token.get_location(place))
            {                         //This for loop is created to get the second to last place
                thecounter = place;   //for grammer purposes in the next for loop
            }
        }

        if(thecounter == 0 || strengthen.empty()) //Checks here for errors instead of second
        {                                          //loop because it ran it the first time checking for matches
            cout << "Sorry your input was not recognized." <<endl;
            return;
        }

        for(int place = 0; place < token.get_location_size(); place++)
        {
            if(place == 0) //To start the sentence off
                {
                    sentence.append("Work on the following muscles: ");
                }
                    if(strengthen == token.get_location(place) )
                    {
                        if(thecounter == place) //thecounter was created to keep track of how many
                        {                       //matches there were so the program can add the "and " part for grammer
                            sentence.append("and ");
                        }

                        sentence.append(token.get_muscle(place));//These two are added to create sentence with proper structure
                        sentence.append(", ");

                    }
                    if(place == token.get_location_size()-1)
                    {
                        cout << sentence.substr(0, sentence.length()-2) << "." << endl; //Last two characters to be deleted because they are ", "
                    }
        }
        //cout << sentence.substr(0, sentence.length()-2) << "." << endl; //Last two characters to be deleted because they are ", "
    cout << "\n";
}


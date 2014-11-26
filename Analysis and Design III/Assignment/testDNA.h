/************************************************************************
 Title         : testDNA.h
 Author        : Peter Kamaris
 Created on    : Oct 14 2013
 Description   : Implement another class to insert into the trees
 Purpose       : Assignment2
 Build with    : g++ testDNA.h
 *************************************************************************/
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>


using namespace std;

class DNA{
public:
    DNA();
    DNA(string seq);
    DNA(string seq, string enzyme);
    friend ostream& operator << (ostream& out, const DNA test);
    bool operator<(const DNA other)
    {

        if(DNA_sequence < other.DNA_sequence)
            return true;
        else
            return false;
    };

    bool operator==(DNA other){

        if(DNA_sequence == other.DNA_sequence){
                return true;
        }
        else
            return false;
    };


    void addEnzyme(DNA other){
        if(DNA_enzymes.size() > 0)
            other.DNA_enzymes.push_back(DNA_enzymes[0]);

        if(other.DNA_enzymes.size() > 0)
            DNA_enzymes.push_back(other.DNA_enzymes[0]);
    }

    void Printenzymes(){

        for(int x = 1; x < DNA_enzymes.size(); x++){

            cout << endl;
            cout << DNA_enzymes[x] << endl;
        }
        cout << endl;
        cout << "These are the enzymes." << endl;
    }
private:
    string DNA_sequence;
    vector<string> DNA_enzymes;


};

DNA::DNA(){
};

DNA::DNA(string seq){

    DNA_sequence = seq;

}

DNA::DNA(string enzyme, string seq){

        DNA_enzymes.push_back(enzyme);
        DNA_sequence = seq;
}


ostream& operator << (ostream& out, const DNA test){

        for(int x = 0; x < test.DNA_enzymes.size(); x++){
            out << test.DNA_enzymes[x] << " & ";
        }
        out << " are the enzymes and the sequence is " << test.DNA_sequence << endl;
        return out;
}

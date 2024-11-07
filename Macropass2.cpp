#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Define data structures
struct MNTEntry {
    string name;
    int mdtIndex;
};

struct MDTEntry {
    int index;
    string definition;
};

// Sample MNT and MDT from Pass 1
vector<MNTEntry> mnt;
vector<MDTEntry> mdt;

// Initialize MNT and MDT
void initialize() {
    mnt.push_back((MNTEntry){"M1", 1});
    
    mdt.push_back((MDTEntry){1, "L 1,&ARG1"});
    mdt.push_back((MDTEntry){2, "A 1,&ARG2"});
    mdt.push_back((MDTEntry){3, "ST 1,&ARG1"});
    mdt.push_back((MDTEntry){4, "MEND"});
}

// Function to split a string by a delimiter
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to expand a macro call
void expandMacro(const string &macroCall, vector<string> &expandedOutput) {
    istringstream ss(macroCall);
    string macroName;
    getline(ss, macroName, ' ');
    string argsStr;
    getline(ss, argsStr);
    
    vector<string> args = split(argsStr, ',');
    
    // Find the macro definition in MNT
    int macroStart = -1;
    for (size_t i = 0; i < mnt.size(); ++i) {
        if (mnt[i].name == macroName) {
            macroStart = mnt[i].mdtIndex;
            break;
        }
    }
    
    // Expand macro by iterating through MDT
    for (size_t i = macroStart - 1; i < mdt.size(); ++i) {
        if (mdt[i].definition == "MEND") break;
        
        string line = mdt[i].definition;
        for (size_t j = 0; j < args.size(); ++j) {
            string placeholder = "&ARG" + static_cast<ostringstream*>( &(ostringstream() << (j + 1)) )->str();
            size_t pos = 0;
            while ((pos = line.find(placeholder, pos)) != string::npos) {
                line.replace(pos, placeholder.length(), args[j]);
                pos += args[j].length();
            }
        }
        expandedOutput.push_back(line);
    }
}

// Main function to process input data for Pass 2
int main() {
    initialize();
    
    const char* inputLinesArr[] = {
        "START",
        "M1 DATA1,COMPUTER",
        "L 2,K",
        "M1 SYSTEM,PROGRAMMING",
        "S 1,PROGRAM",
        "M1 Y,D",
        "M 1,J",
        "END"
    };
    vector<string> inputLines(inputLinesArr, inputLinesArr + sizeof(inputLinesArr) / sizeof(inputLinesArr[0]));
    
    vector<string> expandedOutput;
    
    for (size_t i = 0; i < inputLines.size(); ++i) {
        string line = inputLines[i];
        string token = line.substr(0, line.find(' '));
        
        bool isMacroCall = false;
        for (size_t j = 0; j < mnt.size(); ++j) {
            if (token == mnt[j].name) {
                expandMacro(line, expandedOutput);
                isMacroCall = true;
                break;
            }
        }
        
        if (!isMacroCall) {
            expandedOutput.push_back(line);
        }
    }
    
    // Print the expanded output
    cout << "\nExpanded Source Code:" << endl;
    for (size_t i = 0; i < expandedOutput.size(); ++i) {
        cout << expandedOutput[i] << endl;
    }
    
    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct CodeLine {
    string label;
    string opcode;
    string operand1;
    string operand2;
};

vector<CodeLine> initializeCode() {
    vector<CodeLine> code;
    code.push_back((CodeLine){"PRG1", "START", "", ""});
    code.push_back((CodeLine){"", "USING", "*", "15"});
    code.push_back((CodeLine){"", "L", "", ""});
    code.push_back((CodeLine){"", "A", "", ""});
    code.push_back((CodeLine){"", "ST", "", ""});
    code.push_back((CodeLine){"FOUR", "DC", "F", ""});
    code.push_back((CodeLine){"FIVE", "DC", "1F", ""});
    code.push_back((CodeLine){"TEMP", "DS", "1F", ""});
    code.push_back((CodeLine){"", "END", "", ""});
    return code;
}

void pass1(const vector<CodeLine>& code) {
    vector<int> lc(code.size(), 0);
    int loc = 0;

    cout << "--------------------------------------------------" << endl;
    cout << "LABEL\t\tOPCODE" << endl;
    cout << "--------------------------------------------------" << endl;

    // Display code table
    for (size_t i = 0; i < code.size(); ++i) {
        cout << code[i].label << "\t\t" << code[i].opcode << "\t\t"
             << code[i].operand1 << "\t\t" << code[i].operand2 << endl;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "\nVALUES FOR LC:\n" << endl;

    // Calculating LC values
    for (size_t j = 1; j < code.size(); ++j) {
        if (code[j].opcode != "START" && code[j].opcode != "USING" && code[j].opcode != "L") {
            lc[j] = lc[j - 1] + 4;
        }
        cout << lc[j] << "\t";
    }

    cout << "\n\nSYMBOL TABLE:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "SYMBOL\t\tVALUE\t\tLENGTH\t\tR/A" << endl;
    cout << "--------------------------------------------------" << endl;

    // Symbol table generation
    loc = 0;
    for (size_t i = 0; i < code.size(); ++i) {
        if (code[i].opcode == "START") {
            cout << code[i].label << "\t\t" << loc << "\t\t4\t\tR" << endl;
        } else if (!code[i].label.empty()) {
            cout << code[i].label << "\t\t" << loc << "\t\t4\t\tR" << endl;
            loc += 4;
        } else if (code[i].opcode == "USING") {
            // Placeholder if-statement for future logic
        } else {
            loc += 4;
        }
    }

    cout << "--------------------------------------------------" << endl;
}

int main() {
    vector<CodeLine> code = initializeCode();
    pass1(code);
    return 0;
}


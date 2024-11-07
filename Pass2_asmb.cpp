#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

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

void pass2(const vector<CodeLine>& code) {
    vector<string> avail(15, "N");
    vector<int> lc(code.size(), 0);
    lc[0] = 0;
    for (size_t i = 1; i < lc.size(); ++i) {
        lc[i] = lc[i-1] + 4;
    }

    cout << "\n\nBASE TABLE:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "REG NO\t\tAVAILABILITY\tCONTENTS OF BASE TABLE" << endl;
    cout << "--------------------------------------------------" << endl;

    // Base table setup
    string av;
    for (size_t i = 0; i < code.size(); ++i) {
        if (code[i].opcode == "USING") {
            av = code[i].operand2;
            break;
        }
    }

    // Ensure count_value is within the correct range (1-15)
    istringstream iss(av);
    int count_value;
    iss >> count_value;
    if (1 <= count_value && count_value <= 15) {
        avail[count_value - 1] = "Y";
    } else {
        cout << "Error: BASE value out of range." << endl;
    }

    for (size_t k = 0; k < avail.size(); ++k) {
        cout << k + 1 << "\t\t" << avail[k] << endl;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "Continue..??";
    cin.ignore();

    cout << "PASS2 TABLE:\n" << endl;
    cout << "LABEL\t\tOP1\t\tLC" << endl;
    cout << "--------------------------------------------------" << endl;

    // Display Pass2 table
    for (size_t i = 0; i < code.size(); ++i) {
        if (code[i].opcode == "START" || code[i].opcode == "USING") {
            continue;
        }
        cout << code[i].label << "\t\t" << code[i].opcode << "\t\t" << lc[i] << endl;
    }

    cout << "--------------------------------------------------" << endl;
}

int main() {
    vector<CodeLine> code = initializeCode();
    pass2(code);
    return 0;
}


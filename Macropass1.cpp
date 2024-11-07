#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

// Helper function to convert an integer to a string (C++98 replacement for std::to_string)
string intToString(int num) {
    ostringstream convert;
    convert << num;
    return convert.str();
}

int main() {
    // Sample input data
    string input_data =
        "MACRO\n"
        "M1\t&ARG1,&SYSTEM\n"
        "L\t1,#0\n"
        "A\t1,Y\n"
        "ST\t1,#1\n"
        "MEND\n"
        "START\n"
        "M1\tDATA1,COMPUTER\n"
        "L\t2,K\n"
        "M1\tSYSTEM,PROGRAMMING\n"
        "S\t1,PROGRAM\n"
        "M1\tY,D\n"
        "M\t1,J\n"
        "END\n";

    // Simulating file content as input stream
    istringstream f1(input_data);

    // Output data streams
    ostringstream mnt_table, mdt_table, output_file;

    string label, code, operand;
    int mntc = 1, mdtc = 1;
    vector<string> ala;
    int counter = 0, flag = 0;

    while (f1 >> label >> code >> operand) {
        if (code == "MACRO") {
            f1 >> label >> code >> operand;
            mnt_table << mntc << "\t" << label << "\t" << code << "\t" << operand << "\t" << mdtc << "\n";
            mdt_table << mdtc << "\t" << label << "\t" << code << "\t" << operand << "\n";
            mntc++;
            mdtc++;

            // Process ALA (Argument List Array)
            ala.clear();
            int i = 0;
            while (i < operand.size()) {
                if (operand[i] == '&') {
                    string arg;
                    i++;
                    while (i < operand.size() && operand[i] != ',') {
                        arg += operand[i++];
                    }
                    ala.push_back(arg);
                }
                i++;
            }

            // Reading macro definition
            while (code != "MEND") {
                f1 >> label >> code >> operand;

                // Substitute index notation from ALA
                i = 0;
                while (i < operand.size()) {
                    if (operand[i] == '&') {
                        string arg;
                        i++;
                        while (i < operand.size() && operand[i] != ',' && operand[i] != '\0') {
                            arg += operand[i++];
                        }

                        // Find the argument in ALA and replace it
                        vector<string>::iterator it = find(ala.begin(), ala.end(), arg);
                        if (it != ala.end()) {
                            int index = distance(ala.begin(), it);
                            operand.replace(operand.find('&' + arg), arg.size() + 1, "#" + intToString(index));
                        }
                    } else {
                        i++;
                    }
                }

                mdt_table << mdtc << "\t" << label << "\t" << code << "\t" << operand << "\n";
                mdtc++;
            }
        } else {
            output_file << label << "\t" << code << "\t" << operand << "\n";
        }
    }

    // Displaying the output content
    cout << "Output file:" << endl;
    cout << output_file.str() << endl;

    cout << "Mnt_table:" << endl;
    cout << mnt_table.str() << endl;

    cout << "Mdt_table:" << endl;
    cout << mdt_table.str() << endl;

    return 0;
}


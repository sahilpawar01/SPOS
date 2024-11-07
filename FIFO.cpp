
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int noofpages, capacity, index = 0;
    int hit = 0, fault = 0;
    double faultRatio, hitRatio;

    cout << "Enter the number of pages you want to enter: ";
    cin >> noofpages;
    vector<int> pages(noofpages);

    cout << "Enter the pages: ";
    for (int i = 0; i < noofpages; i++) {
        cin >> pages[i];
    }

    cout << "Enter the capacity of frame: ";
    cin >> capacity;
    vector<int> frame(capacity, -1);
    vector<vector<int>> table(noofpages, vector<int>(capacity));

    cout << "\n----------------------------------------------------------------------\n";
    for (int i = 0; i < noofpages; i++) {
        int search = -1;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                search = j;
                hit++;
                cout << " H";
                break;
            }
        }
        if (search == -1) {
            frame[index] = pages[i];
            fault++;
            cout << " F";
            index++;
            if (index == capacity) {
                index = 0;
            }
        }
        for (int j = 0; j < capacity; j++) {
            table[i][j] = frame[j];
        }
    }
    cout << "\n----------------------------------------------------------------------\n";
    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < noofpages; j++) {
            cout << table[j][i] << "  ";
        }
        cout << endl;
    }

    cout << "----------------------------------------------------------------------\n";
    faultRatio = ((double)fault / noofpages) * 100;
    hitRatio = ((double)hit / noofpages) * 100;
    cout << "Page Fault: " << fault << "\nPage Hit: " << hit << endl;
    printf("Hit Ratio: %.2f \nFault Ratio: %.2f\n", hitRatio, faultRatio);

    return 0;
}

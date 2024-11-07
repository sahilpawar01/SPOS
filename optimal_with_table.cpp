#include <bits/stdc++.h>
using namespace std;

// Function to check whether a page exists in a frame or not
bool search(int key, vector<int>& fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

// Function to find the frame that will not be used recently in future
int predict(int pg[], vector<int>& fr, int pn, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pn; j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        if (j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    vector<int> fr;  // Frames
    int hit = 0;

    cout << left << setw(10) << "Page" << setw(10) << "Result" << "Frames\n";
    cout << "----------------------------------\n";

    for (int i = 0; i < pn; i++) {
        bool isHit = search(pg[i], fr);  // Check if it's a hit or miss

        if (isHit) {
            hit++;
            cout << setw(10) << pg[i] << setw(10) << "Hit";
        } else {
            if (fr.size() < fn) {
                fr.push_back(pg[i]);  // Add page to frames if space available
            } else {
                int j = predict(pg, fr, pn, i + 1);  // Find page to replace
                fr[j] = pg[i];
            }
            cout << setw(10) << pg[i] << setw(10) << "Miss";
        }

        // Display current frame state
        for (int frame : fr)
            cout << frame << " ";
        cout << "\n";
    }
    
    cout << "\nNo. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}

// Driver Function
int main()
{
    int pg[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 };
    int pn = sizeof(pg) / sizeof(pg[0]);
    int fn = 4;
    optimalPage(pg, pn, fn);
    return 0;
}

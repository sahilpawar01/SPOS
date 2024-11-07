#include <bits/stdc++.h>
using namespace std;

// Function to find and display page faults and frames at each step
int pageFaults(vector<int>& pages, int n, int capacity) 
{ 
    unordered_set<int> s;        // Set to store pages in frames
    unordered_map<int, int> indexes; // Map to store the last used indexes of pages
    int page_faults = 0;         // Counter for page faults

    // Print table header
    cout << setw(10) << left << "Step" 
         << setw(10) << left << "Page" 
         << setw(20) << left << "Frames" 
         << setw(15) << left << "Page Fault?" << endl;

    for (int i = 0; i < n; i++) 
    { 
        bool isPageFault = false;

        // Check if set can hold more pages
        if (s.size() < capacity) 
        { 
            if (s.find(pages[i]) == s.end()) 
            { 
                s.insert(pages[i]);
                page_faults++;
                isPageFault = true;
            } 
            indexes[pages[i]] = i;
        } 
        else 
        { 
            if (s.find(pages[i]) == s.end()) 
            { 
                int lru = INT_MAX, val;
                for (auto it = s.begin(); it != s.end(); it++) 
                { 
                    if (indexes[*it] < lru) 
                    { 
                        lru = indexes[*it]; 
                        val = *it; 
                    } 
                } 
                s.erase(val);
                s.insert(pages[i]);
                page_faults++;
                isPageFault = true;
            } 
            indexes[pages[i]] = i;
        }

        // Print the current step details
        cout << setw(10) << left << i+1;              // Step number
        cout << setw(10) << left << pages[i];         // Current page
        cout << "[";                                  // Frame content
        for (auto it = s.begin(); it != s.end(); ) 
        {
            cout << *it;
            if (++it != s.end()) cout << ", ";
        }
        cout << "]";

        cout << setw(20 - s.size() * 3) << "";        // Adjust spacing for alignment
        cout << setw(15) << (isPageFault ? "Yes" : "No") << endl; // Page fault status
    }

    // Print total page faults
    cout << "\nTotal Page Faults: " << page_faults << endl;
    return page_faults; 
} 

// Driver code 
int main() 
{ 
    int n, capacity;

    cout << "Enter the number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page sequence: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter the capacity of frames: ";
    cin >> capacity;

    cout << "\nPage Fault Analysis:\n";
    pageFaults(pages, n, capacity);
    return 0; 
}

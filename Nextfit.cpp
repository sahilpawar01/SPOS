#include <iostream>
#include <vector>
using namespace std;

// Function to allocate memory to blocks as per Next Fit algorithm
void NextFit(vector<int>& blockSize, int m, vector<int>& processSize, int n) {
    // Stores block id of the block allocated to a process
    // Initially no block is assigned to any process
    vector<int> allocation(n, -1);
    int j = 0;
    int t = m - 1;

    // Pick each process and find suitable blocks according to its size and assign to it
    for (int i = 0; i < n; i++) {
        // Do not start from beginning
        while (j < m) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to p[i] process
                allocation[i] = j;
                
                // Reduce available memory in this block
                blockSize[j] -= processSize[i];
                
                // Set a new end point
                t = (j - 1 + m) % m;
                break;
            }
            if (t == j) {
                // Set a new end point
                t = (j - 1 + m) % m;
                // Break the loop after going through all memory blocks
                break;
            }
            
            // Mod m will help in traversing the blocks from starting block after we reach the end
            j = (j + 1) % m;
        }
    }

    cout << "Process No.\tProcess Size\tBlock no." << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "\t" << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1 << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

// Driver Code
int main() {
    int blockArr[] = {5, 10, 20};
    int processArr[] = {10, 20, 5};
    
    vector<int> blockSize(blockArr, blockArr + 3);
    vector<int> processSize(processArr, processArr + 3);

    int m = blockSize.size();
    int n = processSize.size();

    NextFit(blockSize, m, processSize, n);

    return 0;
}


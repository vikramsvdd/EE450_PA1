#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the parity bit for a column
int calculateColumnParity(vector<vector<int>>& data, int col) {
    int colparitybit = 0;
    for (int i = 0; i < data.size(); i++) {
        colparitybit ^= data[i][col];
    }
    return colparitybit;
}

// Function to calculate the parity bit for a row
int calculateRowParity(vector<vector<int>>& data, int row) {
    int rowparitybit = 0;
    for (int i = 0; i < data[row].size(); i++) {
        rowparitybit ^= data[row][i];
        
}
    return rowparitybit;
}


int main() {
    int numRows, numCols;

    cout << "Enter the number of rows: ";
    cin >> numRows;
    cout << "Enter the number of columns: ";
    cin >> numCols;

    // Initialize the 2D data array
    vector<vector<int>> data(numRows, vector<int>(numCols));
    vector<int> colparityrowvect(data[0].size());

    // Input the data
    cout << "Enter the data (0 or 1) row by row:" << endl;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            cin >> data[i][j];
        }
    }

    

    // Calculate and display column parity bits
    cout << "Col: ";
    for (int i = 0; i < data[0].size(); i++) {
        int colparitybit = calculateColumnParity(data, i);
        colparityrowvect[i] = colparitybit;
        cout<<colparitybit<<"";
        
    }
    cout<<endl;
    data.push_back(colparityrowvect);
    

    // Calculate and display row parity bits
    cout<< "Row: ";
    for (int i = 0; i < data.size(); i++) {
        int rowparitybit = calculateRowParity(data,i);
        cout<<rowparitybit<<"";
    }
    cout<<endl;
    data.pop_back();
  
    
    return 0;
}

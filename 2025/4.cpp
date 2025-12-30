#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <string>
#include <numeric>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <limits>
#include <limits.h>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <random>
#include <deque>
using namespace std;

int countAndMarkRemovable(vector<string>& adat, bool mark = true) {
    int countLocal = 0;
    for (int i = 0; i<adat.size(); i++) {
        for (int j = 0; j<adat[0].size(); j++) {
            if (adat[i][j] == '@') {
                int db = 0;
                
                if (i>0 && (adat[i-1][j] == '@' || adat[i-1][j] == 'x')) db++;
                if (i<adat.size()-1 && (adat[i+1][j] == '@' || adat[i+1][j] == 'x')) db++;
                if (j>0 && (adat[i][j-1] == '@' || adat[i][j-1] == 'x')) db++;
                if (j<adat[0].size()-1 && (adat[i][j+1] == '@' || adat[i][j+1] == 'x')) db++;
                if (i>0 && j>0 && (adat[i-1][j-1] == '@' || adat[i-1][j-1] == 'x')) db++;
                if (i>0 && j<adat[0].size()-1 && (adat[i-1][j+1] == '@' || adat[i-1][j+1] == 'x')) db++;
                if (i<adat.size()-1 && j>0 && (adat[i+1][j-1] == '@' || adat[i+1][j-1] == 'x')) db++;
                if (i<adat.size()-1 && j<adat[0].size()-1 && (adat[i+1][j+1] == '@' || adat[i+1][j+1] == 'x')) db++;
                
                if (db<4) {
                    countLocal++;
                    if (mark)
                        adat[i][j] = 'x';
                    //cout << "(" << i << "," << j << ")" << endl;
                }
            }
        }
    }
    return countLocal;
}

void removeRemovable(vector<string>& adat) {
    for (int i = 0; i<adat.size(); i++) {
        for (int j = 0; j<adat[0].size(); j++) {
            if (adat[i][j] == 'x') adat[i][j] = '.';
        }
    }
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    vector<string> adat;
    
    while (!be.eof()) {
        string s;
        getline(be,s);
        adat.push_back(s);
    }
    // 1. feladat
    count = countAndMarkRemovable(adat, false);
    // 2. feladat
    int toRemove;
    while ((toRemove = countAndMarkRemovable(adat)) > 0) {
        removeRemovable(adat);
        count2 += toRemove;
    }
    
    cout                            << endl
    << "==========================" << endl
    << "sum: " << count             << endl
    << "==========================" << endl;
    
    if (count2 != 0)
        cout
        << "sum2: " << count2           << endl
        << "==========================" << endl;
    
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stopTime - startTime);
    cout << "Execution time: " << duration.count()/1000.0/1000.0 << "s" << endl;
    
    be.close();
    return 0;
}


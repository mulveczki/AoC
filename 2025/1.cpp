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

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    string temp;
    int act = 50;
    while(!be.eof()) {
        int prev = act;
        getline(be, temp);
        int moves = stoi(temp.substr(1));
        if (temp[0] == 'R') {
            for (int i = 0; i<moves; i++) {
                act++;
                if(act==100) {
                    act = 0;
                    count2++;
                }
            }
        }
        if (temp[0] == 'L') {
            for (int i = 0; i<moves; i++) {
                act--;
                if (act == 0) {
                    count2++;
                }
                if(act==-1) {
                    act = 99;
                }
            }
        }
        if (act == 0) count++;
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


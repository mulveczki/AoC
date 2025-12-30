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
typedef long long ll;

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    string temp;
    vector<vector<string>> data;
    vector<string> data2;
    
    while (!be.eof()) {
        getline(be, temp);
        //cout << temp << endl;
        data2.push_back(temp);
        vector<string> s = split(temp, " ");
        for (int i = 0; i<s.size(); i++) {
            if (s[i] == "") {
                s.erase(s.begin()+i);
                i--;
            }
        }
        vector<string> sss;
        for (auto ss : s) {
            sss.push_back(ss);
        }
        data.push_back(sss);
    }
    
    // 1. feladat
    for (int i = 0; i<data[0].size(); i++) {
        ll locSum;
        if (data[data.size()-1][i] == "+") {
            locSum = 0;
            for (int j = 0; j<data.size()-1; j++) {
                locSum += stoll(data[j][i]);
            }
        }
        else if (data[data.size()-1][i] == "*") {
            locSum = 1;
            for (int j = 0; j<data.size()-1; j++) {
                locSum *= stoll(data[j][i]);
            }
        }
        count += locSum;
    }
    
    // 2. feladat
    bool multiply;
    ll locSum = 0;
    for (int i = 0; i<data2[0].size(); i++) {
        bool emptyColumn = true;
        for (int j = 0; j<data2.size(); j++) {
            if (data2[j][i] != ' ') {
                emptyColumn = false;
            }
        }
        if (!emptyColumn) {
            // set multiply by last row
            if (data2[data2.size()-1][i] == '+') {
                multiply = false;
                count2 += locSum;
                locSum = 0;
            } else if (data2[data2.size()-1][i] == '*') {
                multiply = true;
                count2 += locSum;
                locSum = 1;
            }
            
            // decode the number
            string num = "";
            for (int j = 0; j<data2.size()-1; j++) {
                if (data2[j][i] != ' ')
                    num += data2[j][i];
            }
            if (multiply) locSum *= stoll(num);
            else locSum += stoll(num);
            
        }
    }
    count2 += locSum;
    
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


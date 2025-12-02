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

bool isRepeated(string szam, int parts) {
    int n = szam.length();
    string s1 = szam.substr(0,n/parts);
    for (int i = 0; i < parts-1; i++) {
        string s2 = szam.substr((i+1)*n/parts,n/parts);
        if (s1 != s2) return false;
    }
    return true;
}

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    string temp;
    getline(be, temp);
    vector<string> ranges = split(temp, ",");
    for (string range : ranges) {
        vector<string> fromTo = split(range, "-");
        long long from = stoll(fromTo[0]);
        long long to = stoll(fromTo[1]);
        for (long long i = from; i<=to; i++) {
            string szam = to_string(i);
            for (int j = 2; j<=szam.length(); j++) {
                if (szam.length()%j == 0 && isRepeated(szam, j)) {
                    if (j == 2) count += i;
                    count2 += i;
                    break;
                }
            }
        }
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
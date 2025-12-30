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

int main() {
    auto startTime = std::chrono::high_resolution_clock::now();
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    string temp;
    bool beforeEmptyLine = true;
    vector<pair<long long, long long>> ranges;
    vector<pair<long long, long long>> ranges_corrected;
    
    while (!be.eof()) {
        getline(be, temp);
        if (temp == "") {
            beforeEmptyLine = false;
            continue;
        }
        if (beforeEmptyLine) {
            auto rangeFromTo = split(temp, "-");
            long long actFrom = stoll(rangeFromTo[0]);
            long long actTo = stoll(rangeFromTo[1]);
            
            ranges.push_back({actFrom, actTo});
        }
        else {
            long long actId = stoll(temp);
            for (auto range : ranges) {
                if (actId>=range.first && actId <=range.second) {
                    count++;
                    break;
                }
            }
        }
    }
    
    
    // 2. feladat
    
    auto comp = [](pair<long long, long long> a, pair
                       <long long, long long> b) {
              return a.first < b.first;
        };

    // Sort the vector of pairs
    sort(ranges.begin(), ranges.end(), comp);
    
    for (auto r : ranges) {
        long long actFrom = r.first;
        long long actTo = r.second;
        bool found = false;
        for (int i = 0; i<ranges_corrected.size(); i++) {
            if (actFrom >= ranges_corrected[i].first && actFrom <= ranges_corrected[i].second) {
                found = true;
                if (actTo > ranges_corrected[i].second)
                    ranges_corrected[i].second = actTo;
            } else if (actTo >= ranges_corrected[i].first && actTo <= ranges_corrected[i].second) {
                found = true;
                if (actFrom < ranges_corrected[i].first)
                    ranges_corrected[i].first = actFrom;
            }
        }
        if (!found) ranges_corrected.push_back({actFrom, actTo});
    }
    
    for (auto rc : ranges_corrected)
        count2 += (rc.second - rc.first + 1) ;
    
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


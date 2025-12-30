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

typedef vector<int> Coord;

void handleConnection(pair<vector<int>, double>& idAndDist, vector<vector<int>>& groups) {
    int firstPlace = -1;
    int secondPlace = -1;
    
    for (int j = 0; j<groups.size(); j++) {
        for (int k = 0; k<groups[j].size(); k++) {
            if (groups[j][k] == idAndDist.first[0]) firstPlace = j;
            if (groups[j][k] == idAndDist.first[1]) secondPlace = j;
        }
    }
    
    if (firstPlace == -1 && secondPlace == -1) {
        vector<int> newGroup = {idAndDist.first};
        groups.push_back(newGroup);
    } else if (firstPlace > -1 && secondPlace == -1) {
        groups[firstPlace].push_back(idAndDist.first[1]);
    } else if (firstPlace == -1 && secondPlace > -1) {
        groups[secondPlace].push_back(idAndDist.first[0]);
    } else if (firstPlace != secondPlace) {
        vector<int> newGroup;
        newGroup.insert(newGroup.end(), groups[firstPlace].begin(), groups[firstPlace].end());
        newGroup.insert(newGroup.end(), groups[secondPlace].begin(), groups[secondPlace].end());
        
        if (firstPlace > secondPlace) {
            groups.erase(groups.begin()+firstPlace);
            groups.erase(groups.begin()+secondPlace);
        } else {
            groups.erase(groups.begin()+secondPlace);
            groups.erase(groups.begin()+firstPlace);
        }
        
        groups.push_back(newGroup);
    }
}

int main() {
    long long count = 0;
    long long count2 = 0;
    ifstream be("be.txt");
    
    vector<Coord> coords;
    vector<pair<vector<int>, double>> idsAndDist;
    vector<vector<int>> idGroups;
    vector<vector<int>> idGroups2;

    string temp;
    while (!be.eof()) {
        getline(be, temp);
        vector<string> coords_string_vec = split(temp, ",");
        coords.push_back({stoi(coords_string_vec[0]), stoi(coords_string_vec[1]), stoi(coords_string_vec[2])});
    }
    
    for (int i = 0; i<coords.size(); i++) {
        for (int j = 0; j<coords.size(); j++) {
            if (i != j && i < j) {
                ll dx = abs(coords[i][0] - coords[j][0]);
                ll dy = abs(coords[i][1] - coords[j][1]);
                ll dz = abs(coords[i][2] - coords[j][2]);
                double dist = sqrt(dx*dx + dy*dy + dz*dz);
                idsAndDist.push_back({{i, j}, dist});
            }
        }
    }
    
    auto comp = [](pair<vector<int>, double> a, pair<vector<int>, double> b) {return a.second < b.second;};
    sort(idsAndDist.begin(), idsAndDist.end(), comp);
    
    for (int i = 0; i<1000; i++) {
        handleConnection(idsAndDist[i], idGroups);
    }
    auto comp2 = [](vector<int> a, vector<int> b) {return a.size() > b.size();};
    sort(idGroups.begin(), idGroups.end(), comp2);
    
    int j = 0;
    do {
        handleConnection(idsAndDist[j++], idGroups2);
    } while (idGroups2[0].size() < coords.size());
    
    count =  idGroups[0].size() *  idGroups[1].size() *  idGroups[2].size();
    count2 = (ll)coords[idsAndDist[j-1].first[0]][0] * coords[idsAndDist[j-1].first[1]][0];
    
    cout                            << endl
    << "==========================" << endl
    << "sum: " << count             << endl
    << "==========================" << endl;
    
    if (count2 != 0)
        cout
        << "sum2: " << count2           << endl
        << "==========================" << endl;
    
    be.close();
    return 0;
}


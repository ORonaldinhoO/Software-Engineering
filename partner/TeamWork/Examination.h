//
// Created by Rush on 2021/10/20.
//

#ifndef TEAMWORK_EXAMINATION_H
#define TEAMWORK_EXAMINATION_H

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Examination {
 public:
  static int random(int max) {
    int val = rand()%(max);
    while (!val) val = rand()%(max);
    return val;
  }

  static vector<std::string> generate(int count, int maxNum, vector<string>& results);

 private:
  static unordered_map<int, char> operatorMap_; // ÔËËã·û 
};


#endif //TEAMWORK_EXAMINATION_H

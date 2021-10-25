//
// Created by Rush on 2021/10/20.
//

#include "Examination.h"
#include "Calculator.h"

unordered_map<int, char> Examination::operatorMap_ = {
        {1, '+'},
        {2, '-'},
        {3, 'x'},
        {4, '/'}
};  // 运算符 

// Examination::generate，生成count道数目运算题 
vector<std::string> Examination::generate(int count, int maxNum, vector<string>& results) {
  srand((int)time(0));
  // 用于判断结果是否重复 如果重复则重新生成
  unordered_set<string> checkResults;

  vector<std::string> examinations;
  for (int i = 0; i < count; i++) {
    // 生成本题目的运算符个数 最多3个
    int operatorCount = random(4);
    // 生成本题目分数个数
    int fractionCount = random(operatorCount + 2);
    // 分数所在位置的序列
    unordered_set<int> fractions;
    while (fractions.size() != fractionCount) {
      int fractionsIndex = random(operatorCount + 2) - 1;
      fractions.insert(fractionsIndex);
    }
    string curExamination;
    for (int j = 0; j < operatorCount + 1; j++) {
      // 本次需要插入的不是分数
      if (!fractions.count(j)) {
        curExamination += to_string(random(maxNum + 1));
      }
      else {
        curExamination += to_string(random(maxNum + 1)) + "/" + to_string(random(maxNum + 1));
      }
      // 最后一轮不需要再加操作运算符了
      if (j != operatorCount) {
        curExamination += " ";
        curExamination += operatorMap_[random(5)];
        curExamination += " ";
      }
    }
    // 对这一道题目求解 
    string examinationRes = Calculator::calculate(curExamination);
    // 查重
    bool flag = checkResults.count(examinationRes);
    // flag为true就重复了，不需要再次添加该题信息 
    if (flag) {
      i--;
      continue;
    }
    // 不重复则添加题目信息和对应答案 
    else {
      examinations.push_back(curExamination);
      checkResults.insert(examinationRes);
      results.push_back(examinationRes);
    }
  }
  return examinations;
}

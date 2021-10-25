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
};  // ����� 

// Examination::generate������count����Ŀ������ 
vector<std::string> Examination::generate(int count, int maxNum, vector<string>& results) {
  srand((int)time(0));
  // �����жϽ���Ƿ��ظ� ����ظ�����������
  unordered_set<string> checkResults;

  vector<std::string> examinations;
  for (int i = 0; i < count; i++) {
    // ���ɱ���Ŀ����������� ���3��
    int operatorCount = random(4);
    // ���ɱ���Ŀ��������
    int fractionCount = random(operatorCount + 2);
    // ��������λ�õ�����
    unordered_set<int> fractions;
    while (fractions.size() != fractionCount) {
      int fractionsIndex = random(operatorCount + 2) - 1;
      fractions.insert(fractionsIndex);
    }
    string curExamination;
    for (int j = 0; j < operatorCount + 1; j++) {
      // ������Ҫ����Ĳ��Ƿ���
      if (!fractions.count(j)) {
        curExamination += to_string(random(maxNum + 1));
      }
      else {
        curExamination += to_string(random(maxNum + 1)) + "/" + to_string(random(maxNum + 1));
      }
      // ���һ�ֲ���Ҫ�ټӲ����������
      if (j != operatorCount) {
        curExamination += " ";
        curExamination += operatorMap_[random(5)];
        curExamination += " ";
      }
    }
    // ����һ����Ŀ��� 
    string examinationRes = Calculator::calculate(curExamination);
    // ����
    bool flag = checkResults.count(examinationRes);
    // flagΪtrue���ظ��ˣ�����Ҫ�ٴ���Ӹ�����Ϣ 
    if (flag) {
      i--;
      continue;
    }
    // ���ظ��������Ŀ��Ϣ�Ͷ�Ӧ�� 
    else {
      examinations.push_back(curExamination);
      checkResults.insert(examinationRes);
      results.push_back(examinationRes);
    }
  }
  return examinations;
}

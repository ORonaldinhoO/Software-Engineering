//
// Created by Rush on 2021/10/20.
//

#include "Calculator.h"

 string Calculator::calculate(string text) {
  // ��һ����� Ĭ��Ϊ+
  char mark = '+';
  const vector<string>& texts = substring(text, ' ');
  stack<string> numStack;
  string fraction;
  string num;
  string result;
  // ѭ���ƽ��ı� 
  for (int i = 0; i < texts.size(); i++) {
    string cur = texts[i];
    if(stringIsNum(cur)) {
      num = cur + "/1";
    }
    // ����Ƿ���
    else if (cur.size() >= 3){
      num = cur;
    }
    // �������������ߵ���ĩβ
    if ((cur.size() == 1 && !stringIsNum(cur)) || i == texts.size() - 1) {
      switch (mark) {
        case '+': {
          numStack.push(num);
          break;
        }
        case '-': {
          numStack.push("-" + num);
          break;
        }
        case 'x': {
            multiplyFraction(num, numStack.top());
            numStack.pop();
            numStack.push(num);
          break;
        }
        case '/': {
          string temp = numStack.top();
          divideFraction(temp, num);
          numStack.pop();
          numStack.push(temp);
          break;
        }
        default: break;
      }
      mark = cur[0];
    }
  }
  // ��������ջ�����ͳһ��� 
  while (!numStack.empty()) {
    // cout << numStack.top() << endl;
    addFraction(result, numStack.top());
    numStack.pop();
  }

  simplyFraction(result);  // ���� 
  return result;
}

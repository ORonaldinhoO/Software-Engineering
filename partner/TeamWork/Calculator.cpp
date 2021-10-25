//
// Created by Rush on 2021/10/20.
//

#include "Calculator.h"

 string Calculator::calculate(string text) {
  // 上一运算符 默认为+
  char mark = '+';
  const vector<string>& texts = substring(text, ' ');
  stack<string> numStack;
  string fraction;
  string num;
  string result;
  // 循环推进文本 
  for (int i = 0; i < texts.size(); i++) {
    string cur = texts[i];
    if(stringIsNum(cur)) {
      num = cur + "/1";
    }
    // 如果是分数
    else if (cur.size() >= 3){
      num = cur;
    }
    // 如果是运算符或者到达末尾
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
  // 整理数据栈，最后统一相加 
  while (!numStack.empty()) {
    // cout << numStack.top() << endl;
    addFraction(result, numStack.top());
    numStack.pop();
  }

  simplyFraction(result);  // 化简 
  return result;
}

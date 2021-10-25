//
// Created by Rush on 2021/10/20.
//

#ifndef TEAMWORK_CALCULATOR_H
#define TEAMWORK_CALCULATOR_H

#include <string>
#include <unordered_map>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Calculator {
 public:
  static string calculate(string text);
 private:
  // 化简 
  static void simplyFraction(string& fraction) {
    vector<string> temp1 = substring(fraction, '/');  // 去除分号 
    string res;
    int m = stoi(temp1[0]), n = stoi(temp1[1]);
    int check = m / n;  // 以5/2为例 
    if (check >= 1) {
      res += to_string(check) + "'";
      m -= check * n;
    }
    if (m == 0)  {     // 如果除得尽，不需分数表示 
      fraction = to_string(check);
      return;
    }
    int gcd = getGcd(n, m);
    fraction = res;
    fraction += n / gcd == 1 ? to_string(m / gcd) : to_string(m / gcd) + "/" + to_string(n / gcd);  // 真分数形式的分数/带分数表示 
  }
  // 求余数 
  static int getGcd(int a,int b) {
    int r = a % b;
    if (r == 0)
      return b;

    while (r != 0) {
      r = a % b;
      a = b;
      b = r;
    }
    return a;
  }

  static void divideFraction(string& fraction, const string& cur) {
    if (!fraction.empty()) {
      // 更新分数
      doDivideFraction(fraction, cur);
    }
  }

  static void doDivideFraction(string& fraction1, const string& fraction2) {
    vector<string> temp2 = substring(fraction2, '/');
     doMultiplyFraction(fraction1, temp2[1] + "/" + temp2[0]);  // 转换成乘法 
  }

  static void multiplyFraction(string& fraction, const string& cur) {
    if (!fraction.empty()) {
      // 更新分数
      doMultiplyFraction(fraction, cur);
    }
  }

  static void doMultiplyFraction(string& fraction1, const string& fraction2) {
    vector<string> temp1 = substring(fraction1, '/');
    vector<string> temp2 = substring(fraction2, '/');
    // 分子
    int molecule1 = stoi(temp1[0]),molecule2 = stoi(temp2[0]);
    // 分母
    int denominator1 = stoi(temp1[1]), denominator2 = stoi(temp2[1]);
    int res1 = molecule1 * molecule2;
    int res2 = denominator1 * denominator2;
    fraction1 = to_string(res1) + "/" + to_string(res2);
  }

  static void addFraction(string& fraction, const string& cur) {
    if (!fraction.empty()) {
      // 更新分数
      doAddFraction(fraction, cur);
    }else {
      fraction = cur;
    }
  }

  static void doAddFraction(string& fraction1, const string& fraction2) {
    vector<string> temp1 = substring(fraction1, '/');
    vector<string> temp2 = substring(fraction2, '/');
    // 分子
    int molecule1 = stoi(temp1[0]),molecule2 = stoi(temp2[0]);
    // 分母
    int denominator1 = stoi(temp1[1]), denominator2 = stoi(temp2[1]);
    // 获得最小公倍数
    int multiple = getLeastCommonMultiple(denominator1, denominator2);
    int res = molecule1 * (multiple / denominator1) + molecule2 * (multiple / denominator2);
    fraction1 = to_string(res) + "/" + to_string(multiple);
  }
  // 获得最小公倍数
  static int getLeastCommonMultiple(int num1, int num2) {
    int cur1 = num1, cur2 = num2;
    int res;
    while ((cur1 %= cur2) && (cur2 %= cur1));
    res = num1 * num2 / (cur1 + cur2);
    return res;
  }

  static vector<string> substring(const string& text, char separator) {
    vector<string> res;
    string cur;
    for(int i = 0; i < text.size(); i++) {
      char ch = text[i];
      if (ch != separator) {
        cur += ch;
        if (i == text.size() - 1)
          res.push_back(cur);
      }
      else {
        res.push_back(cur);  // 不将separator推入至最后
        cur = "";  
      }
    }
    return res;
  }

  static bool stringIsNum(const string& text) {
    for (char c : text)
      if (!isdigit(c))  // 判断一个字符是否是十进制数字
        return false;
    return true;
  }

};


#endif //TEAMWORK_CALCULATOR_H

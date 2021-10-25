
#include <fstream>
#include "Examination.h"
#include "Calculator.h"
using namespace std;

// 将题目、题目结果保存 
void output(vector<string>& examinations, const vector<string>& results) {
  remove("./Exercises.txt");
  ofstream examination("./Exercises.txt",ios::app);
  // 异常处理 
  if(!examination){
    cout << "Unable to open otfile";
    exit(1);
  }
  int index = 0;
  // 输出题目
  for (string& e : examinations) {
    e += " = ";
    examination << ++index << "." << e << endl;
  }
  examination.close(); // 关闭文件 

  index = 0;
  
  // 输出答案
  remove("./Answers.txt");
  ofstream res("./Answers.txt",ios::app);
  //同上，异常处理 
  if(!res){
    cout << "Unable to open otfile";
    exit(1);
  }
  for (const auto& r : results) {
    res << ++index << "." << r << endl;
  }
  res.close();
}

// 主函数 
int main(int argc, char *argv[]) { // 接收（命令行）参数 
  int count = 0,maxNum = 0;
  string exerciseFile, answerFile;
  for (int i = 1; i < argc; i += 2) {
    string curArgv = string(argv[i]);
    if (curArgv == "-n") {
      count = stoi(argv[i + 1]);
    }
    else if (curArgv == "-r") {
      maxNum = stoi(argv[i + 1]);
    }
    else if (curArgv == "-e") {
      exerciseFile = argv[i + 1];
    }
    else if (curArgv == "-a") {
      answerFile = argv[i + 1];
    }
  }  // 下面的模式选择条件，取决于以上四个变量接收情况 
  bool runFlag = false;
  // 模式一
  if (count != 0 && maxNum != 0) {
    runFlag = true;
    vector<string> results;
    vector<std::string> examinations = Examination::generate(count, maxNum, results);
    output(examinations, results);
  }
  // 模式二 
  else if (!exerciseFile.empty() && !answerFile.empty()) {
    runFlag = true;
    fstream exe(exerciseFile), an(answerFile);
    // 异常处理 
    if (!exe || !an) {
      cout << "文件不存在！";
    }
    else {
      remove("./Grade.txt");
      ofstream output("./Grade.txt",ios::app);
      string string1,string2;
      int index = 1;
      string correct, wrong;
      int correctCount = 0, wrongCount = 0;
      // 对题目文件和答案文件分别逐行读取 
      while (getline(exe,string1) && getline(an, string2)) {
        // 去掉序号
        string1 =  string1.substr(string1.find('.') + 1);
        string res = Calculator::calculate(string1);

        string2 =  string2.substr(string2.find('.') + 1);
        // 答对了
        if (res == string2) {
          ++correctCount;
          correct += to_string(index) + "，";
        }
        else {
          ++wrongCount;
          wrong += to_string(index) + "，";
        }
        index++;
      }
      // 输出正确/错误题目统计结果，-3是去掉最后的逗号
      correct = "Correct:"+ to_string(correctCount) + "(" + correct.substr(0, correct.size() - 3) + ")";
      wrong = "Wrong:"+ to_string(wrongCount) + "(" + wrong.substr(0, wrong.size() - 3) + ")";
      output << correct << endl;
      output << wrong << endl;
    }
  }
  if (argc != 5 || !runFlag) {
    cout << "请在运行本文件时输入正确的参数" << endl;
    cout << "示例：" << endl;
    cout << "  模式一：-n 10000 -r 100" << endl;
    cout << "  模式二：-e exerciseFile.txt -a answerFile.txt" << endl;
    return 0;
  }
  return 0;
}

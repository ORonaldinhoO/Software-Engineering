
#include <fstream>
#include "Examination.h"
#include "Calculator.h"
using namespace std;

// ����Ŀ����Ŀ������� 
void output(vector<string>& examinations, const vector<string>& results) {
  remove("./Exercises.txt");
  ofstream examination("./Exercises.txt",ios::app);
  // �쳣���� 
  if(!examination){
    cout << "Unable to open otfile";
    exit(1);
  }
  int index = 0;
  // �����Ŀ
  for (string& e : examinations) {
    e += " = ";
    examination << ++index << "." << e << endl;
  }
  examination.close(); // �ر��ļ� 

  index = 0;
  
  // �����
  remove("./Answers.txt");
  ofstream res("./Answers.txt",ios::app);
  //ͬ�ϣ��쳣���� 
  if(!res){
    cout << "Unable to open otfile";
    exit(1);
  }
  for (const auto& r : results) {
    res << ++index << "." << r << endl;
  }
  res.close();
}

// ������ 
int main(int argc, char *argv[]) { // ���գ������У����� 
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
  }  // �����ģʽѡ��������ȡ���������ĸ������������ 
  bool runFlag = false;
  // ģʽһ
  if (count != 0 && maxNum != 0) {
    runFlag = true;
    vector<string> results;
    vector<std::string> examinations = Examination::generate(count, maxNum, results);
    output(examinations, results);
  }
  // ģʽ�� 
  else if (!exerciseFile.empty() && !answerFile.empty()) {
    runFlag = true;
    fstream exe(exerciseFile), an(answerFile);
    // �쳣���� 
    if (!exe || !an) {
      cout << "�ļ������ڣ�";
    }
    else {
      remove("./Grade.txt");
      ofstream output("./Grade.txt",ios::app);
      string string1,string2;
      int index = 1;
      string correct, wrong;
      int correctCount = 0, wrongCount = 0;
      // ����Ŀ�ļ��ʹ��ļ��ֱ����ж�ȡ 
      while (getline(exe,string1) && getline(an, string2)) {
        // ȥ�����
        string1 =  string1.substr(string1.find('.') + 1);
        string res = Calculator::calculate(string1);

        string2 =  string2.substr(string2.find('.') + 1);
        // �����
        if (res == string2) {
          ++correctCount;
          correct += to_string(index) + "��";
        }
        else {
          ++wrongCount;
          wrong += to_string(index) + "��";
        }
        index++;
      }
      // �����ȷ/������Ŀͳ�ƽ����-3��ȥ�����Ķ���
      correct = "Correct:"+ to_string(correctCount) + "(" + correct.substr(0, correct.size() - 3) + ")";
      wrong = "Wrong:"+ to_string(wrongCount) + "(" + wrong.substr(0, wrong.size() - 3) + ")";
      output << correct << endl;
      output << wrong << endl;
    }
  }
  if (argc != 5 || !runFlag) {
    cout << "�������б��ļ�ʱ������ȷ�Ĳ���" << endl;
    cout << "ʾ����" << endl;
    cout << "  ģʽһ��-n 10000 -r 100" << endl;
    cout << "  ģʽ����-e exerciseFile.txt -a answerFile.txt" << endl;
    return 0;
  }
  return 0;
}

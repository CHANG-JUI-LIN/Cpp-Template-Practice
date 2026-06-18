#include <iostream>   
#include <vector>     
#include <string>     
#include <algorithm>  
#include <iomanip>    
#include <limits>     

using namespace std;  

// Student 結構，放學生資料用的
struct Student {
    string id;      // 學號
    string name;    // 姓名
    int score;      // 成績
};

// getMax template：傳回較大的那個值
template <class T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// getMin template：傳回較小的那個值
template <class T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}

// 用學號找學生在 vector 裡的 index，找不到回 -1
int findIndex(const vector<Student>& students, const string& id) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].id == id)
            return static_cast<int>(i);
    }
    return -1;
}

// 功能 1：新增學生
void addStudent(vector<Student>& students) {
    Student s;

    cout << "請輸入學號：";
    cin >> s.id;
    cout << "請輸入姓名：";
    cin >> s.name;
    cout << "請輸入成績：";
    cin >> s.score;

    int idx = findIndex(students, s.id);
    if (idx != -1) {
        char c;
        cout << "學號已存在，是否覆蓋？(y/n)：";
        cin >> c;
        if (c == 'y' || c == 'Y') {
            students[idx] = s;
            cout << "已更新。\n";
        } else {
            cout << "已取消。\n";
        }
    } else {
        students.push_back(s);
        cout << "新增成功。\n";
    }
}

// 功能 2：列出所有學生
void listStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "目前沒有學生資料。\n";
        return;
    }

    cout << left << setw(12) << "學號"
         << setw(16) << "姓名"
         << "成績\n";
    cout << string(40, '-') << "\n";

    for (const auto& s : students) {
        cout << left << setw(12) << s.id
             << setw(16) << s.name
             << s.score << "\n";
    }
}

// 功能 3：依成績排序（由高到低）
void sortByScore(vector<Student>& students) {
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.score > b.score;
         });

    cout << "排序完成（由高到低）。\n";
    listStudents(students);
}

// 功能 4：查詢學生
void searchById(const vector<Student>& students) {
    string id;
    cout << "請輸入學號：";
    cin >> id;

    int idx = findIndex(students, id);
    if (idx == -1) {
        cout << "找不到該學號。\n";
        return;
    }

    const auto& s = students[idx];
    cout << "學號：" << s.id << "\n"
         << "姓名：" << s.name << "\n"
         << "成績：" << s.score << "\n";
}

// 功能 5：統計成績
void showStatistics(const vector<Student>& students) {
    if (students.empty()) {
        cout << "沒有資料可以統計。\n";
        return;
    }

    int sum = 0;
    int maxScore = students[0].score;
    int minScore = students[0].score;
    int pass = 0, fail = 0;

    for (const auto& s : students) {
        sum += s.score;
        maxScore = getMax(maxScore, s.score);
        minScore = getMin(minScore, s.score);
        if (s.score >= 60)
            pass++;
        else
            fail++;
    }

    double avg = static_cast<double>(sum) / students.size();

    cout << fixed << setprecision(2);
    cout << "學生總人數：" << students.size() << "\n";
    cout << "平均成績  ：" << avg << "\n";
    cout << "最高分    ：" << maxScore << "\n";
    cout << "最低分    ：" << minScore << "\n";
    cout << "及格(>=60)：" << pass << " 人\n";
    cout << "不及格(<60)：" << fail << " 人\n";
}

// main：程式入口
int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n===== 學生成績管理系統 =====\n";
        cout << "1. 新增學生\n";
        cout << "2. 列出所有學生\n";
        cout << "3. 依成績排序\n";
        cout << "4. 查詢學生\n";
        cout << "5. 統計成績\n";
        cout << "0. 離開\n";
        cout << "請輸入選項：";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: listStudents(students); break;
            case 3: sortByScore(students); break;
            case 4: searchById(students); break;
            case 5: showStatistics(students); break;
            case 0: cout << "掰掰。\n"; break;
            default: cout << "無效選項。\n";
        }
    } while (choice != 0);

    return 0;
}

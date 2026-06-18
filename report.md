# C++ Template 延伸自主練習 — 學習報告

**主題**：STL 與基礎資料結構入門  
**姓名**：張瑞麟
**學號**：s11459010    
**GitHub Repository**：https://github.com/CHANG-JUI-LIN/C-Template-Practice

---

## 目錄

1. [自主學習主題與目標](#1-自主學習主題與目標)
2. [Template 與 STL 的關係](#2-template-與-stl-的關係)
3. [常見 STL 容器用途整理](#3-常見-stl-容器用途整理)
4. [第 2 週小專題設計說明](#4-第-2-週小專題設計說明)
5. [主要程式架構與重要程式片段](#5-主要程式架構與重要程式片段)
6. [執行畫面或輸出結果](#6-執行畫面或輸出結果)
7. [GitHub Repo Link 與檔案結構說明](#7-github-repo-link-與檔案結構說明)
8. [遇到的問題與解決方式](#8-遇到的問題與解決方式)
9. [學習心得與未來可延伸方向](#9-學習心得與未來可延伸方向)

---

## 1. 自主學習主題與目標

### 1.1 主題

本次自主學習的主題為「STL 與基礎資料結構入門」，接續課堂 Chapter 16 Templates 中 function template 與 class template 的觀念，進一步延伸至 C++ Standard Template Library（STL）中的 containers 與 algorithms。

### 1.2 學習目標

- 理解 template 與 STL 之間的關係，知道 STL 容器本質上就是 class template 的實例化。
- 熟悉常用 STL 容器（vector、stack、queue、priority_queue、set、map）的基本操作與使用時機。
- 能夠依據不同的問題需求，選擇合適的資料結構來解決問題。
- 能夠撰寫可在 `g++ -std=c++17` 環境下編譯與執行的 C++ 程式。
- 為大二的「資料結構」課程建立先備基礎，降低正式修課時的學習門檻。

### 1.3 學習規劃

| 週次 | 學習內容 | 備註 |
|------|----------|------|
| 第 1 週 | STL 容器基礎自主練習（vector、stack、queue、map） | 自主練習，不用繳交 |
| 第 2 週 | 整合應用小專題——學生成績管理系統 | 正式繳交 |

---

## 2. Template 與 STL 的關係

### 2.1 什麼是 Template

Template 是 C++ 中實現泛型程式設計（generic programming）的核心機制。透過 template，我們可以編寫與型別無關（type-independent）的函式或類別，讓同一份程式碼能夠套用到不同的資料型別上。

```cpp
template <class T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}
```

上述 function template 可以在 `int`、`double`、`string` 等任何支援 `operator>` 的型別上使用，編譯器會依據實際呼叫時的參數型別自動推導（template argument deduction）並實例化出對應的函式。

### 2.2 什麼是 STL

STL（Standard Template Library）是 C++ 標準程式庫的核心組成部分，主要由以下三大元件構成：

1. **Containers（容器）**：用來儲存資料的資料結構，例如 vector、list、map 等。
2. **Algorithms（演算法）**：用來操作容器中資料的泛型演算法，例如 sort、find、accumulate 等。
3. **Iterators（迭代器）**：用來遍歷容器中元素的統一介面，類似於指標的泛化。

### 2.3 Template 與 STL 的連結

STL 的本質就是 Template 的實際應用。舉例來說：

- `std::vector<int>` 是 class template `std::vector` 以 `int` 型別實例化的結果。
- `std::sort(v.begin(), v.end())` 是 function template `std::sort` 搭配隨機存取迭代器的應用。
- `std::map<std::string, int>` 是 class template `std::map` 以 `string` 為鍵、`int` 為值的實例化。

換句話說，如果沒有 template 機制，STL 就無法存在。template 讓 STL 能夠做到「一份容器定義，適用於任意元素型別」，這也是 C++ 泛型程式設計的核心價值。

---

## 3. 常見 STL 容器用途整理

### 3.1 容器分類

| 類別 | 容器 | 底層資料結構 | 特點 |
|------|------|-------------|------|
| 序列容器 | `vector` | 動態陣列 | 隨機存取 O(1)，尾端增刪 O(1) |
| 序列容器 | `deque` | 雙端佇列 | 頭尾增刪 O(1) |
| 序列容器 | `list` | 雙向鏈結串列 | 任意位置插入 O(1)，無隨機存取 |
| 容器配接器 | `stack` | 預設 deque | LIFO，只能操作頂端 |
| 容器配接器 | `queue` | 預設 deque | FIFO，只能操作頭尾 |
| 容器配接器 | `priority_queue` | heap（預設 vector） | 最大／最小元素優先 |
| 關聯容器 | `set` | 紅黑樹 | 有序、不重複、O(log n) 查詢 |
| 關聯容器 | `map` | 紅黑樹 | 鍵值配對、有序、O(log n) 查詢 |
| 無序容器 | `unordered_set` | 哈希表 | 無序、O(1) 平均查詢 |
| 無序容器 | `unordered_map` | 哈希表 | 鍵值配對、O(1) 平均查詢 |

### 3.2 各容器使用情境

**vector**：需要隨機存取且主要在尾端增刪資料時使用。例如學生成績列表、動態陣列。

**stack**：需要 LIFO（後進先出）行為時使用。典型應用包括括號配對檢查、函式呼叫堆疊、undo 操作。

**queue**：需要 FIFO（先進先出）行為時使用。典型應用包括排隊系統、BFS（廣度優先搜尋）、工作佇列。

**priority_queue**：需要每次取出最大（或最小）元素時使用。典型應用包括任務排程、Dijkstra 最短路徑演算法。

**set**：需要維護一群不重複且有序的元素時使用。典型應用包括去除重複值、集合運算。

**map**：需要建立鍵值對應關係時使用。典型應用包括字典、單字計數、學號查詢學生資料。

### 3.3 本專題選擇 vector 的原因

本專題選用 `vector<Student>` 作為主要資料結構，原因如下：

- 系統需要頻繁地進行「列出所有學生」與「依成績排序」的操作，vector 的連續記憶體配置對遍歷與排序非常友好。
- `std::sort` 要求隨機存取迭代器，vector 正好提供此介面。
- 學生數量在執行期間動態成長且主要在尾端新增，符合 vector 的優勢場景。
- 當需要依學號查詢時，我們自行實作線性搜尋（或可改用 map 改善查詢效率）。

---

## 4. 第 2 週小專題設計說明

### 4.1 專題名稱

學生成績管理系統（Student Grade Management System）

### 4.2 功能需求

| 功能編號 | 功能名稱 | 說明 |
|---------|---------|------|
| 1 | 新增學生資料 | 輸入學號、姓名、成績；學號重複時提示覆蓋 |
| 2 | 列出所有學生 | 以表格格式輸出所有學生資料 |
| 3 | 依成績排序 | 使用 `std::sort` 依成績由高到低排序 |
| 4 | 查詢學生 | 輸入學號查詢該學生詳細資料 |
| 5 | 統計成績 | 計算平均、最高分、最低分、及格／不及格人數 |

### 4.3 系統架構

```
main()
  ├── addStudent()    — 新增學生（含重複檢查）
  ├── listStudents()  — 列出所有學生
  ├── sortByScore()   — 依成績排序（使用 std::sort + lambda）
  ├── searchById()    — 依學號查詢（使用線性搜尋）
  └── showStatistics()— 統計分析（使用 getMax / getMin template）
```

### 4.4 選單介面設計

程式啟動後顯示文字選單，使用者輸入數字選擇功能：

```
===== Student Grade Management System =====
1. Add student
2. List all students
3. Sort by score
4. Search by ID
5. Show statistics
0. Exit
Choice: _
```

選單採用 do-while 迴圈持續顯示，直到使用者輸入 0 才結束程式。對無效輸入（非選單選項的數字）會顯示 "Invalid choice." 提示。

---

## 5. 主要程式架構與重要程式片段

### 5.1 Student 結構

```cpp
struct Student {
    string id;      // 學號
    string name;    // 姓名
    int score;      // 成績
};
```

使用 struct 而非 class，因為 Student 僅作為資料聚合（data aggregate），不需封裝或私有成員。

### 5.2 資料儲存方式

```cpp
vector<Student> students;
```

使用 `vector<Student>` 動態陣列儲存所有學生資料，透過 `push_back()` 在尾端新增元素。

### 5.3 Template Function：getMax 與 getMin

```cpp
template <class T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

template <class T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}
```

這兩個 template function 使用三元運算子進行比較，支援所有實作了 `operator>` 或 `operator<` 的型別。在本專題中，它們被用於統計最高分與最低分：

```cpp
int maxScore = students[0].score;
int minScore = students[0].score;
for (const auto& s : students) {
    maxScore = getMax(maxScore, s.score);
    minScore = getMin(minScore, s.score);
}
```

### 5.4 新增學生與重複處理

```cpp
void addStudent(vector<Student>& students) {
    Student s;
    cout << "Enter ID: ";  cin >> s.id;
    cout << "Enter name: "; cin >> s.name;
    cout << "Enter score: "; cin >> s.score;

    int idx = findIndex(students, s.id);
    if (idx != -1) {
        char c;
        cout << "ID already exists. Overwrite? (y/n): ";
        cin >> c;
        if (c == 'y' || c == 'Y') {
            students[idx] = s;
            cout << "Student updated.\n";
        } else {
            cout << "Addition cancelled.\n";
        }
    } else {
        students.push_back(s);
        cout << "Student added.\n";
    }
}
```

當學號重複時，系統會詢問使用者是否要覆蓋原有資料，避免誤操作導致資料遺失。

### 5.5 排序功能

```cpp
void sortByScore(vector<Student>& students) {
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.score > b.score;
         });
    cout << "Sorted by score (descending).\n";
    listStudents(students);
}
```

使用 `std::sort` 搭配 lambda expression 自訂比較邏輯，依成績由高到低排序。排序完成後自動呼叫 `listStudents()` 顯示結果。

### 5.6 統計功能

```cpp
void showStatistics(const vector<Student>& students) {
    int sum = 0;
    int maxScore = students[0].score;
    int minScore = students[0].score;
    int pass = 0, fail = 0;

    for (const auto& s : students) {
        sum += s.score;
        maxScore = getMax(maxScore, s.score);
        minScore = getMin(minScore, s.score);
        if (s.score >= 60) pass++;
        else fail++;
    }

    double avg = static_cast<double>(sum) / students.size();
    cout << "Average score : " << avg << "\n";
    cout << "Highest score : " << maxScore << "\n";
    cout << "Lowest score  : " << minScore << "\n";
    cout << "Pass (>=60)   : " << pass << "\n";
    cout << "Fail (<60)    : " << fail << "\n";
}
```

此函式一趟迴圈完成所有統計：加總、更新最大最小值、計算及格人數。其中 getMax 與 getMin 為自行實作的 template function，滿足固定挑戰題的要求。

---

## 6. 執行畫面或輸出結果

### 6.1 新增學生

```
===== Student Grade Management System =====
1. Add student
2. List all students
3. Sort by score
4. Search by ID
5. Show statistics
0. Exit
Choice: 1
Enter ID: 001
Enter name: Alice
Enter score: 85
Student added.
```

### 6.2 學號重複時

```
Choice: 1
Enter ID: 001
Enter name: Alice2
Enter score: 90
ID already exists. Overwrite? (y/n): n
Addition cancelled.
```

### 6.3 列出所有學生

```
Choice: 2
ID          Name            Score
----------------------------------------
001         Alice           85
002         Bob             92
003         Charlie         58
004         Diana           73
005         Eve             45
```

### 6.4 排序結果

```
Choice: 3
Sorted by score (descending).
ID          Name            Score
----------------------------------------
002         Bob             92
001         Alice           85
004         Diana           73
003         Charlie         58
005         Eve             45
```

### 6.5 查詢學生

```
Choice: 4
Enter ID to search: 003
ID: 003
Name: Charlie
Score: 58
```

查詢不存在的學號：

```
Choice: 4
Enter ID to search: 999
Student not found.
```

### 6.6 統計結果

```
Choice: 5
Total students: 5
Average score : 70.60
Highest score : 92
Lowest score  : 45
Pass (>=60)   : 3
Fail (<60)    : 2
```

---

## 7. GitHub Repo Link 與檔案結構說明

### 7.1 Repository 位置

**GitHub URL**：https://github.com/your-account/your-repository

### 7.2 檔案結構

```
/
├── main.cpp          # 主程式 — 學生成績管理系統
├── README.md         # 專案說明、編譯方式、功能列表
├── report.md         # 學習報告（本文件）
```

### 7.3 編譯方式

```bash
g++ -std=c++17 main.cpp -o main
```

由於程式僅包含單一原始檔，不需額外的 Makefile 或多檔案建置步驟。若未來擴充為多檔案結構，會在 README.md 中更新編譯說明。

---

## 8. 遇到的問題與解決方式

### 8.1 問題一：學號重複處理策略

**問題**：當使用者輸入已存在的學號時，應該如何處理？直接拒絕新增可能會讓使用者困惑，直接覆蓋則可能導致重要資料遺失。

**解決方式**：採用「提示詢問」策略。偵測到重複學號時，先顯示提醒訊息，然後詢問使用者是否要覆蓋。使用者可選擇覆蓋（y）或取消（n），將決定權交給使用者。

### 8.2 問題二：排序方式選擇

**問題**：在設計排序功能時，曾經考慮過是否要讓使用者選擇遞增或遞減排序。

**解決方式**：依照題目要求，實作為依成績由高到低（遞減）排序。若未來要擴充，可以在選單中增加子選項讓使用者選擇排序方向，或在排序前詢問升冪或降冪。

### 8.3 問題三：cin 輸入後的換行問題

**問題**：使用 `cin >>` 讀取數字後，緩衝區中會留下換行字元，若後續使用 `getline()` 會讀到空字串。

**解決方式**：本專案中姓名與 ID 皆使用 `cin >>` 讀取單詞（不含空格），避開了 `getline()` 的換行問題。若未來要支援含空格的姓名，需要使用 `cin.ignore()` 搭配 `getline()` 處理。

### 8.4 問題四：vector 與 map 的選擇

**問題**：題目建議可使用 `vector<Student>` 或 `map<string, Student>`，兩者各有優缺點。

**解決方式**：考量到排序是必要功能（功能 3），`map` 的鍵值有序性對「依成績排序」沒有幫助（map 以學號而非成績排序），仍需轉換為 vector 再排序。為減少不必要的型別轉換並提升程式碼簡潔度，最終選擇 `vector<Student>` 作為主要資料結構，查詢功能則透過線性搜尋實作。

---

## 9. 學習心得與未來可延伸方向

### 9.1 學習心得

透過這次自主學習，我對 C++ 的 template 與 STL 有了更深入的認識。過去我只知道 template 可以讓函式接受不同型別的參數，但並不理解它在實際專案中的應用場景。直到這次作業，我才發現 STL 中隨處可見的 vector、map、sort 等元件，本質上都是 template 的具體實現。

在實作「學生成績管理系統」的過程中，我體會到選擇合適的資料結構對程式設計的重要性。vector 的連續記憶體配置讓排序與遍歷操作非常高效，而它的動態成長特性也讓新增學生變得非常方便。

此外，template function getMax 與 getMin 雖然只有短短幾行，卻展示了泛型程式設計的威力——同一份程式碼可以同時用於 int、double、甚至自訂型別的比較。

### 9.2 未來可延伸方向

1. **增加檔案讀寫功能**：將學生資料儲存至檔案（如 CSV 格式），程式啟動時自動載入，結束時自動儲存，實現資料持久化。

2. **改用 map 提升查詢效率**：若學生數量很大（如數千人），可改用 `map<string, Student>` 以學號為鍵，讓查詢時間從 O(n) 降至 O(log n)。

3. **加入修改與刪除功能**：新增編輯學生資料與刪除學生的功能，讓管理系統更加完整。

4. **圖形化使用者介面**：使用 Qt 或其他 GUI 框架為系統加入圖形介面，提升使用者體驗。

5. **擴充學生欄位**：增加更多欄位如性別、生日、班級、各科成績等，並提供各科成績分析功能。

6. **整合更多 STL 容器**：使用 priority_queue 實作「成績前十名排行榜」，使用 set 實作「不重複的班級列表」等進階功能。

---

*本報告由學生自行撰寫，程式碼為原創作品，如有參考外部資源已於文中標註。*

#include <bits/stdc++.h>
using namespace std;

bool isBlank(string &str) {
    return str.find_first_not_of(" ") == -1;
}

string eraseSpace(string &str) {
    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ")+1, str.length());
    return str;
}

void processParagraph(string &str, int &row, int &col, int width, bool newline) {
    if(str.empty()) {
        return;
    }
    for(int i = width; i < str.length(); i += width) {
        while(str[i] == ' ') {
            str.replace(i, 1, "");
        }
    }
    
    row += (str.size()-1) / width + 1;
    if(newline) {
        row++;
    }
    cout << row << "    " << str << endl;
    str = "";
    return;
}

int main() {
    // ios::sync_with_stdio(false);
    freopen("2020_6_3.txt", "r", stdin);
    int col = 0, row = 0, cnt = 0, width;
    bool newline = false;
    cin >> width;
    string paragraph = "", tmp = "";
    getline(cin, tmp);
    tmp = "";
    while(!cin.eof()) {
        getline(cin, tmp);
        // cout << tmp << endl;
        if(isBlank(tmp)) {
            eraseSpace(paragraph);
            processParagraph(paragraph, row, col, width, newline);
            newline = true;
        } else {
            eraseSpace(tmp);
            paragraph = paragraph + " " + tmp;
            // cout << "para:: " << paragraph << endl;
        }
    }
    cout << row << endl;
    return 0;
}
// int main() {
//     string str;
//     getline(cin, str);
//     cout << str.length();
//     str.replace(1, 1, "");
//     cout << str.length() << " " << str.find_first_not_of(" ") << " " << str.find_last_not_of(" ");
//     return 0;
// }
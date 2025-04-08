#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Alekseev_Aleksei_FST {
protected:
    string sub; 
    int state = 0;  
public:
    vector<int> prefix;  
    Alekseev_Aleksei_FST(string sub) : sub(sub) {}  

    vector<int> prefix_(string s) {
        int n = s.length();
        vector<int> pi(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (s.substr(0, j + 1) == s.substr(i - j, j + 1)) {
                    pi[i] = j + 1;  
                }
            }
        }
        return pi;
    }

    int process(char c) {
        while (state > 0 && c != sub[state]) {
            state = prefix[state - 1];  
        }
        state = transition(c);  
        if (state == sub.length()) {
            state = prefix[state - 1];  
            return 1;  
        }
        return 0;  
    }

    int transition(char c) {
        if (c == this->sub[this->state]) {
            this->state++; 
        } else {
            this->state = 0;  
        }
        return this->state;
    }
};

int main() {
    string str;
    getline(cin, str);  
    Alekseev_Aleksei_FST fst(str);  
    string str2;
    getline(cin, str2);  
    vector<char> line;
    for (char c : str2) {
        line.push_back(c);  
    }
    int output = 0;
    fst.prefix = fst.prefix_(str2);  
    for (int i = 0; i < line.size(); i++) {
        if (fst.process(line[i]) == 1) {
            output++; 
        }
    }
    if (output == 0) {
        cout << "NOT DETECTED" << endl; 
    } else {
        cout << output << endl; 
    }
}
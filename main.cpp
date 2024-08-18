#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

union Value {
    double num;
    char op;
};

class Node {
  public:
    Value value;
    Node* lVal;
    Node* rVal;
    bool isNum = true;

    Node() {};

    void setOp(char op) {
        value.op = op;
        isNum = true;
    }

    void setNum(double num) {
        value.num = num;
        isNum = false;
    }
};

double parseNum(const char* eq) {}

Node* parseEq(char* eqBeg, char* eqEnd) {
    std::vector<char*> bracket;
    for (char* curNode = eqBeg; curNode != eqEnd; ++curNode) {
        if (*curNode == '(') {
            bracket.push_back(curNode);
        }
    }
}

double solve(std::string& eq) {
    std::cout << "solving..." << std::endl;
    std::cout << eq << std::endl;
    return 0;
}

// basic implementation
double simple_solve(std::string& eq) {
    eq.erase(std::remove_if(eq.begin(), eq.end(), isspace), eq.end());
    int lNum = eq.at(0) - 48;
    char symbol = eq.at(1);
    int rNum = eq.at(2) - 48;

    switch (symbol) {
    case '+':
        return lNum + rNum;
    case '-':
        return lNum - rNum;
    case '*':
        return lNum * rNum;
    case '/':
        return (double)lNum / (double)rNum;
    case '^':
        return pow(lNum, rNum);
    default:
        std::cout << "Enter a valid symbol: " << std::endl;
        return -1;
    }
}

int main() {
    std::string eq;
    std::cout << "Enter in your equation: " << std::endl;

    while (std::getline(std::cin, eq)) {
        if (eq.empty()) {
            continue;
        }

        eq.erase(std::remove_if(eq.begin(), eq.end(), isspace), eq.end());
        double ans = simple_solve(eq);
        std::cout << ans << std::endl;
        std::cout << "Enter in your equation: " << std::endl;
    }

    return 0;
}

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

double solve(std::string& eq) {
    eq.erase(std::remove_if(eq.begin(), eq.end(), isspace), eq.end());
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
        return -1;
    }
}

int main() {
    std::string eq;
    std::cout << "Enter in your equation:" << std::endl;
    while (std::getline(std::cin, eq)) {
        double ans = simple_solve(eq);
        std::cout << ans << std::endl;
        std::cout << "Enter in your equation:" << std::endl;
    }

    return 0;
}

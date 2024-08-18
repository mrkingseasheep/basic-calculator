#include <algorithm>
#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// no more tree solution
// using shunting yard algo
// also reverse polish notation
// https://stackoverflow.com/questions/11627440/regex-c-extract-substring
void parseToReversePolish(const std::string& eq,
                          std::vector<std::string>& rPolishEq) {
    std::regex findNum("\\d*.?\\d*");
    // TODO all chars must be lowercase
    std::regex findSym("[^\\d\\.a-z]|[a-z]{3}|[a-z]{3}\\d*");
    std::smatch numMatches;
    std::smatch symMatches;
    std::regex_search(eq.begin(), eq.end(), numMatches, findNum);
    std::regex_search(eq.begin(), eq.end(), symMatches, findSym);
}

int main() {
    std::string eq;
    std::cout << "Enter in your equation: " << std::endl;

    while (std::getline(std::cin, eq)) {
        if (eq.empty()) {
            continue;
        }

        std::vector<std::string> rPolishEq;
        eq.erase(std::remove_if(eq.begin(), eq.end(), isspace), eq.end());
        parseToReversePolish(eq, rPolishEq);
        /*double ans = simple_solve(eq);*/
        /*std::cout << ans << std::endl;*/
        std::cout << "Enter in your equation: " << std::endl;
    }

    return 0;
}

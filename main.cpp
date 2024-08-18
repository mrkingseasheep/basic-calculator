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
void parseToReversePolish(const char* eq, std::vector<std::string>& rPolishEq) {
    std::regex numRgx("\\d*.?\\d*");
    std::smatch match;
    /*const std::string temp = "042.6240";*/
    if (std::regex_search(eq, eq + 1, match, numRgx)) {
        std::cout << match[0] << std::endl;
    }
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
        parseToReversePolish(eq.c_str(), rPolishEq);
        /*double ans = simple_solve(eq);*/
        /*std::cout << ans << std::endl;*/
        std::cout << "Enter in your equation: " << std::endl;
    }

    return 0;
}

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <vector>

// no more tree solution
// using shunting yard algo
// also reverse polish notation
// https://stackoverflow.com/questions/11627440/regex-c-extract-substring
void parseToReversePolish(std::string& eq,
                          std::vector<std::string>& rPolishEq) {
    // TODO all chars must be lowercase
    const std::regex findVal("[^\\d\\.a-z]|[a-z]{3}|\\d*\\.?\\d+");
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> value(eq.begin(), eq.end(),
                                                           findVal);
    std::queue<std::string> eqQueue;
    while (value != rend) {
        std::cout << *value++ << std::endl;
        /*eqQueue.push(*value++);*/
        /*std::cout << eqQueue.front() << std::endl;*/
        /*eqQueue.pop();*/
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
        parseToReversePolish(eq, rPolishEq);
        /*double ans = simple_solve(eq);*/
        /*std::cout << ans << std::endl;*/
        std::cout << "Enter in your equation: " << std::endl;
    }

    return 0;
}

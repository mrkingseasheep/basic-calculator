#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <vector>

// no more tree solution
// using shunting yard algo
// also reverse polish notation
// https://stackoverflow.com/questions/11627440/regex-c-extract-substring
void tokenizeEq(std::string& eq, std::queue<std::string>& actionQueue) {
    // TODO all chars must be lowercase
    // https://stackoverflow.com/questions/21667295/how-to-match-multiple-results-using-stdregex
    const std::regex findVal("[^\\d\\.a-z]|[a-z]{3}|\\d*\\.?\\d+");
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> value(eq.begin(), eq.end(),
                                                           findVal);

    while (value != rend) {
        actionQueue.push(*value++);
    }
}

// Which operators have the greatest priority
// ()
// ^
// */
// +-
// > < >= <= =
std::vector<std::string>
parseToReversePolish(std::string& eq, std::queue<std::string>& actionQueue) {
    std::stack<std::string> eqOperator;
    std::vector<std::string> action;

    while (!actionQueue.empty()) {
        std::string curAction = actionQueue.front();
        actionQueue.pop();

        if (curAction.at(0) == '.' || isdigit(curAction.at(0))) {
            // checks if is digit or not
            // remove for final
            double num;
            try {
                num = std::stod(curAction);
            } catch (...) {
                std::cerr << "Cannot change string to num: " << curAction
                          << std::endl;
                break;
            }
            action.push_back(curAction);
            continue;
        }

        // CHANGE ME AFTER DEBUG
        action.push_back("+");
    }

    return action;
}

double solveReversePolishEq(std::vector<std::string>& action) {}

int main() {
    std::string eq;
    std::cout << "Enter in your equation: " << std::endl;

    while (std::getline(std::cin, eq)) {
        if (eq.empty()) {
            continue;
        }

        std::queue<std::string> actionQueue;
        eq.erase(std::remove_if(eq.begin(), eq.end(), isspace), eq.end());
        tokenizeEq(eq, actionQueue);
        std::vector<std::string> action = parseToReversePolish(eq, actionQueue);

        for (auto temp : action) {
            std::cout << temp << std::endl;
        }

        std::cout << "Enter in your equation: " << std::endl;
    }

    return 0;
}

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

// Which operators have the greatest priority
// ()
// ^
// */
// +-
// > < >= <= =
// cant be const for reasons
// still const in spirit lmao
std::unordered_map<std::string, int> OPERATOR_PRIORITY = {
    {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3}, {"^", 4}, {"%", 4}};

// no more tree solution
// using shunting yard algo
// also reverse polish notation
// https://stackoverflow.com/questions/11627440/regex-c-extract-substring
void tokenizeEq(std::string& eq, std::queue<std::string>& actionQueue) {
    // TODO all chars must be lowercase
    // https://stackoverflow.com/questions/21667295/how-to-match-multiple-results-using-stdregex
    const std::regex findVal("\\d*\\.?\\d+|[^\\d\\.a-z]|[a-z]{3}");
    std::regex_token_iterator<std::string::iterator> rend;
    std::regex_token_iterator<std::string::iterator> value(eq.begin(), eq.end(),
                                                           findVal);

    while (value != rend) {
        actionQueue.push(*value++);
    }
}

std::vector<std::string>
parseToReversePolish(std::string& eq, std::queue<std::string>& actionQueue) {
    std::stack<std::string> eqOperator;
    std::vector<std::string> action;

    double prevPriority = -1;
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
            /*std::cout << curAction << std::endl;*/
            continue;
        }

        // curAction is a operation
        double priority = OPERATOR_PRIORITY[curAction];
        /*std::cout << priority << std::endl;*/

        // debugging code
        /*std::stack<std::string> tempOp = eqOperator;*/
        /*while (!tempOp.empty()) {*/
        /*    std::cout << tempOp.top();*/
        /*    tempOp.pop();*/
        /*}*/
        /*std::cout << std::endl;*/
        /*if (eqOperator.empty()) {*/
        /*    std::cout << "YOU STUPID" << std::endl;*/
        /*}*/

        if (prevPriority == -1) {
            // if first operator, add to stack
            eqOperator.push(curAction);
            prevPriority = priority;
            continue;
        } else {
            // if new, get priority of prev operator
            prevPriority = OPERATOR_PRIORITY[eqOperator.top()];
        }

        if (priority > prevPriority) {
            // if new op is more important
            // add curAction to stack
            eqOperator.push(curAction);
        } else {
            // if prev op is more important
            // put operator in
            action.push_back(eqOperator.top());
            // remove old op
            eqOperator.pop();
            // put new action on stack
            eqOperator.push(curAction);
        }
    }

    while (!eqOperator.empty()) {
        action.push_back(eqOperator.top());
        eqOperator.pop();
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
            std::cout << temp;
        }
        std::cout << std::endl;

        std::cout << "Enter in your equation: " << std::endl;
    }

    return 0;
}

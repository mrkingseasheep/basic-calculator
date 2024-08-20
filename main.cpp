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
    {"(", 0}, {")", 0}, {"+", 2}, {"-", 2},   {"*", 3},   {"/", 3},
    {"^", 5}, {"%", 5}, {"!", 5}, {"cos", 4}, {"tan", 4}, {"sin", 4}};

const std::string ONE_VAL_OPERATORS[] = {"sin", "cos", "tan", "!"};
constexpr int LEN_ONE_OPERATORS =
    sizeof(ONE_VAL_OPERATORS) / sizeof(*ONE_VAL_OPERATORS);

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
        /*std::cout << curAction << std::endl;*/

        if (curAction.at(0) == '.' || isdigit(curAction.at(0))) {
            // checks if is digit or not
            // remove for final
            double num;
            try {
                num = std::stod(curAction);
            } catch (...) {
                std::cerr << "Cannot change string to num: " << curAction
                          << std::endl;
                std::cout << num << std::endl;
                break;
            }
            action.push_back(curAction);
            /*std::cout << curAction << std::endl;*/
            continue;
        }

        if (curAction == "(") {
            // add ( to the stack
            eqOperator.push(curAction);
            continue;
        } else if (curAction == ")") {
            // pair found
            while (eqOperator.top() != "(") {
                // add all actions prior to )
                action.push_back(eqOperator.top());
                eqOperator.pop();
            }
            eqOperator.pop(); // remove the (
            /*std::cout << "STACK SIZE: " << eqOperator.size() << std::endl;*/
            /*std::cout << "STACK EMPTY: " << eqOperator.empty() << std::endl;*/
            prevPriority = -1;
            if (eqOperator.empty()) {
                // if stack empty, do nothing
                continue;
            }
            // if stack has stuff, add next op
            action.push_back(eqOperator.top());
            eqOperator.pop();
            continue;
        }

        // curAction is a operation
        double priority = OPERATOR_PRIORITY[curAction];
        if (prevPriority == -1) {
            // if first operator, add to stack
            /*std::cout << "FIRST TIME OP or after ()" << std::endl;*/
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
        /*std::cout << "straggler: pushing to back" << std::endl;*/
        action.push_back(eqOperator.top());
        eqOperator.pop();
    }

    return action;
}

double factorial(const double num) {
    if (num == 1) {
        return 1;
    }
    return num * factorial(num - 1);
}

bool isDouble(const std::string& str) {
    try {
        std::stod(str);
    } catch (...) {
        return false;
    }
    return true;
}

double getDouble(const std::string& str) {
    try {
        return std::stod(str);
    } catch (...) {
        std::cerr << "<ERROR> cannot convert to double" << std::endl;
        return -0.069;
    }
}

bool calcEqOneOp(std::string& lNum, std::string& op) {
    if (isDouble(op)) {
        return false;
    }
    double num = getDouble(lNum);
    if (op == "sin") {
        num = sin(num);
    } else if (op == "cos") {
        num = cos(num);
    } else if (op == "tan") {
        num = tan(num);
    } else if (op == "!") {
        num = factorial(num);
    } else {
        /*std::cout << "<ERROR> symbol not found" << std::endl;*/
        return false;
    }
    lNum = std::to_string(num);
    return true;
}

bool calcEqTwoOp(std::string& lNumStr, std::string& rNumStr, std::string& op) {
    double num;
    if (isDouble(op)) {
        return false;
    }
    double lNum = getDouble(lNumStr);
    double rNum = getDouble(rNumStr);
    /*std::cout << "======" << std::endl;*/
    /*std::cout << lNum << " " << op << " " << rNum << std::endl;*/
    if (op == "+") {
        lNum += rNum;
    } else if (op == "-") {
        lNum -= rNum;
    } else if (op == "*") {
        lNum *= rNum;
    } else if (op == "/") {
        lNum /= rNum;
    } else if (op == "^") {
        lNum = pow(lNum, rNum);
    } else if (op == "%") {
        lNum = (int)lNum % (int)rNum;
    } else {
        /*std::cout << "<ERROR> symbol not found" << std::endl;*/
        return false;
    }
    lNumStr = std::to_string(lNum);
    return true;
}

void debugActions(std::vector<std::string>* action) {
    std::cout << ">>> ";
    for (auto temp : *action) {
        std::cout << temp << " ";
    }
    std::cout << std::endl;
}

double solveReversePolishEq(std::vector<std::string>& action) {
    if (action.size() == 1) {
        return std::stod(action.at(0));
    } else if (action.size() == 0) {
        std::cerr << "<ERROR> no operations in stack" << std::endl;
        return -1;
    }

    int idx = 0;
    while (idx < action.size()) {
        debugActions(&action);

        std::string& lNumStr = action.at(idx);
        std::string& rNumStr = action.at(idx + 1);
        std::string& op = action.at(idx + 2);

        if (!isDouble(lNumStr)) {
            ++idx;
            continue;
        }

        if (calcEqOneOp(lNumStr, op)) {
            action.erase(action.begin() + idx + 1);
            return solveReversePolishEq(action);
        }

        if (calcEqTwoOp(lNumStr, rNumStr, op)) {
            action.erase(action.begin() + idx + 2); // erase from back to front
            action.erase(action.begin() + idx + 1);
            return solveReversePolishEq(action);
        }

        ++idx;
    }

    std::cerr << "<ERROR> loop completed without solution" << std::endl;
    std::cout << idx << std::endl;
    return -1;
}

void formatString(std::string& str) {
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    for (char& temp : str) {
        temp = tolower(temp);
        switch (temp) {
        case '[':
            temp = '(';
            break;
        case ']':
            temp = ')';
            break;
        case '{':
            temp = '(';
            break;
        case '}':
            temp = ')';
            break;
        }
    }
}

int main() {
    std::string eq;
    std::cout << "Enter in your equation: " << std::endl;

    while (std::getline(std::cin, eq)) {
        if (eq.empty()) {
            continue;
        }
        std::queue<std::string> actionQueue;

        formatString(eq);

        /*std::cout << eq << std::endl;*/
        tokenizeEq(eq, actionQueue);
        std::vector<std::string> action = parseToReversePolish(eq, actionQueue);

        double ans = solveReversePolishEq(action);
        std::cout << "<ANS> " << ans << std::endl;

        std::cout
            << "------------------------------------------------------------"
            << std::endl;
        std::cout << "Enter in your equation: " << std::endl;
    }

    return 0;
}

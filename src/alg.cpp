// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include <vector>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    TStack<char> stack;
    std::vector<std::string> tokens;
    std::string number;
    auto priority = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };
    for (char ch : inf) {
        if (std::isdigit(ch)) {
            number += ch;
            continue;
        } else {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
        }
        if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                tokens.push_back(std::string(1, stack.pop()));
            }
            if (!stack.isEmpty()) stack.pop();
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!stack.isEmpty() && stack.top() != '(' &&
                   priority(stack.top()) >= priority(ch)) {
                tokens.push_back(std::string(1, stack.pop()));
            }
            stack.push(ch);
        }
    }
    if (!number.empty()) {
        tokens.push_back(number);
    }
    while (!stack.isEmpty()) {
        tokens.push_back(std::string(1, stack.pop()));
    }
    std::string result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (i != 0) result += ' ';
        result += tokens[i];
    }
    return result;
}

int eval(const std::string& post) {
    TStack<int> stack;
    std::string token;
    for (char ch : post) {
        if (std::isdigit(ch)) {
            token += ch;
            continue;
        }
        if (ch == ' ') {
            if (!token.empty()) {
                stack.push(std::stoi(token));
                token.clear();
            }
            continue;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int rh = stack.pop();
            int lh = stack.pop();
            int res;
            if (ch == '+') res = lh + rh;
            else if (ch == '-') res = lh - rh;
            else if (ch == '*') res = lh * rh;
            else if (ch == '/') res = lh / rh;
            stack.push(res);
        }
    }
    if (!token.empty()) {
        stack.push(std::stoi(token));
    }
    return stack.pop();
}

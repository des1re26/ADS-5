// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"
std::string infx2pstfx(const std::string& inf) {
    TStack<char> stack;
    std::string output;
    auto priority = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };
    for (char ch : inf) {
        if (std::isdigit(ch)) {
            output += ch;
            continue;
        }
        if (ch == '(') {
            stack.push(ch);
            continue;
        }
        if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                output += ' ';
                output += stack.pop();
            }
            if (!stack.isEmpty()) stack.pop();
            continue;
        }
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            output += ' ';
            while (!stack.isEmpty() && stack.top() != '(' && priority(stack.top()) >= priority(ch)) {
                output += ' ';
                output += stack.pop();
            }
            stack.push(ch);
            continue;
        }
    }
    while (!stack.isEmpty()) {
        output += ' ';
        output += stack.pop();
    }
    return output;
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

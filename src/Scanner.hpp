#ifndef SCANNER_H
#define SCANNER_H

#include <vector>
#include <iostream>
#include "Token.hpp"

class Scanner {
    public:
        Scanner(const string& src);
        bool isAtEnd();
        const char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, string literal);
        void scanToken();
        void print();
        bool getErrStatus();
        int skipCommentIndex();
        string getStringLiteral();
        string getNumberLiteral();
        bool isDigit(char c);
        bool isDouble(const string&);

    private:
        string src;
        vector<Token*> tokens;
        int start = 0;
        int current = 0;
        int line = 1;
        bool isError = false;
};

#endif 
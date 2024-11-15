#include "token.hpp"
#include <cctype>
#include <iostream>

Token Token_stream::pop() {
  if (hasbuf) {
    Token tok = buffer;
    hasbuf = false;
    return tok;
  }

  char ch;
  do {
    ch = std::cin.get();

    if (isdigit(ch)) {
      Token token = {NUM};
      std::cin.unget();
      std::cin >> token.value;
      return token;
    }

    switch (ch) {
      case '+':
        return Token{ADD};
      case '-':
        return Token{SUB};
      case '*':
        return Token{MUT};
      case '/':
        return Token{DIV};
      case '^':
        return Token{POW};
      case 'e':
      case 'E':
        return Token{EXP};
      case '(':
        return Token{L_PAR};
      case ')':
        return Token{R_PAR};
      default:
        break;
    }

  } while (ch != '\n');

  return Token{END};
}

Token Token_stream::peek() {
  if (hasbuf)
    return buffer;
  else {
    buffer = pop();
    hasbuf = true;
    return buffer;
  }
}

void Token_stream::clear() {
  while (peek().type != END) {
    pop();
  }
  hasbuf = false;
}

void Token_stream::putback(Token k) {
  buffer = k, hasbuf = true;
}
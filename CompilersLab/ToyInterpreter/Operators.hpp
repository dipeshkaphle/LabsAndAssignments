#pragma once
#include <string>
#include <unordered_map>
enum Op { PLUS, MINUS, MUL, DIV, LT, GT, LE, GE, EQ, NEQ };

inline std::string to_str(Op o) {
  std::unordered_map<Op, std::string> mp{
      {PLUS, "+"}, {MINUS, "-"},
      {MUL, "*"},  {DIV, "/"},
      {LT, "<"},   {GT, ">"},
      {LE, "<="},  {GE, ">="},
      {EQ, "="},   {NEQ, "(compose1 not =)"}};
  return mp[o];
}

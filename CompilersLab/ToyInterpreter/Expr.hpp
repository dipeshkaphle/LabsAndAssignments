#pragma once
#include "./Operators.hpp"
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

using namespace std::string_literals;

using lang_type = std::variant<bool, double>;

enum Type { BOOL, DOUBLE, MISMATCH };

#define BINOP(l, op, r, tp) std::get<tp>(l) op std::get<tp>(r)

inline Type is_same_type(const std::variant<bool, double> &a,
                         const std::variant<bool, double> &b) {
  if (std::holds_alternative<bool>(a) && std::holds_alternative<bool>(b)) {
    return BOOL;
  }
  if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
    return DOUBLE;
  return MISMATCH;
}

struct Env {
  static inline std::vector<std::unordered_map<std::string, lang_type>>
      symtab{};
  static void push_frame() { symtab.emplace_back(); }
  static void pop_frame() { symtab.pop_back(); }
  static lang_type get(const std::string &symbol) {
    for (auto it = symtab.rbegin(); it != symtab.rend(); advance(it, 1)) {
      if (it->count(symbol)) {
        return it->at(symbol);
      }
    }
    throw std::runtime_error((symbol + " not found").c_str());
  }
  static void set(const std::string &sym, lang_type data) {
    if (symtab.empty())
      symtab.emplace_back();
    symtab.back().insert({sym, data});
  }
};

struct Expr {
  virtual ~Expr() = default;
  virtual std::variant<bool, double> eval() = 0;
  virtual std::string s_exp() = 0;

  std::string eval_to_string() {
    auto ans = this->eval();
    if (std::holds_alternative<bool>(ans)) {
      return std::get<bool>(ans) ? "#t" : "#f";
    }
    if (std::holds_alternative<double>(ans)) {
      return std::to_string(std::get<double>(ans));
    }
  }
};

struct Neg : Expr {
  Expr *e;
  Neg(Expr *e) : e(e) {}
  ~Neg() { delete e; }
  virtual std::variant<bool, double> eval() {
    auto ans = e->eval();
    if (std::holds_alternative<bool>(ans)) {
      return (double)-((std::get<bool>(ans)) ? 1 : 0);
    }
    if (std::holds_alternative<double>(ans)) {
      return -(std::get<double>(ans));
    }
  }
  virtual std::string s_exp() { return "("s + "- "s + e->s_exp() + " )"s; }
};

struct Assign : Expr {
  std::string symbol;
  Expr *exp;
  Assign(std::string sym, Expr *e) : symbol(move(sym)), exp(e) {}
  ~Assign() { delete exp; }

  virtual std::variant<bool, double> eval() {
    Env::set(symbol, exp->eval());
    return Env::get(symbol);
  }
  virtual std::string s_exp() {
    return "(define " + symbol + " " + exp->s_exp() + " )";
  }
};

struct Var : Expr {
  std::string symbol;
  Var(std::string sym) : symbol(move(sym)) {}
  ~Var() = default;

  virtual std::variant<bool, double> eval() { return Env::get(symbol); }
  virtual std::string s_exp() { return symbol; }
};
struct Literal : Expr {
  lang_type lit;
  Literal(lang_type sym) : lit(move(sym)) {}
  ~Literal() = default;

  virtual std::variant<bool, double> eval() { return lit; }
  virtual std::string s_exp() {
    if (std::holds_alternative<bool>(lit)) {
      return std::get<bool>(lit) ? "#t"s : "#f"s;
    }
    if (std::holds_alternative<double>(lit)) {
      return std::to_string(std::get<double>(lit));
    }
  }
};

struct BinaryExpr : Expr {
  Expr *lhs;
  Expr *rhs;
  Op op;
  BinaryExpr(Expr *l, Expr *r, Op o) : lhs(l), rhs(r), op(o) {}
  ~BinaryExpr() {
    delete lhs;
    delete rhs;
  }
  virtual std::variant<bool, double> eval() {
    auto l = lhs->eval();
    auto r = rhs->eval();
    auto t = is_same_type(l, r);
    if (t == MISMATCH) {
      throw std::runtime_error("Type mismatch");
    }
    if (t == DOUBLE) {
      if (op == PLUS)
        return BINOP(l, +, r, double);
      if (op == MINUS)
        return BINOP(l, -, r, double);
      if (op == MUL)
        return BINOP(l, *, r, double);
      if (op == DIV)
        return BINOP(l, /, r, double);
      if (op == LT)
        return BINOP(l, <, r, double);
      if (op == LE)
        return BINOP(l, <=, r, double);
      if (op == GT)
        return BINOP(l, >, r, double);
      if (op == GE)
        return BINOP(l, >=, r, double);
      if (op == EQ)
        return BINOP(l, ==, r, double);
      if (op == NEQ)
        return BINOP(l, !=, r, double);
    } else {
      if (op == EQ)
        return BINOP(l, ==, r, bool);
      if (op == NEQ)
        return BINOP(l, !=, r, bool);
      throw std::runtime_error(
          (to_str(op) + " cant be applied to boolean values").c_str());
    }
  }
  virtual std::string s_exp() {
    return "( "s + to_str(this->op) + " " + lhs->s_exp() + " " + rhs->s_exp() +
           " )"s;
  }
};

#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <cstdlib>
#include <cstring>
#include <string_view>
#include <vector>
#include <cassert>
#include <memory>
#include <optional>

//
// トークナイザ
//

// トークンの種類
enum class TokenKind
{
    TK_RESERVED, // 記号
    TK_IDENT,    // 識別子
    TK_NUM,      // 整数トークン
    TK_EOF,      // 入力終わりを表すトークン
};

// トークン型
struct Token
{
    TokenKind kind;       // トークンの型
    int val;              // kindがTK_NUMの場合、その数値
    std::string_view str; // トークン文字列
};

void error(const char *fmt, ...);
void error_at(std::string_view loc, std::string_view user_input, const char *fmt, ...);
std::vector<std::unique_ptr<Token>> tokenize(std::string_view user_input);

//
// パーサ
//

// ASTのノードの種類
enum class NodeKind
{
    ND_ADD,     // +
    ND_SUB,     // -
    ND_MUL,     // *
    ND_DIV,     // /
    ND_EQ,      // ==
    ND_NE,      // !=
    ND_LT,      // <
    ND_LE,      // <=
    ND_ASSIGN,  // =
    ND_LVAR,    // ローカル変数
    ND_NUM,     // 整数
    ND_RETURN,  // return
    ND_IF,      // if
    ND_WHILE,   // while
    ND_FOR,     // for
    ND_BLOCK,   // {...}
    ND_FUNCALL, // call function
    ND_ADDR,    // unary &
    ND_DEREF    // unary *
};

// ASTのノードの型
struct Node
{
    NodeKind kind;             // ノードの型
    std::unique_ptr<Node> lhs; // 左辺
    std::unique_ptr<Node> rhs; // 右辺
    int val;                   // kindがND_NUMの場合のみ使う
    int offset;                // kindがND_LVARの場合のみ使う
    int stack_size;
    std::string_view funcname;
    std::vector<std::unique_ptr<Node>> args;

    // if,while,for文
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> then;
    std::unique_ptr<Node> els;
    std::unique_ptr<Node> init;
    std::unique_ptr<Node> inc;

    // {...}
    std::vector<std::unique_ptr<Node>> body;

    std::vector<std::unique_ptr<Node>> function;
};

std::vector<std::unique_ptr<Node>> program(const std::vector<std::unique_ptr<Token>> &_head, std::string_view user_input);

//
// ASTをアセンブリで表記
//

void gen(const Node &node);

#include <gtest/gtest.h>

#include "9cc.hpp"

#include <string_view>

// 整数をパースするテスト
TEST(ParseTest, HandlesInteger)
{
    {
        std::string_view user_input = "int main() {return 0;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);
    }

    {
        std::string_view user_input = "int main() {return 42;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 42);
    }
}

// 四則演算の式をパースするテスト
TEST(ParseTest, HandlesCalculation)
{
    {
        std::string_view user_input = "int main() {return 5+20-4;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_SUB);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->lhs->val, 5);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->rhs->val, 20);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 4);
    }

    {
        std::string_view user_input = "int main() {return 5+6*7;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 5);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_MUL);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->lhs->val, 6);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->rhs->val, 7);
    }
}

// 単項演算子をパースするテスト
TEST(ParseTest, HandlesUnary)
{
    {
        std::string_view user_input = "int main() {return -10+20;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_SUB);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->rhs->val, 10);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 20);
    }

    {
        std::string_view user_input = "int main() {return - +10;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_SUB);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 10);
    }
}

// 比較演算子をパースするテスト
TEST(ParseTest, HandlesLogicalOperator)
{
    {
        std::string_view user_input = "int main() {return 0==1;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_EQ);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 1);
    }

    {
        std::string_view user_input = "int main() {return 42!=42;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_NE);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 42);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 42);
    }

    {
        std::string_view user_input = "int main() {return 42!=23;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_NE);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 42);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 23);
    }

    {
        std::string_view user_input = "int main() {return 0<1;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LT);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 1);
    }

    {
        std::string_view user_input = "int main() {return 0<=1;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LE);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 1);
    }

    {
        std::string_view user_input = "int main() {return 1>0;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LT);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 1);
    }

    {
        std::string_view user_input = "int main() {return 1>=0;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LE);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->val, 1);
    }
}

// 一文字のローカル変数をパースするテスト
TEST(ParseTest, HandlesOneLocalVer)
{
    {
        std::string_view user_input = "int main() {return 3; 2; 3;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 2);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->val, 3);
    }

    {
        std::string_view user_input = "int main() {a=3; z=5; return a+z;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->val, 5);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->rhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->rhs->offset, 16);
    }
}

// 複数文字のローカル変数をパースするテスト
TEST(ParseTest, HandlesMultiLocalVer)
{
    {
        std::string_view user_input = "int main() {foo=1; bar=2+3; return foo+bar;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 1);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->lhs->val, 2);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->rhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->rhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->rhs->offset, 16);
    }
}

// 制御構文をパースするテスト
TEST(ParseTest, HandlesControlSyntax)
{
    {
        std::string_view user_input = "int main() {if (0) return 2; return 3;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_IF);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->val, 2);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->val, 3);
    }

    {
        std::string_view user_input = "int main() {if (2-1) return 2; return 3;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_IF);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->kind, NodeKind::ND_SUB);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->lhs->val, 2);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->rhs->val, 1);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->val, 2);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->val, 3);
    }

    {
        std::string_view user_input = "int main() {if (0) return 2; else return 3;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_IF);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->cond->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->val, 2);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->els->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->els->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->els->lhs->val, 3);
    }

    {
        std::string_view user_input = "int main() {i=0; while(i<10) i=i+1; return i;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_WHILE);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->cond->kind, NodeKind::ND_LT);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->cond->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->cond->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->cond->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->cond->rhs->val, 10);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->rhs->kind, NodeKind::ND_ADD);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->rhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->rhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->rhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->rhs->rhs->val, 1);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->offset, 8);
    }

    {
        std::string_view user_input = "int main() {i=0; j=0; for (i=0; i<=10; i=i+1) j=i+j; return j;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_FOR);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->init->kind, NodeKind::ND_ASSIGN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->init->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->init->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->init->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->init->rhs->offset, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->kind, NodeKind::ND_LE);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->rhs->val, 10);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->rhs->kind, NodeKind::ND_ADD);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->rhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->rhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->rhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->inc->rhs->rhs->val, 1);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->rhs->kind, NodeKind::ND_ADD);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->rhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->rhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->rhs->rhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->rhs->rhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->lhs->offset, 16);
    }

    {
        std::string_view user_input = "int main() {for (;;) return 3; return 5;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_FOR);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->then->lhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->val, 5);
    }
}

// ブロックをパースするテスト
TEST(ParseTest, HandlesBlock)
{

    {
        std::string_view user_input = "int main() {{return 0;}}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(0)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(0)->val, 0);
    }

    {
        std::string_view user_input = "int main() {{1; {2;} return 3;}}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(0)->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(0)->val, 1);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(1)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(1)->body.at(0)->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(1)->body.at(0)->val, 2);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(2)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->body.at(2)->lhs->val, 3);
    }

    {
        std::string_view user_input = "int main() {i=0; j=0; while(i<=10) {j=i+j; i=i+1;} return j;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_WHILE);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->kind, NodeKind::ND_LE);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->cond->rhs->val, 10);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->rhs->kind, NodeKind::ND_ADD);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->rhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->rhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->rhs->rhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(0)->rhs->rhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->rhs->kind, NodeKind::ND_ADD);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->rhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->rhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->rhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->then->body.at(1)->rhs->rhs->val, 1);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->lhs->offset, 16);
    }
}

// 関数をパースするテスト
TEST(ParseTest, HandlesCallFunction)
{
    {
        std::string_view user_input = "int main() {return ret3();}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_FUNCALL);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->funcname, "ret3");
    }

    {
        std::string_view user_input = "int main() {return add(3, 5);}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_FUNCALL);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->funcname, "add");

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->args.at(0)->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->args.at(0)->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->args.at(1)->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->args.at(1)->val, 5);
    }

    {
        std::string_view user_input = "int main() {foo = 3; bar = 5; return add(foo, bar);}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->val, 5);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_FUNCALL);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->funcname, "add");

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(0)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(0)->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(1)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(1)->offset, 16);
    }
}

// 関数定義をパースするテスト
TEST(ParseTest, HandlesFuncDefinition)
{
    {
        std::string_view user_input = "int main() {return ret3();} int ret3() { return 3; }";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_FUNCALL);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->funcname, "ret3");

        ASSERT_EQ(parsed.at(1)->funcname, "ret3");

        ASSERT_EQ(parsed.at(1)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->val, 3);
    }

    {
        std::string_view user_input = "int main() {foo = 3; bar = 5; return add(foo, bar);} int add(foo, bar) { return foo + bar; }";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->val, 5);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_FUNCALL);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->funcname, "add");

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(0)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(0)->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(1)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->args.at(1)->offset, 16);

        ASSERT_EQ(parsed.at(1)->funcname, "add");

        ASSERT_EQ(parsed.at(1)->args.at(0)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->args.at(0)->offset, 8);

        ASSERT_EQ(parsed.at(1)->args.at(1)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->args.at(1)->offset, 16);

        ASSERT_EQ(parsed.at(1)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->rhs->offset, 16);
    }

    {
        std::string_view user_input = "int add(foo, bar) { return foo + bar; } int main() {foo = 3; bar = 5; return add(foo, bar);}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "add");

        ASSERT_EQ(parsed.at(0)->args.at(0)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->args.at(0)->offset, 8);

        ASSERT_EQ(parsed.at(0)->args.at(1)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->args.at(1)->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_ADD);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->rhs->offset, 16);

        ASSERT_EQ(parsed.at(1)->funcname, "main");

        ASSERT_EQ(parsed.at(1)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->rhs->val, 3);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->rhs->val, 5);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_FUNCALL);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(2)->lhs->funcname, "add");

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(2)->lhs->args.at(0)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(2)->lhs->args.at(0)->offset, 8);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(2)->lhs->args.at(1)->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(2)->lhs->args.at(1)->offset, 16);
    }
}

// 単項&と単項*をパースするテスト
TEST(ParseTest, HandlesAdDer)
{
    {
        std::string_view user_input = "int main() {x=8; y=&x; return *y;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_ADDR);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_DEREF);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->lhs->offset, 16);
    }

    {
        std::string_view user_input = "int main() {x=3; y=5; z=&y+8; return *z;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->rhs->val, 5);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->offset, 24);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->rhs->kind, NodeKind::ND_ADD);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->rhs->lhs->kind, NodeKind::ND_ADDR);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->rhs->lhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->rhs->lhs->lhs->offset, 16);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->rhs->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->rhs->rhs->val, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->lhs->kind, NodeKind::ND_DEREF);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->lhs->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(3)->lhs->lhs->offset, 24);
    }
}

// 戻り値のないreturn文をパースするテスト
TEST(ParseTest, HandlesNoValReturn)
{
    {
        std::string_view user_input = "int main() {i=0; if(1){i=3; return;} return i;}";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "main");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->rhs->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->kind, NodeKind::ND_IF);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->cond->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->cond->val, 1);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->body.at(0)->kind, NodeKind::ND_ASSIGN);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->body.at(0)->val, 0);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->body.at(0)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->body.at(0)->lhs->offset, 8);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->body.at(0)->rhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->body.at(0)->rhs->val, 3);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(1)->then->body.at(1)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->kind, NodeKind::ND_LVAR);
        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(2)->lhs->offset, 8);
    }

    {
        std::string_view user_input = "int foo() { return; } int main() { foo(); return 42; }";
        std::vector<std::unique_ptr<Node>> parsed = program(tokenize(user_input), user_input);

        ASSERT_EQ(parsed.at(0)->funcname, "foo");

        ASSERT_EQ(parsed.at(0)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(0)->function.at(0)->body.at(0)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(1)->funcname, "main");

        ASSERT_EQ(parsed.at(1)->function.at(0)->kind, NodeKind::ND_BLOCK);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->kind, NodeKind::ND_FUNCALL);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(0)->funcname, "foo");

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->kind, NodeKind::ND_RETURN);

        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->lhs->kind, NodeKind::ND_NUM);
        ASSERT_EQ(parsed.at(1)->function.at(0)->body.at(1)->lhs->val, 42);
    }
}

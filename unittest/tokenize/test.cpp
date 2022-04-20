#include <gtest/gtest.h>

#include "9cc.hpp"

#include <string_view>

// 整数をトークナイズするテスト
TEST(TokenizeTest, HandlesInteger)
{
    {
        std::string_view user_input = "int main() {return 0;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 0);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, ";");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 42;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 42);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, ";");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, "}");
    }
}

// 四則演算の式をトークナイズするテスト
TEST(TokenizeTest, HandlesCalculation)
{
    {
        std::string_view user_input = "int main() {return 5+20-4;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 5);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "+");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 20);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, "-");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(10)->val, 4);

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, ";");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 5+6*7;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 5);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "+");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 6);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, "*");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(10)->val, 7);

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, ";");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "}");
    }
}

// 単項演算子をトークナイズするテスト
TEST(TokenizeTest, HandlesUnary)
{
    {
        std::string_view user_input = "int main() {return -10+20;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "-");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 10);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, "+");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(9)->val, 20);

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, ";");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return - +10;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "-");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "+");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 10);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }
}

// 比較演算子をトークナイズするテスト
TEST(TokenizeTest, HandlesLogicalOperator)
{
    {
        std::string_view user_input = "int main() {return 0==1;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 0);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "==");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 1);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 42!=42;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 42);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "!=");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 42);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 42!=23;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 42);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "!=");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 23);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 0<1;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 0);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "<");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 1);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 0<=1;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 0);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "<=");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 1);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 1>0;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 1);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, ">");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 0);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return 1>=0;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 1);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, ">=");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 0);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }
}

// 一文字のローカル変数をトークナイズするテスト
TEST(TokenizeTest, HandlesOneLocalVer)
{

    {
        std::string_view user_input = "int main() {return 3; 2; 3;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 3);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, ";");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 2);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(10)->val, 3);

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, ";");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "}");
    }

    {
        std::string_view user_input = "int main() {a=3; z=5; return a+z;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "a");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 3);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "z");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 5);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "return");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(14)->str, "a");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "+");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(16)->str, "z");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, ";");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, "}");
    }
}

// 複数文字のローカル変数をトークナイズするテスト
TEST(TokenizeTest, HandlesMultiLocalVer)
{
    {
        std::string_view user_input = "int main() {foo=1; bar=2+3; return foo+bar;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "foo");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 1);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "bar");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 2);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "+");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(13)->val, 3);

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, ";");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "return");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(16)->str, "foo");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, "+");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(18)->str, "bar");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, ";");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, "}");
    }
}

// 制御構文をトークナイズするテスト
TEST(TokenizeTest, HandlesControlSyntax)
{
    {
        std::string_view user_input = "int main() {if (0) return 2; return 3;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "if");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "(");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 0);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ")");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, "return");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(10)->val, 2);

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, ";");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "return");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(13)->val, 3);

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, ";");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "}");
    }

    {
        std::string_view user_input = "int main() {if (2-1) return 2; return 3;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "if");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "(");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 2);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, "-");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(9)->val, 1);

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, ")");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, "return");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(12)->val, 2);

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, ";");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, "return");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(15)->val, 3);

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, ";");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, "}");
    }

    {
        std::string_view user_input = "int main() {if (0) return 2; else return 3;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "if");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "(");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 0);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ")");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, "return");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(10)->val, 2);

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, ";");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "else");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "return");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(14)->val, 3);

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, ";");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "}");
    }

    {
        std::string_view user_input = "int main() {i=0; while(i<10) i=i+1; return i;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "i");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 0);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, "while");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "(");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(11)->str, "i");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "<");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(13)->val, 10);

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, ")");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(15)->str, "i");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "=");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(17)->str, "i");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, "+");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(19)->val, 1);

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, ";");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(21)->str, "return");

        ASSERT_EQ(tok.at(22)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(22)->str, "i");

        ASSERT_EQ(tok.at(23)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(23)->str, ";");

        ASSERT_EQ(tok.at(24)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(24)->str, "}");
    }

    {
        std::string_view user_input = "int main() {i=0; j=0; for (i=0; i<=10; i=i+1) j=i+j; return j;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "i");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 0);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "j");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 0);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "for");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, "(");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(15)->str, "i");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "=");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(17)->val, 0);

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, ";");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(19)->str, "i");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, "<=");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(21)->val, 10);

        ASSERT_EQ(tok.at(22)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(22)->str, ";");

        ASSERT_EQ(tok.at(23)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(23)->str, "i");

        ASSERT_EQ(tok.at(24)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(24)->str, "=");

        ASSERT_EQ(tok.at(25)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(25)->str, "i");

        ASSERT_EQ(tok.at(26)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(26)->str, "+");

        ASSERT_EQ(tok.at(27)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(27)->val, 1);

        ASSERT_EQ(tok.at(28)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(28)->str, ")");

        ASSERT_EQ(tok.at(29)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(29)->str, "j");

        ASSERT_EQ(tok.at(30)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(30)->str, "=");

        ASSERT_EQ(tok.at(31)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(31)->str, "i");

        ASSERT_EQ(tok.at(32)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(32)->str, "+");

        ASSERT_EQ(tok.at(33)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(33)->str, "j");

        ASSERT_EQ(tok.at(34)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(34)->str, ";");

        ASSERT_EQ(tok.at(35)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(35)->str, "return");

        ASSERT_EQ(tok.at(36)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(36)->str, "j");

        ASSERT_EQ(tok.at(37)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(37)->str, ";");

        ASSERT_EQ(tok.at(38)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(38)->str, "}");
    }

    {
        std::string_view user_input = "int main() {for (;;) return 3; return 5;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "for");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "(");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, ";");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ")");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "return");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 3);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "return");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(14)->val, 5);

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, ";");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "}");
    }
}

// ブロックをトークナイズするテスト
TEST(TokenizeTest, HandlesBlocks)
{
    {
        std::string_view user_input = "int main() {{return 1;}}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "{");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "return");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 1);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, "}");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {{1; {2;} return 3;}}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "{");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(6)->val, 1);

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, ";");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, "{");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(9)->val, 2);

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, ";");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, "}");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "return");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(13)->val, 3);

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, ";");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "}");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "}");
    }

    {
        std::string_view user_input = "int main() {i=0; j=0; while(i<=10) {j=i+j; i=i+1;} return j;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "i");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 0);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "j");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 0);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "while");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, "(");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(15)->str, "i");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "<=");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(17)->val, 10);

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, ")");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, "{");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(20)->str, "j");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(21)->str, "=");

        ASSERT_EQ(tok.at(22)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(22)->str, "i");

        ASSERT_EQ(tok.at(23)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(23)->str, "+");

        ASSERT_EQ(tok.at(24)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(24)->str, "j");

        ASSERT_EQ(tok.at(25)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(25)->str, ";");

        ASSERT_EQ(tok.at(26)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(26)->str, "i");

        ASSERT_EQ(tok.at(27)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(27)->str, "=");

        ASSERT_EQ(tok.at(28)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(28)->str, "i");

        ASSERT_EQ(tok.at(29)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(29)->str, "+");

        ASSERT_EQ(tok.at(30)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(30)->val, 1);

        ASSERT_EQ(tok.at(31)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(31)->str, ";");

        ASSERT_EQ(tok.at(32)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(32)->str, "}");

        ASSERT_EQ(tok.at(33)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(33)->str, "return");

        ASSERT_EQ(tok.at(34)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(34)->str, "j");

        ASSERT_EQ(tok.at(35)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(35)->str, ";");

        ASSERT_EQ(tok.at(36)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(36)->str, "}");
    }
}

// 関数をトークナイズするテスト
TEST(TokenizeTest, HandlesCallFunction)
{
    {
        std::string_view user_input = "int main() {return ret3();}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(6)->str, "ret3");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "(");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ")");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");
    }

    {
        std::string_view user_input = "int main() {return add(3, 5);}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(6)->str, "add");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "(");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(8)->val, 3);

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ",");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(10)->val, 5);

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, ")");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "}");
    }

    {
        std::string_view user_input = "int main() {foo = 3; bar = 5; return add(foo, bar);}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "foo");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 3);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "bar");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 5);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "return");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(14)->str, "add");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "(");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(16)->str, "foo");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, ",");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(18)->str, "bar");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, ")");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, ";");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(21)->str, "}");
    }
}

// 関数定義をトークナイズするテスト
TEST(TokenizeTest, HandlesFuncDefinition)
{
    {
        std::string_view user_input = "int main() {return ret3();} int ret3() { return 3; }";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(6)->str, "ret3");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "(");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ")");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, ";");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "}");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(11)->str, "int");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(12)->str, "ret3");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "(");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, ")");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "{");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "return");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(17)->val, 3);

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, ";");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, "}");
    }

    {
        std::string_view user_input = "int main() {foo = 3; bar = 5; return add(foo, bar);} int add(foo, bar) { return foo + bar; }";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "foo");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 3);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "bar");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 5);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "return");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(14)->str, "add");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "(");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(16)->str, "foo");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, ",");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(18)->str, "bar");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, ")");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, ";");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(21)->str, "}");

        ASSERT_EQ(tok.at(22)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(22)->str, "int");

        ASSERT_EQ(tok.at(23)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(23)->str, "add");

        ASSERT_EQ(tok.at(24)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(24)->str, "(");

        ASSERT_EQ(tok.at(25)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(25)->str, "foo");

        ASSERT_EQ(tok.at(26)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(26)->str, ",");

        ASSERT_EQ(tok.at(27)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(27)->str, "bar");

        ASSERT_EQ(tok.at(28)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(28)->str, ")");

        ASSERT_EQ(tok.at(29)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(29)->str, "{");

        ASSERT_EQ(tok.at(30)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(30)->str, "return");

        ASSERT_EQ(tok.at(31)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(31)->str, "foo");

        ASSERT_EQ(tok.at(32)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(32)->str, "+");

        ASSERT_EQ(tok.at(33)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(33)->str, "bar");

        ASSERT_EQ(tok.at(34)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(34)->str, ";");

        ASSERT_EQ(tok.at(35)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(35)->str, "}");
    }

    {
        std::string_view user_input = "int add(foo, bar) { return foo + bar; } int main() {foo = 3; bar = 5; return add(foo, bar);}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(1)->str, "add");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(3)->str, "foo");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, ",");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "bar");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, ")");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "{");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, "return");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "foo");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "+");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(11)->str, "bar");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "}");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(14)->str, "int");

        ASSERT_EQ(tok.at(15)->str, "main");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, "(");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, ")");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, "{");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(19)->str, "foo");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, "=");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(21)->val, 3);

        ASSERT_EQ(tok.at(22)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(22)->str, ";");

        ASSERT_EQ(tok.at(23)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(23)->str, "bar");

        ASSERT_EQ(tok.at(24)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(24)->str, "=");

        ASSERT_EQ(tok.at(25)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(25)->val, 5);

        ASSERT_EQ(tok.at(26)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(26)->str, ";");

        ASSERT_EQ(tok.at(27)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(27)->str, "return");

        ASSERT_EQ(tok.at(28)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(28)->str, "add");

        ASSERT_EQ(tok.at(29)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(29)->str, "(");

        ASSERT_EQ(tok.at(30)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(30)->str, "foo");

        ASSERT_EQ(tok.at(31)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(31)->str, ",");

        ASSERT_EQ(tok.at(32)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(32)->str, "bar");

        ASSERT_EQ(tok.at(33)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(33)->str, ")");

        ASSERT_EQ(tok.at(34)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(34)->str, ";");

        ASSERT_EQ(tok.at(35)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(35)->str, "}");
    }
}

// 単項&と単項*をトークナイズするテスト
TEST(TokenizeTest, HandlesAdDer)
{
    {
        std::string_view user_input = "int main() {x=8; y=&x; return *y;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "x");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 8);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "y");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, "&");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(12)->str, "x");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, ";");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, "return");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "*");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(16)->str, "y");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, ";");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, "}");
    }

    {
        std::string_view user_input = "int main() {x=3; y=5; z=&y+8; return *z;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "x");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 3);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(9)->str, "y");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "=");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 5);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ";");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(13)->str, "z");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, "=");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "&");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(16)->str, "y");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, "+");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(18)->val, 8);

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, ";");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, "return");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(21)->str, "*");

        ASSERT_EQ(tok.at(22)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(22)->str, "z");

        ASSERT_EQ(tok.at(23)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(23)->str, ";");

        ASSERT_EQ(tok.at(24)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(24)->str, "}");
    }
}

// 戻り値のないreturn文をトークナイズするテスト
TEST(TokenizeTest, HandlesNoValReturn)
{
    {
        std::string_view user_input = "int main() {i=0; if(1){i=3; return;} return i;}";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "main");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(5)->str, "i");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, "=");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(7)->val, 0);

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(8)->str, ";");

        ASSERT_EQ(tok.at(9)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(9)->str, "if");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "(");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(11)->val, 1);

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, ")");

        ASSERT_EQ(tok.at(13)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(13)->str, "{");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(14)->str, "i");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, "=");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(16)->val, 3);

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, ";");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(18)->str, "return");

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, ";");

        ASSERT_EQ(tok.at(20)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(20)->str, "}");

        ASSERT_EQ(tok.at(21)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(21)->str, "return");

        ASSERT_EQ(tok.at(22)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(22)->str, "i");

        ASSERT_EQ(tok.at(23)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(23)->str, ";");
    }

    {
        std::string_view user_input = "int foo() { return; } int main() { foo(); return 42; }";

        std::vector<std::unique_ptr<Token>> tok = tokenize(user_input);

        ASSERT_EQ(tok.at(0)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(0)->str, "int");

        ASSERT_EQ(tok.at(1)->str, "foo");

        ASSERT_EQ(tok.at(2)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(2)->str, "(");

        ASSERT_EQ(tok.at(3)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(3)->str, ")");

        ASSERT_EQ(tok.at(4)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(4)->str, "{");

        ASSERT_EQ(tok.at(5)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(5)->str, "return");

        ASSERT_EQ(tok.at(6)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(6)->str, ";");

        ASSERT_EQ(tok.at(7)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(7)->str, "}");

        ASSERT_EQ(tok.at(8)->kind, TokenKind::TK_IDENT);
        ASSERT_EQ(tok.at(8)->str, "int");

        ASSERT_EQ(tok.at(9)->str, "main");

        ASSERT_EQ(tok.at(10)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(10)->str, "(");

        ASSERT_EQ(tok.at(11)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(11)->str, ")");

        ASSERT_EQ(tok.at(12)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(12)->str, "{");

        ASSERT_EQ(tok.at(13)->str, "foo");

        ASSERT_EQ(tok.at(14)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(14)->str, "(");

        ASSERT_EQ(tok.at(15)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(15)->str, ")");

        ASSERT_EQ(tok.at(16)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(16)->str, ";");

        ASSERT_EQ(tok.at(17)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(17)->str, "return");

        ASSERT_EQ(tok.at(18)->kind, TokenKind::TK_NUM);
        ASSERT_EQ(tok.at(18)->val, 42);

        ASSERT_EQ(tok.at(19)->kind, TokenKind::TK_RESERVED);
        ASSERT_EQ(tok.at(19)->str, ";");
    }
}

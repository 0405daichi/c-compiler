#include "9cc.hpp"

std::unique_ptr<Token> new_token(TokenKind kind, std::string_view str, int len);

bool startswith(std::string_view p, std::string_view q);

bool is_ident1(const char c);

bool is_ident2(const char c);

bool is_alpha(const char c);

bool is_alnum(const char c);

std::string symbol_reserved(std::string_view p);

// エラーを報告するための関数
// printfと同じ引数を取る
void error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// エラー箇所を明示するための関数
void error_at(std::string_view loc, std::string_view user_input, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    int pos = user_input.find(loc);
    fprintf(stderr, "%s\n", user_input.data());
    fprintf(stderr, "%*s", pos, ""); // pos個の空白を出力
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// 新しいトークンを作成してcurに繋げる
std::unique_ptr<Token> new_token(TokenKind kind, std::string_view str, int len)
{
    auto tok = std::make_unique<Token>();
    if (kind == TokenKind::TK_NUM)
    {
        char *pos;
        tok->val = strtol(str.data(), &pos, 10);
        str = std::string_view(pos);
        tok->kind = kind;
        return tok;
    }
    tok->kind = kind;
    tok->str = str.substr(0, len);
    return tok;
}

bool startswith(std::string_view p, std::string_view q)
{
    return p.find(q) == 0;
}

bool is_ident1(const char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool is_ident2(const char c)
{
    return is_ident1(c) || ('0' <= c && c <= '9');
}

bool is_alpha(const char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_');
}

bool is_alnum(const char c)
{
    return isalpha(c) || ('0' <= c && c <= '9');
}

std::string symbol_reserved(std::string_view p)
{
    std::vector<std::string> kw = {"return", "if", "else", "while", "for"};

    for (std::size_t i = 0; i < kw.size(); i++)
    {
        int len = kw[i].size();
        if (startswith(p, kw[i]) && !is_alnum(p[len]))
            return kw[i];
    }

    std::vector<std::string> symbol = {"==", "!=", "<=", ">="};

    for (std::size_t i = 0; i < symbol.size(); i++)
    {
        if (startswith(p, symbol[i]))
            return symbol[i];
    }

    return "";
}

// user_inputをトークナイズしてそれを返す
std::vector<std::unique_ptr<Token>> tokenize(std::string_view user_input)
{
    std::string_view p = user_input;
    std::vector<std::unique_ptr<Token>> tokens;

    while (!p.empty())
    {
        if (std::isspace(p[0]))
        {
            p.remove_prefix(1);
            continue;
        }

        std::string kw = symbol_reserved(p);
        if (!kw.empty())
        {
            int len = kw.size();
            tokens.emplace_back(new_token(TokenKind::TK_RESERVED, p, len));
            p.remove_prefix(len);
            kw.clear();
            continue;
        }

        if (std::strchr("+-*/()<>;={},&", p[0]))
        {
            tokens.emplace_back(new_token(TokenKind::TK_RESERVED, p, 1));
            p.remove_prefix(1);
            continue;
        }

        if (std::isdigit(p[0]))
        {
            tokens.emplace_back(new_token(TokenKind::TK_NUM, p, 0));
            char *pos;
            strtol(p.data(), &pos, 10);
            p = std::string_view(pos);
            continue;
        }

        if (is_ident1(p[0]))
        {
            std::string_view q = p;
            int len = 0;
            while (is_ident2(p[0]))
            {
                p.remove_prefix(1);
                len++;
            }
            tokens.emplace_back(new_token(TokenKind::TK_IDENT, q, len));
            continue;
        }

        error_at(p, user_input, "トークナイズできません。");
    }

    return tokens;
}

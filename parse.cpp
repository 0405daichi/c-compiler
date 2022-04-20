#include "9cc.hpp"

// ローカル変数の型
struct LVar
{
    std::string_view name; // 変数名
    int offset;            // RBPからのオフセット
};

struct ParseContext
{
private:
    const std::vector<std::unique_ptr<Token>> &head; // トークナイザ関数の戻り値
    std::size_t cur_token_ = 0;

    std::vector<std::unique_ptr<LVar>> locals;
    int current_offset = 0;

public:
    ParseContext(const std::vector<std::unique_ptr<Token>> &_head) : head(_head) {}

    bool is_valid() const
    {
        return head.size() > cur_token_;
    }

    Token current_token()
    {
        assert(head.size() > cur_token_);
        return *head[cur_token_];
    }

    void next_token()
    {
        cur_token_++;
    }

    std::optional<LVar> find_lvar(const Token &tok)
    {
        for (std::size_t i = 0; i != locals.size(); i++)
        {
            if (locals[i]->name == tok.str)
                return *locals[i];
        }
        return std::nullopt;
    }

    std::optional<LVar> find_argvar()
    {
        if (current_token().str == "int")
            next_token();
        for (std::size_t i = 0; i != locals.size(); i++)
        {
            if (locals[i]->name == current_token().str)
                return *locals[i];
        }
        return std::nullopt;
    }

    int new_var(const Token &tok)
    {
        if (tok.str == "int")
            next_token();
        auto var = std::make_unique<LVar>();
        var->name = tok.str;
        var->offset = current_offset + 8;
        current_offset += 8;
        locals.push_back(std::move(var));
        return current_offset;
    }

    int cur_offset()
    {
        return current_offset;
    }
};

std::unique_ptr<Node> new_node(NodeKind kind);

std::unique_ptr<Node> new_binary(NodeKind kind, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs);

std::unique_ptr<Node> new_num(int val);

std::optional<Token> consume_ident(ParseContext &ctx);

std::vector<std::unique_ptr<Node>> create_arg(ParseContext &ctx, std::string_view user_input);

bool consume(std::string_view op, ParseContext &ctx);

int expect_number(ParseContext &ctx, std::string_view user_input);

void expect(std::string_view op, ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> function(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> stmt(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> expr(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> assign(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> equality(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> relational(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> add(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> mul(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> unary(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> primary(ParseContext &ctx, std::string_view user_input);

std::unique_ptr<Node> new_node(NodeKind kind)
{
    auto node = std::make_unique<Node>();
    node->kind = kind;
    return node;
}

std::unique_ptr<Node> new_binary(NodeKind kind, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
{
    auto node = new_node(kind);
    node->lhs = std::move(lhs);
    node->rhs = std::move(rhs);
    return node;
}

std::unique_ptr<Node> new_num(int val)
{
    auto node = new_node(NodeKind::ND_NUM);
    node->val = val;
    return node;
}

// 現在のトークンが識別子の場合、トークンを一つ読み進めてその値を返す。
// それ以外の場合にはエラーを報告する。
std::optional<Token> consume_ident(ParseContext &ctx)
{
    if (ctx.current_token().str == "int")
        ctx.next_token();

    if (ctx.current_token().kind != TokenKind::TK_IDENT)
        return std::nullopt;
    Token t = ctx.current_token();
    ctx.next_token();
    return t;
}

Token expect_ident(ParseContext &ctx, std::string_view user_input)
{
    if (ctx.current_token().kind != TokenKind::TK_IDENT)
        error_at(ctx.current_token().str, user_input, "関数名ではありません");
    Token t = ctx.current_token();
    ctx.next_token();
    return t;
}

std::vector<std::unique_ptr<Node>> create_arg(ParseContext &ctx, std::string_view user_input)
{
    std::vector<std::unique_ptr<Node>> args;
    if (consume(")", ctx))
        return args;
    while (ctx.current_token().kind == TokenKind::TK_NUM || ctx.current_token().kind == TokenKind::TK_IDENT)
    {
        if (ctx.current_token().kind == TokenKind::TK_IDENT)
        {
            auto arg = new_node(NodeKind::ND_LVAR);

            std::optional<LVar> lvar = ctx.find_argvar();

            if (lvar)
            {
                arg->offset = lvar->offset;
            }
            else
            {
                arg->offset = ctx.new_var(ctx.current_token());
            }

            args.push_back(std::move(arg));
        }
        else
        {
            auto arg = new_node(NodeKind::ND_NUM);

            arg->val = ctx.current_token().val;

            args.push_back(std::move(arg));
        }
        ctx.next_token();
        if (!consume(",", ctx))
            break;
    }
    expect(")", ctx, user_input);
    return args;
}

// 現在のトークンが`op`と同じであればトークンを消費し、真を返す。
// それ以外の場合には偽を返す。
bool consume(std::string_view op, ParseContext &ctx)
{
    if (ctx.current_token().kind != TokenKind::TK_RESERVED || ctx.current_token().str != op)
        return false;
    ctx.next_token();
    return true;
}

// 現在のトークンが数値の場合、トークンを一つ読み進めてその数値を返す。
// それ以外の場合にはエラーを報告する。
int expect_number(ParseContext &ctx, std::string_view user_input)
{
    if (ctx.current_token().kind != TokenKind::TK_NUM)
        error_at(ctx.current_token().str, user_input, "数ではありません");
    int val = ctx.current_token().val;
    ctx.next_token();
    return val;
}

// 現在のトークンが`op`の場合、トークンを一つ読み進めてその数値を返す。
// `op`以外の場合にはエラーを報告する。
void expect(std::string_view op, ParseContext &ctx, std::string_view user_input)
{
    if (ctx.current_token().kind != TokenKind::TK_RESERVED || ctx.current_token().str != op)
        error_at(ctx.current_token().str, user_input, "有効値ではありません");
    ctx.next_token();
}

// program = function*
std::vector<std::unique_ptr<Node>> program(const std::vector<std::unique_ptr<Token>> &_head, std::string_view user_input)
{
    ParseContext ctx{_head};
    std::vector<std::unique_ptr<Node>> nodes;

    while (ctx.is_valid())
    {
        nodes.emplace_back(function(ctx, user_input));
    }
    return nodes;
}

// function = ident "(" arg? | (arg"," arg)* ")" "{" stmt* "}"*
std::unique_ptr<Node> function(ParseContext &ctx, std::string_view user_input)
{
    std::unique_ptr<Node> node = std::make_unique<Node>();
    if (ctx.current_token().str == "int")
        ctx.next_token();
    else
        error_at(ctx.current_token().str, user_input, "型名ではありません");
    Token tok = expect_ident(ctx, user_input);
    node->funcname = tok.str;
    expect("(", ctx, user_input);
    node->args = create_arg(ctx, user_input);
    node->function.emplace_back(stmt(ctx, user_input));
    node->stack_size = ctx.cur_offset();
    return node;
}

// stmt = "return" expr? ";"
//      | "if" "(" expr ")" stmt ("else" stmt)?
//      | "while" "(" expr ")" stmt
//      | "for" "(" expr? ";" expr? ";" expr? ")" stmt
//      | "{" stmt* "}"
//      | expr ";"
std::unique_ptr<Node> stmt(ParseContext &ctx, std::string_view user_input)
{
    std::unique_ptr<Node> node;

    if (consume("return", ctx))
    {
        node = new_node(NodeKind::ND_RETURN);
        if (ctx.current_token().str != ";")
            node->lhs = expr(ctx, user_input);
    }
    else if (consume("if", ctx))
    {
        node = new_node(NodeKind::ND_IF);
        expect("(", ctx, user_input);
        node->cond = expr(ctx, user_input);
        expect(")", ctx, user_input);
        node->then = stmt(ctx, user_input);
        if (consume("else", ctx))
            node->els = stmt(ctx, user_input);
        return node;
    }
    else if (consume("while", ctx))
    {
        node = new_node(NodeKind::ND_WHILE);
        expect("(", ctx, user_input);
        node->cond = expr(ctx, user_input);
        expect(")", ctx, user_input);
        node->then = stmt(ctx, user_input);
        return node;
    }
    else if (consume("for", ctx))
    {
        node = new_node(NodeKind::ND_FOR);
        expect("(", ctx, user_input);
        if (!consume(";", ctx))
        {
            node->init = expr(ctx, user_input);
            expect(";", ctx, user_input);
        }
        if (!consume(";", ctx))
        {
            node->cond = expr(ctx, user_input);
            expect(";", ctx, user_input);
        }
        if (!consume(")", ctx))
        {
            node->inc = expr(ctx, user_input);
            expect(")", ctx, user_input);
        }
        node->then = stmt(ctx, user_input);
        return node;
    }
    else if (consume("{", ctx))
    {
        node = new_node(NodeKind::ND_BLOCK);
        while (!consume("}", ctx))
        {
            node->body.emplace_back(stmt(ctx, user_input));
        }
        return node;
    }
    else
    {
        node = expr(ctx, user_input);
    }
    expect(";", ctx, user_input);
    return node;
}

// expr = assign
std::unique_ptr<Node> expr(ParseContext &ctx, std::string_view user_input)
{
    return assign(ctx, user_input);
}

// assign = equality ("=" assign)?
std::unique_ptr<Node> assign(ParseContext &ctx, std::string_view user_input)
{
    auto node = equality(ctx, user_input);
    if (consume("=", ctx))
    {
        node = new_binary(NodeKind::ND_ASSIGN, std::move(node), equality(ctx, user_input));
    }
    return node;
}

// equality = relational ("==" relational | "!=" relational)*
std::unique_ptr<Node> equality(ParseContext &ctx, std::string_view user_input)
{
    auto node = relational(ctx, user_input);

    for (;;)
    {
        if (consume("==", ctx))
            node = new_binary(NodeKind::ND_EQ, std::move(node), relational(ctx, user_input));
        else if (consume("!=", ctx))
            node = new_binary(NodeKind::ND_NE, std::move(node), relational(ctx, user_input));
        else
            return node;
    }
}

// relational = add ("<" add | "<=" add | ">" add | ">=" add)*
std::unique_ptr<Node> relational(ParseContext &ctx, std::string_view user_input)
{
    auto node = add(ctx, user_input);

    for (;;)
    {
        if (consume("<", ctx))
            node = new_binary(NodeKind::ND_LT, std::move(node), add(ctx, user_input));
        else if (consume("<=", ctx))
            node = new_binary(NodeKind::ND_LE, std::move(node), add(ctx, user_input));
        else if (consume(">", ctx))
            node = new_binary(NodeKind::ND_LT, add(ctx, user_input), std::move(node));
        else if (consume(">=", ctx))
            node = new_binary(NodeKind::ND_LE, add(ctx, user_input), std::move(node));
        else
            return node;
    }
}

// add = mul ("+" mul | "-" mul)*
std::unique_ptr<Node> add(ParseContext &ctx, std::string_view user_input)
{
    auto node = mul(ctx, user_input);

    for (;;)
    {
        if (consume("+", ctx))
            node = new_binary(NodeKind::ND_ADD, std::move(node), mul(ctx, user_input));
        else if (consume("-", ctx))
            node = new_binary(NodeKind::ND_SUB, std::move(node), mul(ctx, user_input));
        else
            return node;
    }
}

// mul = unary ("*" unary | "/" unary)*
std::unique_ptr<Node> mul(ParseContext &ctx, std::string_view user_input)
{
    auto node = unary(ctx, user_input);

    for (;;)
    {
        if (consume("*", ctx))
            node = new_binary(NodeKind::ND_MUL, std::move(node), unary(ctx, user_input));
        else if (consume("/", ctx))
            node = new_binary(NodeKind::ND_DIV, std::move(node), unary(ctx, user_input));
        else
            return node;
    }
}

// unary = ("+" | "-" | "&" | "*")? unary
//       | primary
std::unique_ptr<Node> unary(ParseContext &ctx, std::string_view user_input)
{
    if (consume("+", ctx))
        return unary(ctx, user_input);
    if (consume("-", ctx))
        return new_binary(NodeKind::ND_SUB, new_num(0), unary(ctx, user_input));
    if (consume("&", ctx))
    {
        auto node = new_node(NodeKind::ND_ADDR);
        node->lhs = unary(ctx, user_input);
        return node;
    }
    if (consume("*", ctx))
    {
        auto node = new_node(NodeKind::ND_DEREF);
        node->lhs = unary(ctx, user_input);
        return node;
    }
    return primary(ctx, user_input);
}

// primary = "(" expr ")" | num | ident | ident "(" arg? | (arg"," arg)* ")" "{" stmt* "}"*
std::unique_ptr<Node> primary(ParseContext &ctx, std::string_view user_input)
{
    // 次のトークンが"("なら、"(" expr ")"のはず
    if (consume("(", ctx))
    {
        auto node = expr(ctx, user_input);
        expect(")", ctx, user_input);
        return node;
    }

    std::optional<Token> tok = consume_ident(ctx);
    if (tok)
    {
        if (consume("(", ctx))
        {
            auto node = new_node(NodeKind::ND_FUNCALL);
            node->funcname = tok->str;
            node->args = create_arg(ctx, user_input);
            return node;
        }
        auto node = new_node(NodeKind::ND_LVAR);
        node->kind = NodeKind::ND_LVAR;

        std::optional<LVar> lvar = ctx.find_lvar(tok.value());
        if (lvar)
        {
            node->offset = lvar->offset;
        }
        else
        {
            node->offset = ctx.new_var(tok.value());
        }
        return node;
    }

    return new_num(expect_number(ctx, user_input));
}

#include "9cc.hpp"

std::string create_label()
{
    static int i = 0;
    i++;
    std::string label = std::to_string(i);
    return label;
}

void gen_lval(const Node &node)
{
    if (node.kind != NodeKind::ND_LVAR)
        error("代入の左辺値が変数ではありません");

    std::cout << "  mov rax, rbp\n"
              << "  sub rax, " << node.offset << "\n"
              << "push rax\n"
              << std::endl;
}

void gen(const Node &node)
{
    switch (node.kind)
    {
    case NodeKind::ND_NUM:
        std::cout << "  push " << node.val << "\n"
                  << std::endl;
        return;
    case NodeKind::ND_LVAR:
        gen_lval(node);
        std::cout << "  pop rax\n"
                  << "  mov rax, [rax]\n"
                  << "  push rax\n"
                  << std::endl;
        return;
    case NodeKind::ND_ASSIGN:
        gen_lval(*node.lhs);
        gen(*node.rhs);

        std::cout << "  pop rdi\n"
                  << "  pop rax\n"
                  << "  mov [rax], rdi\n"
                  << "  push rdi\n"
                  << "  pop rax\n"
                  << std::endl;
        return;
    case NodeKind::ND_RETURN:
        if (node.lhs)
        {
            gen(*node.lhs);
        }

        std::cout << "  pop rax\n"
                  << "  mov rsp, rbp\n"
                  << "  pop rbp\n"
                  << "  ret\n";
        return;
    case NodeKind::ND_IF:
        if (node.els)
        {
            auto label = create_label();

            gen(*node.cond);
            std::cout << "  pop rax\n"
                      << "  cmp rax, 0\n"
                      << "  je .Lelse" << label << std::endl;
            gen(*node.then);
            std::cout << "  jmp .Lend" << label << "\n";
            std::cout << ".Lelse" << label << ":" << std::endl;
            gen(*node.els);
            std::cout << ".Lend" << label << ":" << std::endl;
        }
        else
        {
            auto label = create_label();

            gen(*node.cond);
            std::cout << "  pop rax\n"
                      << "  cmp rax, 0\n"
                      << "  je .Lend" << label << std::endl;
            gen(*node.then);
            std::cout << ".Lend" << label << ":" << std::endl;
        }
        return;
    case NodeKind::ND_WHILE:
    {
        auto label = create_label();

        std::cout << ".Lbegin" << label << ":" << std::endl;
        gen(*node.cond);
        std::cout << "  pop rax\n"
                  << "  cmp rax, 0\n"
                  << "  je .Lend" << label << std::endl;
        gen(*node.then);
        std::cout << "  jmp .Lbegin" << label << "\n";
        std::cout << ".Lend" << label << ":" << std::endl;
        return;
    }
    case NodeKind::ND_FOR:
    {
        auto label = create_label();

        if (node.init)
            gen(*node.init);
        std::cout << ".Lbegin" << label << ":" << std::endl;
        if (node.cond)
            gen(*node.cond);
        if (!node.init && !node.cond)
            std::cout << "  pop rax\n"
                      << " mov rax, " << 1 << "\n"
                      << "  push rax\n";
        std::cout << "  pop rax\n"
                  << "  cmp rax, 0\n"
                  << "  je .Lend" << label << std::endl;
        gen(*node.then);
        if (node.inc)
            gen(*node.inc);
        std::cout << "  jmp .Lbegin" << label << "\n";
        std::cout << ".Lend" << label << ":" << std::endl;
        return;
    }
    case NodeKind::ND_BLOCK:
        for (const auto &body : node.body)
            gen(*body);
        return;
    case NodeKind::ND_FUNCALL:
    {
        int argcount = 0;
        for (const auto &arg : node.args)
        {
            gen(*arg);
            argcount++;
        }

        std::string argreg[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
        for (int i = argcount - 1; i >= 0; i--)
            std::cout << "  pop " << argreg[i] << std::endl;

        std::cout << "  call " << node.funcname << "\n"
                  << "  push rax" << std::endl;
        return;
    }
    case NodeKind::ND_ADDR:
        gen_lval(*node.lhs);
        return;
    case NodeKind::ND_DEREF:
        gen(*node.lhs);
        std::cout << "  pop rax\n"
                  << "  mov rax, [rax]\n"
                  << "  push rax\n"
                  << std::endl;
        return;
    default:
        break;
    }

    gen(*node.lhs);
    gen(*node.rhs);

    std::cout << "  pop rdi\n";
    std::cout << "  pop rax\n"
              << std::endl;

    switch (node.kind)
    {
    case NodeKind::ND_ADD:
        std::cout << "  add rax, rdi\n"
                  << std::endl;
        break;
    case NodeKind::ND_SUB:
        std::cout << "  sub rax, rdi\n"
                  << std::endl;
        break;
    case NodeKind::ND_MUL:
        std::cout << "  imul rax, rdi\n"
                  << std::endl;
        break;
    case NodeKind::ND_DIV:
        std::cout << "  cqo\n";
        std::cout << "  idiv rdi\n"
                  << std::endl;
        break;
    case NodeKind::ND_EQ:
        std::cout << "  cmp rax, rdi\n"
                  << "  sete al\n"
                  << "  movzb rax, al\n"
                  << std::endl;
        break;
    case NodeKind::ND_NE:
        std::cout << "  cmp rax, rdi\n"
                  << "  setne al\n"
                  << "  movzb rax, al\n"
                  << std::endl;
        break;
    case NodeKind::ND_LT:
        std::cout << "  cmp rax, rdi\n"
                  << "  setl al\n"
                  << "  movzb rax, al\n"
                  << std::endl;
        break;
    case NodeKind::ND_LE:
        std::cout << "  cmp rax, rdi\n"
                  << "  setle al\n"
                  << "  movzb rax, al\n"
                  << std::endl;
        break;
    default:
        break;
    }

    std::cout << "  push rax\n"
              << std::endl;
}

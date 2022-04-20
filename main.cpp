#include "9cc.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        std::cout << argv[0] << ": 引数が間違っています。" << std::endl;

    // トークナイズとパースをする
    std::string_view user_input = argv[1];
    std::vector<std::unique_ptr<Token>> tokenized = tokenize(user_input);
    std::vector<std::unique_ptr<Node>> parsed = program(tokenized, user_input);

    // アセンブリの前半部分を出力
    std::cout << ".intel_syntax noprefix\n"
              << ".global main\n";
    // 先頭の式から順にコード生成
    for (std::size_t i = 0; i < parsed.size(); i++)
    {
        std::cout << parsed.at(i)->funcname << ":"
                  << "\n";

        // プロローグ
        std::cout << "  push rbp\n"
                  << "  mov rbp, rsp\n"
                  << "  sub rsp, " << parsed.at(i)->stack_size << "\n"
                  << std::endl;

        if (!parsed.at(i)->args.empty())
        {
            int argcount = 0;
            for (const auto &arg : parsed.at(i)->args)
            {
                gen(*arg);
                argcount++;
            }

            std::string argreg[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
            for (int h = argcount - 1; h >= 0; h--)
                std::cout << "  mov rax, rbp\n"
                          << "  sub rax, " << parsed.at(i)->args.at(h)->offset << "\n"
                          << "  mov [rax], " << argreg[h] << "\n"
                          << std::endl;
        }

        for (std::size_t j = 0; j < parsed[i]->function.size(); j++)
        {
            gen(*parsed[i]->function[j]);
        }
    }

    return 0;
}

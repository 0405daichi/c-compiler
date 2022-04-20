# バージョン
cmake_minimum_required(VERSION 3.1)

# プロジェクト設定
project(9cc_cmake CXX)

# 実行ファイル作成
add_executable(9cc main.cpp parse.cpp codegen.cpp tokenize.cpp 9cc.hpp)

# オプションを指定
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall --pedantic-errors -g")

# buildディレクトリ内でctestを実行するとテストが実行される
enable_testing()
add_subdirectory(unittest)

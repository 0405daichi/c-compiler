#!/bin/bash
assert() {
    expected="$1"
    input="$2"

    ./build/9cc "$input" > tmp.s
    cc -c -S -o foo.s foo.c
    cc -o tmp tmp.s foo.s
    ./tmp
    actual="$?"
    rm foo.s
    rm tmp*
    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

assert 0 'int main() {return 0;}'
assert 42 'int main() {return 42;}'
assert 21 'int main() {return 5+20-4;}'
assert 41 'int main() {return  12 + 34 - 5 ;}'
assert 47 'int main() {return 5+6*7;}'
assert 15 'int main() {return 5*(9-6);}'
assert 4 'int main() {return (3+5)/2;}'
assert 10 'int main() {return -10+20;}'
assert 10 'int main() {return - -10;}'
assert 10 'int main() {return - - +10;}'

assert 0 'int main() {return 0==1;}'
assert 1 'int main() {return 42==42;}'
assert 1 'int main() {return 0!=1;}'
assert 0 'int main() {return 42!=42;}'
assert 1 'int main() {return 42!=23;}'

assert 1 'int main() {return 0<1;}'
assert 0 'int main() {return 1<1;}'
assert 0 'int main() {return 2<1;}'
assert 1 'int main() {return 0<=1;}'
assert 1 'int main() {return 1<=1;}'
assert 0 'int main() {return 2<=1;}'

assert 1 'int main() {return 1>0;}'
assert 0 'int main() {return 1>1;}'
assert 0 'int main() {return 1>2;}'
assert 1 'int main() {return 1>=0;}'
assert 1 'int main() {return 1>=1;}'
assert 0 'int main() {return 1>=2;}'

assert 1 'int main() {return 1; 2; 3;}'
assert 2 'int main() {1; return 2; 3;}'
assert 3 'int main() {1; 2; return 3;}'

assert 3 'int main() {int a; a=3; return a;}'

assert 8 'int main() {int a=3; int z=5; return a+z;}'
assert 14 'int main() {int a = 3; int b = 5 * 6 - 8; return a + b / 2;}'

assert 3 'int main() {int foo=3; return foo;}'
assert 6 'int main() {int foo=1; int bar=2+3; return foo+bar;}'

assert 3 'int main() {if (0) return 2; return 3;}'
assert 3 'int main() {if (1-1) return 2; return 3;}'
assert 2 'int main() {if (1) return 2; return 3;}'
assert 2 'int main() {if (2-1) return 2; return 3;}'
assert 3 'int main() {if (0) return 2; else return 3;}'
assert 3 'int main() {if (1-1) return 2; return 3;}'
assert 2 'int main() {if (1) return 2; return 3;}'
assert 2 'int main() {if (2-1) return 2; return 3;}'

assert 1 'int main() {return 1;}'
assert 3 'int main() {{1; {2;} return 3;}}'

assert 10 'int main() {int i=0; while(i<10) i=i+1; return i;}'
assert 0 'int main() {int i=1000000; while(i>0) i=i-1; return 0;}'
assert 55 'int main() {int i=0; int j=0; while(i<=10) {j=i+j; i=i+1;} return j;}'

assert 55 'int main() {int i=0; int j=0; for (i=0; i<=10; i=i+1) j=i+j; return j;}'
assert 3 'int main() {for (;;) return 3; return 5;}'

assert 3 'int main() {return ret3();}'
assert 8 'int main() {return add(3, 5);}'
assert 8 'int main() {int foo = 3; int bar = 5; return add(foo, bar);}'

assert 3 'int main() { return ret3(); } int ret3() { return 3; }'
assert 8 'int main() {int foo = 3; int bar = 5; return add(foo, bar);} int add(int foo, int bar) { return foo + bar; }'
assert 8 'int add(int foo, int bar) { return foo + bar; } int main() {int foo = 3; int bar = 5; return add(foo, bar);}'

assert 8 'int main() {int x=8; int y=&x; return *y;}'
assert 3 'int main() {int x=3; int y=5; int z=&y+8; return *z;}'

assert 3 'int main() {int i=0; if(1){i=3; return;} return i;}'
assert 42 'int foo() { return; } int main() { foo(); return 42; }'

echo OK

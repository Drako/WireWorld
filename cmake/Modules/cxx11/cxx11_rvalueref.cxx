#include <utility>

struct foo
{
    int * value;

    foo(int val) : value(new int(val)) {}
    foo(foo const & cp) : value(new int(*(cp.value))) {}
    foo(foo && mv) : value(std::move(mv.value)) {}
    ~foo() { delete value; }
};

int main()
{
    foo f1(42);
    foo f2(std::move(f1));
    return f1.value != 0;
}

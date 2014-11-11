struct foo
{
    foo() = default;
    ~foo() = default;
    foo(foo const &) = delete;
    foo & operator = (foo const &) = delete;
};

int main()
{
    return 0;
}

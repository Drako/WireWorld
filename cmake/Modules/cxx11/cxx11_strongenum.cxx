enum class foo : int
{
    FOO = 0
};

int main()
{
    return static_cast<int>(foo::FOO);
}

constexpr int square(int n)
{
    return (n * n);
}

int main()
{
    int values[square(1)] = { 0 };
    return values[0];
}

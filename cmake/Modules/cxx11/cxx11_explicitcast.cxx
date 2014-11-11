struct foo
{
    explicit operator bool () const
    {
        return true;
    }
};

int main()
{
    return 0;
}

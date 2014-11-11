template <int... Types>
int size()
{
    return sizeof...(Types);
}

int main()
{
    return size<1, 2, 3, 4>() - 4;
}

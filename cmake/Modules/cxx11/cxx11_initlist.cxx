#include <initializer_list>

int sum(std::initializer_list<int> numbers)
{
    int sum = 0;
    for (std::initializer_list<int>::iterator it = numbers.begin(); it != numbers.end(); ++it)
        sum += *it;
    return sum;
}

int main()
{
    return sum({ -42, 42 });
}

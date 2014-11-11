template <int A, int B>
struct sum { static int const value = A + B; };

template <int B>
using inc = sum<1, B>;

int main()
{
    return inc<-1>::value;
}

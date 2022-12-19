#include "exp.h"

int fast_exp(int x, int k)
{
    int res = 1;
    int pow = x;
    while (k != 0)
    {
        if (k & 1 == 1)
        {
            res = res * pow;

        }
        pow = pow * pow;
        k = k >> 1;
    }
    return res;
}
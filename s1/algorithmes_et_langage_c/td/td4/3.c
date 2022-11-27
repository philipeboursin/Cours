#include<stdio.h>


typedef struct cplx_struct
{
    float a;
    float b;
} cplx;

void c_print(cplx z1)
{
    printf("%f + i%f", z1.a, z1.b);
}

cplx c_add(cplx z1, cplx z2)
{
    return (cplx){z1.a + z2.a, z1.b + z2.b};
}

cplx c_mul(cplx z1, cplx z2)
{
    return (cplx){z1.a*z2.a - z1.b*z1.b, z1.a*z2.b + z1.b*z2.a};
}

void auxi(unsigned int* fn, unsigned int* res, unsigned int n)
{
    unsigned int m = n >> 1;
    for (int i = 0; i < m; i++)
    {
        res[i] = fn[i << 1];
        res[m + i] = fn[(i << 1) + 1];
    }
    fft(res, res, m);
}


int main()
{
    cplx z1 = (cplx){2,1};
    cplx z2 = (cplx){2,-1};
    c_print(c_add(z1, z1));
    printf("\n");
    c_print(c_mul(z1, z2));
    printf("\n");
}
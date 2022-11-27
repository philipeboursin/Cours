#include<stdio.h>


// Fonctions auxiliaires
// Aditionne deux vecteurs de taille n
void add_vect(unsigned int* v, unsigned int* w, unsigned int* res, unsigned int n);
// Calcule le poids de hamming d'un entier 
unsigned int hamming_weight(unsigned int v);
// Affiche un vecteur de taille n
void print_vect(unsigned int* v, unsigned int n);
// Question 1
// Transformation de Mobius
void truth_to_alg(unsigned int* fn, unsigned int n);
// Tests de la question 1
void q1()
// Question 2
// Calcul du degre d'une fonction booleenne sous forme algebrique
unsigned int deg_alg(unsigned int* fn, unsigned int n);
// Calcul du degre d'une fonction booleenne sous forme table de verite
unsigned int deg_truth(unsigned int* fn, unsigned int n);
// Tests de la question 2
void q2();


//------ Fonctions auxiliaires
void add_vect(unsigned int* v, unsigned int* w, unsigned int* res, unsigned int n)
{
    for (int i = 0; i < n; i++)
    {
        res[i] = v[i] ^ w[i];    
    }
}

unsigned int hamming_weight(unsigned int v)
{
    unsigned int m11 = 0b01010101010101010101010101010101;
    unsigned int m12 = 0b10101010101010101010101010101010;
    unsigned int m21 = 0b00110011001100110011001100110011;
    unsigned int m22 = 0b11001100110011001100110011001100;
    unsigned int m31 = 0b00001111000011110000111100001111;
    unsigned int m32 = 0b11110000111100001111000011110000;
    unsigned int m41 = 0b00000000111111110000000011111111;
    unsigned int m42 = 0b11111111000000001111111100000000;
    unsigned int m51 = 0b00000000000000001111111111111111;
    unsigned int m52 = 0b11111111111111110000000000000000;
    v = ((v & m11) + ((v & m12) >> 1));
    v = ((v & m21) + ((v & m22) >> 2));
    v = ((v & m31) + ((v & m32) >> 4));
    v = ((v & m41) + ((v & m42) >> 8));
    v = ((v & m51) + ((v & m52) >> 16));
    return v;
}

void print_vect(unsigned int* v, unsigned int n)
{
    printf("[");
    for (int i = 0; i < n - 1; i++) printf("%d, ", v[i]);
    printf("%d]", v[n-1]);
}


//------ Question 1
void truth_to_alg(unsigned int* fn, unsigned int n)
{
    if (n != 1)
    {
        unsigned int m = n >> 1;
        add_vect(fn, fn + m, fn + m, m);
        truth_to_alg(fn, m);
        truth_to_alg(fn + m, m);
    }
}

void q1()
{
    unsigned int n = 0;
    unsigned int i;
    unsigned int j = 0;
    FILE* fp;
    FILE* fpbis;
    fp = fopen("./fonction.txt", "r");
    fpbis = fp;
    
    fscanf(fp, "%u", &n);
    unsigned int fn[n];
    while (fscanf(fp, "%d", &i) !=EOF)
    {
        fn[j] = i;
        j++;
    }

    truth_to_alg(fn, n);
    
    print_vect(fn, n);
    printf("\n");

    fclose(fp);
}


//------ Question 2
unsigned int deg_alg(unsigned int* fn, unsigned int n)
{
    unsigned int max = 0;
    unsigned int w;
    for (int i = 0; i < n; i++)
    {
        w = hamming_weight(i);
        if ((fn[i] == 1) & (w > max))
        {
            max = w;
        }
    }
    return max;
}

unsigned int deg_truth(unsigned int* fn, unsigned int n)
{
    truth_to_alg(fn, n);
    deg_alg(fn, n);
}

void q2()
{
    unsigned int n = 0;
    unsigned int i;
    unsigned int j = 0;
    FILE* fp;
    FILE* fpbis;
    fp = fopen("./fonction.txt", "r");
    fpbis = fp;
    
    fscanf(fp, "%u", &n);
    unsigned int fn[n];
    while (fscanf(fp, "%d", &i) !=EOF)
    {
        fn[j] = i;
        j++;
    }

    truth_to_alg(fn, n);
    printf("deg(f) = %u\n", deg_truth(fn, n));
    fclose(fp);   
}


//------ Main
int main()
{
    // q1();
    q2();
}
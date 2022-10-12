#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define CI(v, i) (v ^= (1 << i))
#define CIJ(M, i, j) CI(M[i], j)
#define GI(v, i) (v >> i) & 1
#define GIJ(M, i, j) GI(M[i], j)

// Taille des matrices/vecteurs
int n = 16;
int m = 16;
int C = 65536;
int test_it = 10000000;
// int m = 8*(int)sizeof(unsigned int);

//// PARTIE 1
// Affichage d'un vecteur classique (en ligne)
void print_vect(int v[n])
{
    printf("[");
    for (int i = 0; i < n - 1; i++) printf("%d, ", v[i]);
    printf("%d]", v[n-1]);
}

// Affichage d'une matrice classique
void print_mat(int M[n][n])
{
    for (int i = 0; i < n - 1; i++)
    {
        printf("[");
        for (int j = 0; j < n - 1; j++) printf("%d, ", M[i][j]);
        printf("%d]\n", M[i][n-1]);
    }
    printf("[");
    for (int j = 0; j < n - 1; j++) printf("%d, ", M[n-1][j]);
    printf("%d]", M[n-1][n-1]);
}

// Remplis une matrice classique de 1 et 0 aléatoirement
void rand_mat(int M[n][n])
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) M[i][j] = rand() & 1;
    }
}

// Remplis un vecteur classique de 1 et 0 aléatoirement
void rand_vect(int v[n])
{
    srand(time(NULL));
    for (int i = 0; i < n; i++) v[i] = rand() & 1;
}

// Produit matrice classique-vecteur classique
void Mv(int M[n][n], int v[], int res[])
{
    for (int i = 0; i < n; i++)
    {
        int inter = 0;
        for (int j = 0; j < n; j++) inter ^= M[i][j] & v[j];
        res[i] = inter;
    }
}

// Produit matrice^n vecteur
void Mkv(int M[n][n], int v[], int res[], int k)
{
    int inter[n];
    for (int i = 0; i < n; i++) res[i] = v[i];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++) inter[j] = res[j];
        Mv(M, inter, res);
    }
}


//// PARTIE 2
// Affiche une matrice de unsigned int
void print_mat_bis(unsigned int M[])
{
    for (int i = 0; i < m - 1; i++)
    {
        printf("[");
        for (int j = 0; j < m - 1; j++) printf("%d, ", GIJ(M, i, j));
        printf("%d]\n", GIJ(M, i, m-1));
    }
    printf("[");
    for (int j = 0; j < m - 1; j++) printf("%d, ", GIJ(M, m - 1, j));
    printf("%d]", GIJ(M, m - 1, m - 1));
    
}

// Affiche en binaire un unsigned int
void print_vect_bis(unsigned int v)
{
    printf("[");
    for (int i = 0; i < m - 1; i++) printf("%d, ", GI(v,i));
    printf("%d]", GI(v, m - 1));
}

// Remplis une matrice de ui de manière aléatoire
void rand_mat_bis(unsigned int M[m])
{
    srand(time(NULL));
    for (int i = 0; i < m; i++)
    {
        M[i] = 0;
        for (int j = 0; j < m; j++)
        {
            if (rand() & 1) CIJ(M, i, j);
        }
    }
}

// Fabrique un unsigned int aléatoire
unsigned int rand_vect_bis()
{
    unsigned int v = 0;
    srand(time(NULL));
    for (int i = 0; i < m; i++)
    {
        if (rand() & 1 == 1) CI(v, i);
    }
    return v;
}


//// PARTIE 4
// Calcule la parité d'un unsigned int
unsigned int parity(unsigned int v)
{
    int res = 0;
    for (int i = 0; i < m; i++) res ^= GI(v, i);
    return res;
}

// Calcule un tableau qui contient la parité de tous les vecteurs de 16 bits
void parity_tab(unsigned int T[C])
{
    for (int i = 0; i < C; i++) T[i] = parity(i);
}

// Calcule la parité d'un vecteur binaire de moins de 32 bits
unsigned int parity_bis(unsigned int T[C], unsigned int v)
{
    unsigned int a = T[(v << 16) >> 16];
    return a ^ T[v >> 16];
} 

//// PARTIE 5
// Produit matrice vecteur en utiliant parity
unsigned int Mv_par(unsigned int M[m], unsigned int v)
{
    unsigned int res = 0;
    for (int i = 0; i < m; i++)
    {
        if (parity(M[i] & v) == 1) CI(res, i);
    }
    return res;
}

// Produit matrice vecteur en utilisant le tableau des parités précalculées
unsigned int Mv_16(unsigned int T[C], unsigned int M[m], unsigned int v)
{
    unsigned int res = 0;
    if (m != 16) printf("Taille de matrice non compatible");
    else
    {
        for (int i = 0; i < m; i++)
        {
            if (T[M[i] & v] == 1) CI(res, i);
        }
    }
    return res;
}

// Produit matrice vecteur en utilisant parity_bis
unsigned int Mv_par_bis(unsigned int T[C], unsigned int M[m], unsigned int v)
{
    unsigned int res = 0;
    for (int i = 0; i < m; i++)
    {
        if (parity_bis(T, M[i] & v) == 1) CI(res, i);
    }
    return res;
}


//// PARTIE 5
void test1()
{
    unsigned int M[m];
    unsigned int T[C];
    unsigned int v = rand_vect_bis();
    unsigned int res;

    rand_mat_bis(M);
    parity_tab(T);
    for (int i = 0; i < test_it; i++)
    {
        // printf("%d % \r", i*100/test_it);
        res = Mv_par_bis(T, M, v);
    }
}

void test2()
{
    unsigned int M[m];
    unsigned int v = rand_vect_bis();
    unsigned int res;

    rand_mat_bis(M);
    for (int i = 0; i < test_it; i++)
    {
        // printf("%d % \r", i*100/test_it);
        res = Mv_par(M, v);
    }
}

void test3()
{
    int M[n][n];
    int v[n];
    int res[n];

    rand_mat(M);
    rand_vect(v);
    for (int i = 0; i < test_it; i++)
    {
        // printf("%d % \r", i*100/test_it);
        Mv(M, v, res);
    }
}

void test4()
{
    unsigned int M[m];
    unsigned int T[C];
    unsigned int v = rand_vect_bis();
    unsigned int res;

    rand_mat_bis(M);
    parity_tab(T);
    for (int i = 0; i < test_it; i++)
    {
        // printf("%d % \r", i*100/test_it);
        res = Mv_16(T, M, v);
    }
}

//////
int main()
{
    // // PARTIE 1
    // printf("--PARTIE 1-- \n");
    // int v[n];
    // int M[n][n];
    // rand_vect(v);
    // rand_mat(M);
    // printf("M = \n");
    // print_mat(M);
    // printf("\n");
    // printf("v = \n");
    // print_vect(v);
    // printf("\n");
    // int res[n];
    // Mv(M, v, res);
    // printf("M*v = \n");
    // print_vect(res);
    // printf("\n");
    // Mkv(M, v, res, 10);
    // printf("(M^k)*v = \n");
    // print_vect(res);
    // printf("\n");


    // // PARTIE 2
    // printf("\n--PARTIE 2-- \n");
    // unsigned int Mb[m];
    // unsigned int vb = rand_vect_bis();
    // rand_mat_bis(Mb);
    // printf("Matrice aléatoire M = \n");
    // print_mat_bis(Mb);
    // printf("\n");
    // printf("Vecteur aléatoire v = \n");
    // print_vect_bis(vb);
    // printf("\n");

    // //PARTIE 3
    // printf("\n--PARTIE 3-- \n");
    // unsigned int T[C];
    // parity_tab(T);
    // int i = C - 10;
    // printf("Parité des entiers entre %d et %d :\n", i, i+9);
    // for (int j = i; j < i + 10; j++)
    //     {
    //         print_vect_bis(j);
    //         printf(" %d", T[j]);
    //         printf("%d \n", parity_bis(T, j));
    //     }
    // print_vect_bis(C);
    // printf(" %d \n", parity_bis(T, C));

    // // PARTIE 4
    // printf("\n--PARTIE 4-- \n");
    // unsigned int Nb[m];
    // Nb[0] = 1;
    // Nb[1] = 0;
    // Nb[2] = 1;
    // unsigned int wb = 3;
    // printf("Nb =\n");
    // print_mat_bis(Nb);
    // printf("\n wb =\n");
    // print_vect_bis(wb);
    // printf("\n Mb*wb =\n");
    // print_vect_bis(Mv_par(Nb, wb));
    // printf("\n");
    // print_vect_bis(Mv_par_bis(T, Nb, wb));
    // printf("\n");

    test3();
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CI(v, i) (v ^= (1 << i))
#define CIJ(M, i, j) CI(M[i], j)

#define GI(v, i) (v >> i) & 1
#define GIJ(M, i, j) GI(M[i], j)

#define TP16 65536

//// VARIABLES GLOBALES
// Taille des matrices/vecteurs
int n = 16;
int m = 16;


//// PARTIE 1
// Affichage d'un vecteur classique (en ligne)
void print_vect(int v[n]);
// Affichage d'une matrice classique
void print_mat(int M[n][n]);
// Remplis une matrice classique de 1 et 0 aléatoirement
void rand_mat(int M[n][n]);
// Remplis un vecteur classique de 1 et 0 aléatoirement
void rand_vect(int v[n]);
// Produit matrice classique-vecteur classique
void Mv(int M[n][n], int v[], int res[]);
// Produit matrice^n vecteur
void Mkv(int M[n][n], int v[], int res[], int k);
// Tests de la partie 1
void partie_1();

//// PARTIE 2 ET 4
// Fabrique un unsigned int aléatoire
unsigned int rand_vect_bis();
// Remplis une matrice de ui de manière aléatoire
void rand_mat_bis(unsigned int M[m]);
// Affiche en binaire un unsigned int
void print_vect_bis(unsigned int v);
// Affiche une matrice de unsigned int
void print_mat_bis(unsigned int M[m]);
// Tests des parties 2 et 4
void partie_2_et_4();

//// PARTIE 3
// Calcule la parité d'un unsigned int
unsigned int parity(unsigned int v);
// Calcule un tableau qui contient la parité de tous les vecteurs de 16 bits
void parity_tab(unsigned int T[TP16]);
// Calcule la parité d'un vecteur binaire de moins de 32 bits
unsigned int parity_bis(unsigned int T[TP16], unsigned int v);
// Tests de la partie 3
void partie_3();

//// PARTIE 5
// Produit matrice vecteur en utiliant parity
unsigned int Mv_naive(unsigned int M[m], unsigned int v);
// Produit matrice vecteur en utilisant le tableau des parités précalculées
unsigned int Mv_16(unsigned int T[TP16], unsigned int M[m], unsigned int v);
// Produit matrice vecteur en utilisant parity_bis
unsigned int Mv_opt(unsigned int T[TP16], unsigned int M[m], unsigned int v);
// Tests de la partie 5
void partie_5();

//// PARTIE 6
// Test du calcul matriciel standard
void test1(int test_it);
// Test du calcul matriciel avec parité naive
void test2(int test_it);
// Test du calcul matriciel avec parité précalculée
void test1(int test_it);
// Test du calcul matriciel avec parité optimisée
void test1(int test_it);
// Tests de la partie 6
void partie_6();



//// PARTIE 1
void print_vect(int v[n])
{
    printf("[");
    for (int i = 0; i < n - 1; i++) printf("%d, ", v[i]);
    printf("%d]", v[n-1]);
}

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

void rand_mat(int M[n][n])
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) M[i][j] = rand() & 1;
    }
}

void rand_vect(int v[n])
{
    srand(time(NULL));
    for (int i = 0; i < n; i++) v[i] = rand() & 1;
}

void Mv(int M[n][n], int v[], int res[])
{
    for (int i = 0; i < n; i++)
    {
        int inter = 0;
        for (int j = 0; j < n; j++) inter ^= M[i][j] & v[j];
        res[i] = inter;
    }
}

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

void partie_1()
{
    n = 3;
    int M[3][3] = {{1, 0, 0}, {0, 0, 0}, {0, 0, 1}};
    int v[3] = {1,1,1};
    int res[3];
    int k = 10;

    printf("M=\n");
    print_mat(M);
    printf("\n");
    
    printf("v=\n");
    print_vect(v);
    printf("\n");
    
    Mv(M, v, res);
    printf("M*v=\n");
    print_vect(res);
    printf("\n");

    Mkv(M, v, res, k);
    printf("(M^k)*v=\n");
    print_vect(res);
    printf("\n");

    n = 10;
    int N[n][n];
    int w[n];
    int res2[n];

    rand_mat(N);
    rand_vect(w);
    
    printf("Matrice aléatoire de taille 10 :\n");
    print_mat(N);
    printf("\n");
    
    printf("Vecteur aléatoire de taille 10 :\n");
    print_vect(w);
    printf("\n");
    
    printf("Leur produit =\n");
    Mv(N, w, res2);
    print_vect(res2);
    printf("\n");
}


//// PARTIE 2 et 4
unsigned int rand_vect_bis()
{
    unsigned int v = 0;
    srand(time(NULL));
    v = (rand() << 1);
    v ^= rand() & 1;
    v = (v << (32 - m)) >> (32 - m);
    return v;
}

void rand_mat_bis(unsigned int M[m])
{
    unsigned int v = 0;
    srand(time(NULL));
    for (int i = 0; i < m; i++)
    {
        v = (rand() << 1);
        v ^= rand() & 1;
        v = (v << (32 - m)) >> (32 - m);
        M[i] = v;
    }
}

void print_vect_bis(unsigned int v)
{
    printf("[");
    for (int i = 0; i < m - 1; i++) printf("%d, ", GI(v,i));
    printf("%d]", GI(v, m - 1));
}

void print_mat_bis(unsigned int M[m])
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

void partie_2_et_4()
{
    m = 10;
    unsigned int M[m];
    unsigned int v = rand_vect_bis();
    rand_mat_bis(M);

    printf("Vecteur format ui aléatoire :\n");
    print_vect_bis(v);
    printf("\n");
    printf("Matrice format ui aléatoire :\n");
    print_mat_bis(M);
    printf("\n");
}


//// PARTIE 3
unsigned int parity(unsigned int v)
{
    v = (v >> 16) ^ v;
    v = (v >> 8) ^ v;
    v = (v >> 4) ^ v;
    v = (v >> 2) ^ v;
    v = (v >> 1) ^ v;
    return v & 1;
    // return __builtin_popcount(v) & 1; // Compiler avec -march=native pour faire marcher celui la
}

void parity_tab(unsigned int T[TP16])
{
    for (int i = 0; i < TP16; i++) T[i] = parity(i);
}

unsigned int parity_bis(unsigned int T[TP16], unsigned int v)
{
    unsigned int a = T[(v << 16) >> 16];
    return a ^ T[v >> 16];
} 

void partie_3()
{
    unsigned int T[TP16];
    parity_tab(T);
    unsigned int v = 0;

    printf("Fonction de parité générique :\n");
    m = 4;
    v = rand_vect_bis();
    printf("v = ");
    print_vect_bis(v);
    printf(" sa parité = %u\n", parity(v));

    printf("Tableau de parités :\n");
    m = 16;
    v = rand_vect_bis();
    printf("v = ");
    print_vect_bis(v);
    printf(" sa parité = %u\n", T[v]);
    
    printf("Fonction de parité optimisée :\n");
    m = 20;
    v = rand_vect_bis();
    printf("v = ");
    print_vect_bis(v);
    printf(" sa parité = %u\n", parity_bis(T, v));
}


//// PARTIE 5
unsigned int Mv_naive(unsigned int M[m], unsigned int v)
{
    unsigned int res = 0;
    for (int i = 0; i < m; i++)
    {
        if (parity(M[i] & v) == 1) CI(res, i);
    }
    return res;
}

unsigned int Mv_16(unsigned int T[TP16], unsigned int M[m], unsigned int v)
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

unsigned int Mv_opt(unsigned int T[TP16], unsigned int M[m], unsigned int v)
{
    unsigned int res = 0;
    for (int i = 0; i < m; i++)
    {
        if (parity_bis(T, M[i] & v) == 1) CI(res, i);
    }
    return res;
}

void partie_5()
{
    m = 3;
    unsigned int res;
    unsigned int v = 3; // [1,1,0]
    unsigned int M[3] = {1, 0, 4}; // [[1,0,0],[0,0,0],[0,0,1]]
    unsigned int T[TP16];
    parity_tab(T);
    
    printf("Produit matrice vecteur naif\n");
    printf("M =\n");
    print_mat_bis(M);
    printf("\nv =\n");
    print_vect_bis(v);
    printf("\nM*v =\n");
    res = Mv_naive(M, v);
    print_vect_bis(res);
    printf("\n");

    printf("Produit matrice vecteur de taille 16 en utilisant un tableau précalculé des parités des vecteurs de taille 16\n");
    m = 16;
    unsigned int N[m];
    v = TP16 - 1;
    for (int i = 0; i < m; i++)
    {
        N[i] = 1 << i;
    }
    printf("M =\n");
    print_mat_bis(N);
    printf("\nv =\n");
    print_vect_bis(v);
    printf("\nM*v =\n");
    res = Mv_16(T, N, v);
    print_vect_bis(res);
    printf("\n");

    printf("Produit matrice vecteur optimisé\n");
    m = 20;
    unsigned int P[m];
    v = ((-1) << (32 - m)) >> (32 - m);
    for (int i = 0; i < m; i++)
    {
        P[i] = 1 << i;
    }
    printf("M =\n");
    print_mat_bis(P);
    printf("\nv =\n");
    print_vect_bis(v);
    printf("\nM*v =\n");
    res = Mv_opt(T, P, v);
    print_vect_bis(res);
    printf("\n");
}


//// PARTIE 5
void test1(int test_it)
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

void test2(int test_it)
{
    unsigned int M[m];
    unsigned int v = rand_vect_bis();
    unsigned int res;

    rand_mat_bis(M);
    for (int i = 0; i < test_it; i++)
    {
        // printf("%d % \r", i*100/test_it);
        res = Mv_naive(M, v);
    }
    printf("%d\n", res);
}

void test3(int test_it)
{
    unsigned int M[m];
    unsigned int T[TP16];
    unsigned int v = rand_vect_bis();
    unsigned int res;

    rand_mat_bis(M);
    parity_tab(T);
    for (int i = 0; i < test_it; i++)
    {
        // printf("%d % \r", i*100/test_it);
        res = Mv_16(T, M, v);
    }
    printf("%d\n", res);

}

void test4(int test_it)
{
    unsigned int M[m];
    unsigned int T[TP16];
    unsigned int v = rand_vect_bis();
    unsigned int res;

    rand_mat_bis(M);
    parity_tab(T);
    for (int i = 0; i < test_it; i++)
    {
        // printf("%d % \r", i*100/test_it);
        res = Mv_opt(T, M, v);
    }
    printf("%d\n", res);

}

void partie_6()
{
    int test_it = 200000000;
    m = 16;
    test2(test_it);
}


//////
int main()
{
    // partie_1();
    // partie_2_et_4();
    // partie_3();
    // partie_5();
    partie_6();
}
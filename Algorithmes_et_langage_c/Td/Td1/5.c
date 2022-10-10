#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define CI(v, i) (v ^= (1 << (i - 1)))
#define CIJ(M, i, j) CI(M[i], j)
#define GI(v, i) (v >> (i - 1)) & 1
#define GIJ(M, i, j) GI(M[i], j)

// Taille des matrices/vecteurs
int n = 3;
int m = 3;
// int m = 8*(int)sizeof(unsigned int);

//// PARTIE 1
// Affichage d'un vecteur classique (en ligne)
void print_vect(int v[n])
{
    printf("[");
    for (int i = 0; i < n - 1; i++) printf("%d, ", v[i]);
    printf("%d]\n", v[n-1]);
}

// Affichage d'une matrice classique
void print_mat(int M[n][n])
{
    for (int i = 0; i < n; i++)
    {
        printf("[");
        for (int j = 0; j < n - 1; j++) printf("%d, ", M[i][j]);
        printf("%d]\n", M[i][n-1]);
    }
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
    for (int i = 0; i < m; i++)
    {
        printf("[");
        for (int j = 0; j < m - 1; j++) printf("%d, ", GIJ(M, i, j));
        printf("%d]\n", GIJ(M, i, m));
    }
}

// Affiche en binaire un unsigned int
void print_vect_bis(unsigned int v)
{
    printf("[");
    for (int i = 0; i < m - 1; i++) printf("%d, ", GI(v,i));
    printf("%d]\n", GI(v, m));
}

// Remplis une matrice de ui de manière aléatoire
void rand_mat_bis(unsigned int M[m])
{
    srand(time(NULL));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (rand() & 1) CIJ(M, i, j);
        }
    }
}

// Fabrique un unsigned int aléatoire
unsigned int rand_vect_bis()
{
    unsigned int v;
    srand(time(NULL));
    for (int i = 0; i < m; i++)
    {
        if (rand() & 1) CI(v, i);
    }
    return v;
}



int main()
{
    // PARTIE 1
    printf("--PARTIE 1-- \n");
    int v[n];
    int M[n][n];
    rand_vect(v);
    rand_mat(M);
    printf("M = \n");
    print_mat(M);
    printf("v = \n");
    print_vect(v);
    int res[n];
    Mv(M, v, res);
    printf("M*v = \n");
    print_vect(res);
    Mkv(M, v, res, 10);
    printf("(M^k)*v = \n");
    print_vect(res);


    // PARTIE 2
    printf("\n--PARTIE 2-- \n");
    unsigned int Mb[m];
    unsigned int vb = rand_vect_bis();
    rand_mat_bis(Mb);
    printf("Matrice aléatoire M = \n");
    print_mat_bis(Mb);
    printf("Vecteur aléatoire v = \n");
    print_vect_bis(vb);

    //PARTIE 3
    printf("\n--PARTIE 3-- \n");
}
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ith(x,i) (x>>(i-1))&1
#define tki(t,i,j) ith(t[i],j)

// Taille des matrices/vecteurs
int n = 5;
int m = 8*(int)sizeof(unsigned int);

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
        for (int j = 0; j < n; j++) inter += M[i][j] & v[j];
        res[i] = inter;
    }
}


//// PARTIE 2
// Affiche une matrice de unsigned int
void print_mat_bis(unsigned int t[m])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++) printf("%d", tki(t,i,j));
        printf("\n");
    }
}

// Affiche en binaire un unsigned int
void print_vect_bis(unsigned int v)
{
    for (int i = 0; i < m; i++) printf("%d", ith(v,i));
    printf("\n");
}

// Remplis une matrice de ui de manière aléatoire
void rand_mat_bis(unsigned int t[m])
{
    srand(time(NULL));
    for (int i = 0; i < m; i++)
    {
        t[i] = (rand() << 1) ^ (rand() & 1);
    }
}

// Fabrique un unsigned int aléatoire
unsigned int rand_vect_bis()
{
    srand(time(NULL));
    return (unsigned int)(rand() << 1) ^ (rand() & 1);
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

    // PARTIE 2
    printf("\n--PARTIE 2-- \n");
    unsigned int t[m];
    rand_mat_bis(t);
    printf("matrice d'unsigned int aléatoire t = \n");
    print_mat_bis(t);
    printf("unsigned int aléatoire v = \n");
    print_vect_bis(rand_vect_bis());

    //PARTIE 3
    printf("\n--PARTIE 3-- \n");
}
// Contexte q-adique : comprend un contexte p-adique et un polynôme représentant l'extension q-adique 
typedef struct _qadic_ctx_t qadic_ctx_t;

// Teichmuller modulus
void _teichmuller_modulus(padic_poly_t M, padic_poly_t m, int N, padic_ctx_t C);

// void qadic_ctx_init(qadic_ctc_t )

// Procédure qui attribue à R (resp Q) la valeur du reste (resp quotient) de la div de A par B (supposé unitaire)
void DivEucl(padic_poly_t A, padic_poly_t B, padic_poly_t R, padic_poly_t Q, padic_ctx_t C );


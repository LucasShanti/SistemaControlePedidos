typedef struct {
    int id;
    char nome  [100];
    char endereco [100];
    char telefone [20];
    int tipo; // 0 - Pessoa Fisica, 1 - Pessoa Juridica
    PessoaFisica pf;
    PessoaJuridica pj;
} Cliente;

typedef struct {
    char cpf[15];
    char nome[50];
    char dataNascimento[11];
} PessoaFisica;

typedef struct {
    char cnpj[20];
    char razaoSocial[50];
    char nome [20];
} PessoaJuridica;

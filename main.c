#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACOES  50
#define TAM_STR   100

typedef enum {
    PLANEJADA  = 0,
    REALIZADA  = 1,
    CANCELADA  = 2
} Situacao;

typedef struct {
    int      codigo;
    char     escola[TAM_STR];
    char     tema[TAM_STR];
    char     descricao[TAM_STR];
    char     data_prevista[12];
    char     publico_alvo[TAM_STR];
    char     responsavel[TAM_STR];
    int      qtd_prevista;
    int      qtd_efetiva;
    Situacao situacao;
} Acao;

typedef struct {
    const char *tema;
    const char *descricao;
} TemaPredef;

static const TemaPredef TEMAS[] = {
    { "Vacinacao",           "Verificacao da situacao vacinal e orientacao sobre o calendario de imunizacao dos alunos." },
    { "Alimentacao Saudavel","Promocao de habitos alimentares saudaveis por meio de oficinas, palestras e material educativo." },
    { "Atividade Fisica",    "Estimulo a pratica regular de exercicios e vida ativa no ambiente escolar." },
};
#define NUM_TEMAS (int)(sizeof(TEMAS) / sizeof(TEMAS[0]))

Acao acoes[MAX_ACOES];
int  total = 0;

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(const char *prompt, char *destino, int tamanho) {
    do {
        printf("%s", prompt);
        fgets(destino, tamanho, stdin);
        destino[strcspn(destino, "\n")] = '\0';
        if (strlen(destino) == 0) {
            printf("  [!] Campo obrigatorio. Digite novamente.\n");
        }
    } while (strlen(destino) == 0);
}

int lerInteiro(const char *prompt, int min) {
    int valor;
    char buf[32];
    while (1) {
        printf("%s", prompt);
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &valor) == 1 && valor >= min) return valor;
        if (min > 0)
            printf("  [!] Valor invalido. Informe um numero inteiro maior que zero.\n");
        else
            printf("  [!] Valor invalido. Informe um numero inteiro maior ou igual a zero.\n");
    }
}

void selecionarTema(char *tema, char *descricao) {
    int opcao;
    char buf[32];

    while (1) {
        printf("\n  Selecione o tema da acao:\n");
        for (int i = 0; i < NUM_TEMAS; i++) {
            printf("    %d. %s\n", i + 1, TEMAS[i].tema);
            printf("       %s\n", TEMAS[i].descricao);
        }
        printf("    %d. Outro (digitar manualmente)\n", NUM_TEMAS + 1);
        printf("  Opcao: ");

        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &opcao) != 1 || opcao < 1 || opcao > NUM_TEMAS + 1) {
            printf("  [!] Opcao invalida. Escolha entre 1 e %d.\n", NUM_TEMAS + 1);
            continue;
        }

        if (opcao <= NUM_TEMAS) {
            strncpy(tema,      TEMAS[opcao - 1].tema,      TAM_STR - 1); tema[TAM_STR - 1]      = '\0';
            strncpy(descricao, TEMAS[opcao - 1].descricao, TAM_STR - 1); descricao[TAM_STR - 1] = '\0';
        } else {
            lerString("  Tema          : ", tema,      TAM_STR);
            lerString("  Descricao     : ", descricao, TAM_STR);
        }
        printf("  Tema selecionado: %s\n", tema);
        break;
    }
}

int buscarPorCodigo(int codigo) {
    for (int i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) return i;
    }
    return -1;
}

const char *situacaoStr(Situacao s) {
    switch (s) {
        case PLANEJADA: return "Planejada";
        case REALIZADA: return "Realizada";
        case CANCELADA: return "Cancelada";
        default:        return "Desconhecida";
    }
}

void linha(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

void exibirAcao(const Acao *a) {
    linha('-', 60);
    printf("  Codigo        : %d\n", a->codigo);
    printf("  Escola        : %s\n", a->escola);
    printf("  Tema          : %s\n", a->tema);
    printf("  Descricao     : %s\n", a->descricao);
    printf("  Data prevista : %s\n", a->data_prevista);
    printf("  Publico-alvo  : %s\n", a->publico_alvo);
    printf("  Responsavel   : %s\n", a->responsavel);
    printf("  Qtd. prevista : %d\n", a->qtd_prevista);
    printf("  Qtd. efetiva  : %d\n", a->qtd_efetiva);
    printf("  Situacao      : %s\n", situacaoStr(a->situacao));
}

void buscarPorCampo(const char *prompt, const char *nomeCampo, int campoBusca) {
    char termo[TAM_STR];
    lerString(prompt, termo, TAM_STR);

    int encontrou = 0;
    for (int i = 0; i < total; i++) {
        int achou;
        if (campoBusca == 1)
            achou = strstr(acoes[i].escola, termo) != NULL;
        else
            achou = strstr(acoes[i].tema, termo) != NULL;

        if (achou) {
            exibirAcao(&acoes[i]);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("  Nenhuma acao encontrada para %s contendo \"%s\".\n", nomeCampo, termo);
    } else {
        linha('-', 60);
    }
}

void exibirAsciiArt(void) { //Essa funçao foi construida atraves de IA afim de deixar mais estetico a inicializaçao do sistema.
    printf("\n");
    printf("  ██████╗ ███████╗███████╗    ███████╗███╗   ███╗      █████╗  ██████╗ █████╗  ██████╗ \n");
    printf("  ██╔══██╗██╔════╝██╔════╝    ██╔════╝████╗ ████║     ██╔══██╗██╔════╝██╔══██╗██╔═══██╗\n");
    printf("  ██████╔╝███████╗█████╗      █████╗  ██╔████╔██║     ███████║██║     ███████║██║   ██║\n");
    printf("  ██╔═══╝ ╚════██║██╔══╝      ██╔══╝  ██║╚██╔╝██║     ██╔══██║██║     ██╔══██║██║   ██║\n");
    printf("  ██║     ███████║███████╗    ███████╗██║ ╚═╝ ██║     ██║  ██║╚██████╗██║  ██║╚██████╔╝\n");
    printf("  ╚═╝     ╚══════╝╚══════╝    ╚══════╝╚═╝     ╚═╝     ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝ \n");
    printf("\n");
    printf("       Sistema de Planejamento e Acompanhamento de Acoes de Saude na Escola\n");
    printf("       UniCesumar  -  Engenharia de Software / ADS  -  2 Semestre 2026\n");
    linha('=', 90);
    printf("\n");
}


void exibirMenu(void) {
    printf("\n");
    linha('=', 50);
    printf("  MENU PRINCIPAL\n");
    linha('=', 50);
    printf("  1. Cadastrar acao do PSE\n");
    printf("  2. Listar acoes cadastradas\n");
    printf("  3. Pesquisar acao\n");
    printf("  4. Atualizar situacao da acao\n");
    printf("  5. Gerar resumo geral\n");
    linha('-', 50);
    printf("  0. Sair\n");
    linha('=', 50);
    printf("  Opcao: ");
}

void cadastrarAcao(void) {
    printf("\n--- CADASTRAR ACAO ---\n");

    if (total >= MAX_ACOES) {
        printf("  [!] Limite maximo de %d acoes atingido. Nao e possivel cadastrar.\n", MAX_ACOES);
        return;
    }

    Acao nova;
    memset(&nova, 0, sizeof(Acao));

    /* Código único */
    while (1) {
        nova.codigo = lerInteiro("  Codigo: ", 1);
        if (buscarPorCodigo(nova.codigo) != -1) {
            printf("  [!] Codigo %d ja existe. Informe outro.\n", nova.codigo);
        } else {
            break;
        }
    }

    lerString("  Escola        : ", nova.escola, TAM_STR);
    selecionarTema(nova.tema, nova.descricao);
    lerString("  Data prevista (DD/MM/AAAA): ", nova.data_prevista, 12);
    lerString("  Publico-alvo  : ", nova.publico_alvo,   TAM_STR);
    lerString("  Responsavel   : ", nova.responsavel,    TAM_STR);
    nova.qtd_prevista = lerInteiro("  Qtd. prevista de participantes: ", 1);

    nova.qtd_efetiva = 0;
    nova.situacao    = PLANEJADA;

    acoes[total] = nova;
    total++;

    printf("  [OK] Acao cadastrada com sucesso! Total de acoes: %d/%d\n", total, MAX_ACOES);
}

void listarAcoes(void) {
    printf("\n--- LISTA DE ACOES CADASTRADAS ---\n");

    if (total == 0) {
        printf("  Nenhuma acao cadastrada.\n");
        return;
    }

    printf("  Total: %d acao(oes)\n", total);
    for (int i = 0; i < total; i++) {
        exibirAcao(&acoes[i]);
    }
    linha('-', 60);
}

void pesquisarAcao(void) {
    printf("\n--- PESQUISAR ACAO ---\n");

    if (total == 0) {
        printf("  Nenhuma acao cadastrada.\n");
        return;
    }

    int opcao;
    char buf[32];

    while (1) {
        printf("\n  Criterio de pesquisa:\n");
        printf("    1. Por codigo\n");
        printf("    2. Por escola\n");
        printf("    3. Por tema\n");
        printf("    0. Voltar\n");
        printf("  Opcao: ");

        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &opcao) != 1) {
            printf("  [!] Opcao invalida.\n");
            continue;
        }

        if (opcao == 0) return;

        if (opcao == 1) {
            int codigo;
            printf("  Codigo: ");
            fgets(buf, sizeof(buf), stdin);
            if (sscanf(buf, "%d", &codigo) != 1) {
                printf("  [!] Codigo invalido.\n");
                continue;
            }
            int idx = buscarPorCodigo(codigo);
            if (idx == -1) {
                printf("  Nenhuma acao encontrada com codigo %d.\n", codigo);
            } else {
                exibirAcao(&acoes[idx]);
                linha('-', 60);
            }
        } else if (opcao == 2) {
            buscarPorCampo("  Escola (ou parte do nome): ", "escola", 1);
        } else if (opcao == 3) {
            buscarPorCampo("  Tema (ou parte): ", "tema", 2);
        } else {
            printf("  [!] Opcao invalida.\n");
        }
    }
}

void atualizarSituacao(void) {
    printf("\n--- ATUALIZAR SITUACAO ---\n");

    if (total == 0) {
        printf("  Nenhuma acao cadastrada.\n");
        return;
    }

    int codigo;
    char buf[32];

    printf("  Codigo da acao: ");
    fgets(buf, sizeof(buf), stdin);
    if (sscanf(buf, "%d", &codigo) != 1) {
        printf("  [!] Codigo invalido.\n");
        return;
    }

    int idx = buscarPorCodigo(codigo);
    if (idx == -1) {
        printf("  [!] Nenhuma acao encontrada com codigo %d.\n", codigo);
        return;
    }

    printf("\n  Acao localizada:\n");
    exibirAcao(&acoes[idx]);
    linha('-', 60);

    int nova;
    while (1) {
        printf("\n  Nova situacao:\n");
        printf("    1. Planejada\n");
        printf("    2. Realizada\n");
        printf("    3. Cancelada\n");
        printf("  Opcao: ");
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &nova) == 1 && nova >= 1 && nova <= 3) break;
        printf("  [!] Opcao invalida. Escolha 1, 2 ou 3.\n");
    }

    acoes[idx].situacao = (Situacao)(nova - 1);

    if (acoes[idx].situacao == REALIZADA) {
        acoes[idx].qtd_efetiva = lerInteiro("  Quantidade efetiva de participantes: ", 0);
    } else {
        acoes[idx].qtd_efetiva = 0;
    }

    printf("  [OK] Situacao atualizada para: %s\n", situacaoStr(acoes[idx].situacao));
}

void gerarResumo(void) {
    printf("\n--- RESUMO GERAL ---\n");

    if (total == 0) {
        printf("  Nenhuma acao cadastrada.\n");
        return;
    }

    int planejadas = 0, realizadas = 0, canceladas = 0;
    int prev_total = 0, efet_total = 0;

    for (int i = 0; i < total; i++) {
        switch (acoes[i].situacao) {
            case PLANEJADA:
                planejadas++;
                prev_total += acoes[i].qtd_prevista;
                break;
            case REALIZADA:
                realizadas++;
                prev_total += acoes[i].qtd_prevista;
                efet_total += acoes[i].qtd_efetiva;
                break;
            case CANCELADA:
                canceladas++;
                break;
        }
    }

    double percentual = (prev_total > 0)
        ? (efet_total * 100.0) / prev_total
        : 0.0;

    linha('=', 50);
    printf("  RESUMO DO PROGRAMA SAUDE NA ESCOLA\n");
    linha('=', 50);
    printf("  Acoes cadastradas  : %d\n", total);
    printf("  Planejadas         : %d\n", planejadas);
    printf("  Realizadas         : %d\n", realizadas);
    printf("  Canceladas         : %d\n", canceladas);
    linha('-', 50);
    printf("  Participantes previstos  : %d\n", prev_total);
    printf("  Participantes efetivos   : %d\n", efet_total);
    printf("  Percentual de participacao: %.1f%%\n", percentual);
    linha('=', 50);
}

int main(void) {
    exibirAsciiArt();

    int opcao;
    char buf[32];

    do {
        exibirMenu();
        fgets(buf, sizeof(buf), stdin);

        if (sscanf(buf, "%d", &opcao) != 1) {
            printf("  [!] Opcao invalida. Digite um numero do menu.\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: cadastrarAcao();   break;
            case 2: listarAcoes();     break;
            case 3: pesquisarAcao();   break;
            case 4: atualizarSituacao(); break;
            case 5: gerarResumo();     break;
            case 0:
                printf("\n  Encerrando o sistema PSE em Acao. Ate logo!\n\n");
                break;
            default:
                printf("  [!] Opcao invalida. Escolha entre 0 e 5.\n");
        }

    } while (opcao != 0);

    return 0;
}

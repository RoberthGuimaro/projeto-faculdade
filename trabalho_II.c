#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NUM_CIDADES 5
#define MAX_VEICULOS 10
#define MAX_VIAGENS 100
#define PRECO_COMBUSTIVEL 5.80f
#define DISPONIVEL 0
#define EM_VIAGEM 1
#define EM_MANUTENCAO 2

struct Veiculo
{
    int id; // identificador único
    char placa[8];
    char modelo[30];
    float consumoKmL;      // Consumo por litro
    float capacidadeCarga; // Capacidade de carga em toneladas
    int status;            // 0 - disponivel, 1 - em viagem, 2 - em manutenção
};

struct Viagem
{
    int idVeiculo;     // identificador único
    int cidadeOrigem;  // indice da cidade de 0 a N - 1
    int cidadeDestino; // indice da cidade de 0 a N - 1
    float distanciaTotal;
    float consumoEstimadoLitros;
    float custoEstimadoReais;
};

// nomes das cidades apenas para referencias nos menus e relatorios
const char *NOME_CIDADES[NUM_CIDADES] = {
    "0: Central",
    "1: Norte",
    "2: Sul",
    "3: Leste",
    "4: Oeste"};

// matris de distancia em km
// 0 - mesma cidade
// -1 - sem rota direta

int distancias[NUM_CIDADES][NUM_CIDADES] = {
    /*             0:Central  1:Norte  2:Sul  3:Leste  4:Oeste */
    /* 0:central */ {0, 45, 60, 30, 80},
    /* 1:norte   */ {45, 0, -1, 25, 110},
    /* 2:sul     */ {60, -1, 0, 70, 40},
    /* 3:leste   */ {30, 25, 70, 0, -1},
    /* 4:oeste   */ {80, 110, 40, -1, 0}};

static void lerLinha(const char *prompt, char *buffer, size_t tamanho)
{
    printf("%s", prompt);
    if (fgets(buffer, tamanho, stdin) == NULL)
    {
        printf("\nEntrada encererrada.\n");
        exit(0);
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0'; // Remove o caractere de nova linha
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }
}

static int lerInteiro(const char *prompt)
{
    char buffer[64], *endptr;
    for (;;)
    {
        lerLinha(prompt, buffer, sizeof(buffer));
        long valor = strtol(buffer, &endptr, 10);
        if (endptr != buffer && *endptr == '\0' && valor >= INT_MIN && valor <= INT_MAX)
        {
            return (int)valor;
        }
        printf("Entrada inválida. Por favor, insira um número inteiro.\n");
    }
}

static float lerFloat(const char *prompt)
{
    char buffer[64], *endptr;
    for (;;)
    {
        lerLinha(prompt, buffer, sizeof(buffer));
        float valor = strtof(buffer, &endptr);
        if (endptr != buffer && *endptr == '\0')
        {
            return valor;
        }
        printf("Entrada inválida. Por favor, insira um número válido.\n");
    }
}

int cadastrarVeiculo(struct Veiculo veiculos[], int quantidade)
{
    int id;
    int repetido;
    int i;

    if (quantidade >= MAX_VEICULOS)
    {
        printf("Limite de veículos atingido.\n");
        return quantidade;
    }
    do
    {
        id = lerInteiro("Digite o ID do veículo (número inteiro): ");
        repetido = 0;

        for (i = 0; i < quantidade; i++)
        {
            if (veiculos[i].id == id)
            {
                repetido = 1;
            }
        }

        if (repetido)
        {
            printf("ID já cadastrado.\n");
        }
    } while (repetido == 1);

    veiculos[quantidade].id = id;

    lerLinha("Digite a placa: ",
             veiculos[quantidade].placa,
             sizeof(veiculos[quantidade].placa));

    lerLinha("Digite o modelo: ",
             veiculos[quantidade].modelo,
             sizeof(veiculos[quantidade].modelo));

    do
    {
        veiculos[quantidade].consumoKmL =
            lerFloat("Digite o consumo em km/l: ");

        if (veiculos[quantidade].consumoKmL <= 0)
        {
            printf("O Consumo deve ser maior que zero.\n");
        }
    } while (veiculos[quantidade].consumoKmL <= 0);

    do
    {
        veiculos[quantidade].capacidadeCarga =
            lerFloat("Digite a capacidade eem toneladas: ");

        if (veiculos[quantidade].capacidadeCarga <= 0)
        {
            printf("A capacidade de carga deve ser maior que zero.\n");
        }
    } while (veiculos[quantidade].capacidadeCarga <= 0);

    veiculos[quantidade].status = DISPONIVEL;
    printf("Veículo cadastrado com sucesso!\n");
    return quantidade + 1;
}

void listarVeiculos(struct Veiculo veiculos[], int quantidade)
{
    int i;
    if (quantidade == 0)
    {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }

    printf("\nID\tPlaca\tModelo\tConsumo (km/l)\tCapacidade (t)\tStatus\n");
    for (i = 0; i < quantidade; i++)
    {
        printf("%d\t%s\t%s\t%f\t%f\t",
               veiculos[i].id,
               veiculos[i].placa,
               veiculos[i].modelo,
               veiculos[i].consumoKmL,
               veiculos[i].capacidadeCarga);
        if (veiculos[i].status == DISPONIVEL)
        {
            printf("Disponível\n");
        }
        else if (veiculos[i].status == EM_VIAGEM)
        {
            printf("Em viagem\n");
        }
        else if (veiculos[i].status == EM_MANUTENCAO)
        {
            printf("Em manutenção\n");
        }
    }
}

void consultarMatrix(void)
{
    int i;
    int j;
    int alterar;
    int origem;
    int destino;
    int distancia;

    printf("\nCidades:\n");

    for (i = 0; i < NUM_CIDADES; i++)
    {
        printf("%s\n", NOME_CIDADES[i]);
    }

    printf("\nOrigem/Destino\t0\t1\t2\t3\t4\n");

    for (i = 0; i < NUM_CIDADES; i++)
    {
        printf("%d\t\t", i);
        for (j = 0; j < NUM_CIDADES; j++)
        {
            printf("%d\t", distancias[i][j]);
        }
        printf("\n");
    }

    alterar = lerInteiro("\nDeseja alterar alguma distancia? (1-Sim / 0-Não): ");

    if (alterar == 1)
    {
        origem = lerInteiro("Digite a cidade de origem (0-4): ");
        destino = lerInteiro("Digite a cidade de destino (0-4): ");
        distancia = lerInteiro("Digite a nova distancia: ");

        if (origem == destino)
        {
            printf("As cidades devem ser diferentes.\n");
        }
        else if (distancia == 0 || distancia < -1)
        {
            printf("A distancia deve ser maior que zero ou -1 para sem rota direta.\n");
        }
        else
        {
            distancias[origem][destino] = distancia;
            distancias[destino][origem] = distancia; // Atualiza a matriz simetricamente

            printf("Distancia atualizada com sucesso!\n");
        }
    }
}

void simularViagem(struct Veiculo veiculos[], int quantidade)
{
    int id;
    int posicao = -1;
    int i;
    int confirmar;
    struct Viagem viagem;

    if (quantidade == 0)
    {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }

    id = lerInteiro("Digite o ID do veículo: ");

    for (i = 0; i < quantidade; i++)
    {
        if (veiculos[i].id == id)
        {
            posicao = i;
        }
    }

    if (posicao == -1)
    {
        printf("Veículo não encontrado.\n");
        return;
    }

    if (veiculos[posicao].status != DISPONIVEL)
    {
        printf("Veículo não está disponível.\n");
        return;
    }

    printf("\nCidades:\n");

    for (i = 0; i < NUM_CIDADES; i++)
    {
        printf("%s\n", NOME_CIDADES[i]);
    }

    viagem.idVeiculo = id;
    viagem.cidadeOrigem = lerInteiro("Digite a cidade de origem: ");
    viagem.cidadeDestino = lerInteiro("Digite a cidade de destino: ");

    if (viagem.cidadeOrigem < 0 || viagem.cidadeOrigem >= NUM_CIDADES ||
        viagem.cidadeDestino < 0 || viagem.cidadeDestino >= NUM_CIDADES)
    {
        printf("Cidades inválidas.\n");
        return;
    }

    viagem.distanciaTotal =
        distancias[viagem.cidadeOrigem][viagem.cidadeDestino];

    if (viagem.distanciaTotal <= 0)
    {
        printf("Não há rota direta entre as cidades selecionadas.\n");
        return;
    }

    viagem.consumoEstimadoLitros =
        viagem.distanciaTotal / veiculos[posicao].consumoKmL;

    viagem.custoEstimadoReais =
        viagem.consumoEstimadoLitros * PRECO_COMBUSTIVEL;

    printf("\nDistancia: %.2f km\n", viagem.distanciaTotal);
    printf("Consumo estimado: %.2f litros\n", viagem.consumoEstimadoLitros);
    printf("Custo estimado: R$ %.2f\n", viagem.custoEstimadoReais);

    confirmar = lerInteiro("Deseja confirmar a viagem? (1-Sim / 0-Não): ");

    if (confirmar == 1)
    {
        veiculos[posicao].status = EM_VIAGEM;
        printf("Viagem confirmada.\n");
    }
    else
    {
        printf("Viagem cancelada.\n");
    }
}

int main(void)
{
    struct Veiculo veiculos[MAX_VEICULOS];
    int quantidadeVeiculos = 0;

    int opcao;
    do
    {
        printf("\n======================================\n");
        printf("Sistema de Gerenciamento de Frota\n");
        printf("======================================\n");
        printf("1. Cadastrar Veículo\n");
        printf("2. Listar Veículos\n");
        printf("3. Consultar matriz de distancia\n");
        printf("4. Planejar / Simular viagem\n");
        printf("5. Relatório de desempenho de frota\n");
        printf("0. Sair\n");
        printf("======================================\n");

        opcao = lerInteiro("Escolha uma opção: ");

        if (opcao == 1)
        {
            quantidadeVeiculos = cadastrarVeiculo(veiculos, quantidadeVeiculos);
        }
        else if (opcao == 2)
        {
            listarVeiculos(veiculos, quantidadeVeiculos);
        }
        else if (opcao == 3)
        {
            consultarMatrix();
        }
        else if (opcao == 4)
        {
            simularViagem(veiculos, quantidadeVeiculos);
        }
        else if (opcao == 5)
        {
            printf("Opção 5: Relatório de desempenho de frota\n");
            // Implementar relatório de desempenho
        }
        else if (opcao == 0)
        {
            printf("Saindo do sistema...\n");
        }
        else
        {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
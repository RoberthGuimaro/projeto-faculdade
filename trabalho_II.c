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

struct Veiculo {
    int id; // identificador único
    char placa[8];
    char modelo[30];
    float consumoKmL; // Consumo por litro
    float capacidadeCarga; // Capacidade de carga em toneladas
    int status; // 0 - disponivel, 1 - em viagem, 2 - em manutenção
};

struct Viagem {
    int idVeiculo; // identificador único
    int cidadeOrigem; // indice da cidade de 0 a N - 1  
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
    "4: Oeste"
};

// matris de distancia em km
// 0 - mesma cidade
// -1 - sem rota direta

int distancias[NUM_CIDADES][NUM_CIDADES] = {
    /*             0:Central  1:Norte  2:Sul  3:Leste  4:Oeste */
    /* 0:central */ {   0,       45,    60,    30,    80 },
    /* 1:norte   */ {  45,        0,    -1,    25,   110 },
    /* 2:sul     */ {  60,       -1,     0,    70,    40 },
    /* 3:leste   */ {  30,       25,    70,     0,    -1 },
    /* 4:oeste   */ {  80,      110,    40,    -1,     0 }
};

static void lerLinha(const char *prompt, char *buffer, size_t tamanho) {
    printf("%s", prompt);
    if (fgets(buffer, tamanho, stdin) == NULL) {
        printf("\nEntrada encererrada.\n");
        exit(0);
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0'; // Remove o caractere de nova linha
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
}

static int lerInteiro(const char *prompt) {
    char buffer[64], *endptr;
    for (;;) {
        lerLinha(prompt, buffer, sizeof(buffer));
        long valor = strtol(buffer, &endptr, 10);
        if (endptr != buffer && *endptr == '\0' && valor >= INT_MIN && valor <= INT_MAX) {
            return (int)valor;
        }
        printf("Entrada inválida. Por favor, insira um número inteiro.\n");
    }
}

static float lerFloat(const char *prompt) {
    char buffer[64], *endptr;
    for (;;) {
        lerLinha(prompt, buffer, sizeof(buffer));
        float valor = strtof(buffer, &endptr);
        if (endptr != buffer && *endptr == '\0') {
            return valor;
        }
        printf("Entrada inválida. Por favor, insira um número válido.\n");
    }
}

int main(void) {
    return 0;
}
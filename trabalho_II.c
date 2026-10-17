#include <stdio.h>

#define NUM_CIDADES 5

// nomes das cidades apenas para referencias nos menus e relatorios
const char *NOME_CIDADES[NUM_CIDADES] = {
    "0: Central"",
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
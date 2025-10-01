// tema_atp.c : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

unsigned long lastid = 0;
FILE* logPointer;

typedef struct {
    int nivelSare;
    int nivelZahar;
} gust ;

typedef struct {
    int id;
    int esteSetat;
    char nume[100];
    int diametru;
    double lungime;
    float grosime;
    char material[100];
    gust gust;
} disc ;

disc citireObiect() {
    disc output;
    printf("numele obiectului? ");
    fgets(output.nume, 100, stdin);
    printf("diametrul obiectului? ");
    scanf("%d", &output.diametru); getchar();
    printf("lungimea obiectului? ");
    scanf("%lf", &output.lungime); getchar();
    printf("grosimea obiectului? 
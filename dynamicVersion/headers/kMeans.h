//
// Created by andrew on 31.10.2021.
//
#pragma once
#include <stddef.h>

//структура для инициализации радиус векторов
typedef struct {
    double x;
    double y;
    double z;
} rVector;

//структура для работы с потоками
typedef struct {
    size_t nVec;
    rVector *arrV;
    size_t nClus;
    rVector *centroids;
    size_t *arrI;
    size_t startIndex;
    double *sumX;
    double *sumY;
    double *sumZ;
    size_t *numInCluster;
    short *flag;
} argsT;

rVector *cMassCentroids(rVector *, size_t *, size_t, int *);

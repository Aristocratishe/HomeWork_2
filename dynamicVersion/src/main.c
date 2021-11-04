//
// Created by andrew on 31.10.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "kMeans.h"

#define ERROR -1
#define DEFAULT_CPU 4
//количество кластеров
const size_t NUMCLUSTERS = 33;

int main() {
    struct timespec mt1, mt2;
    long int tt;
    clock_gettime(CLOCK_REALTIME, &mt1);
    //определяем количество CPU (для Linux). Если не вышло берем дефолтный
    //параметр 4, исходя из доступности 4 ядерных процессоров
    int numThreads = sysconf(_SC_NPROCESSORS_CONF);
    if (numThreads == ERROR) {
        numThreads = DEFAULT_CPU;
    }
    numThreads = 100;
    size_t numVectors;
    rVector *arrVec = NULL;
    //считываем датасет из радиус векторов
    FILE *rFile;
    if ((rFile = fopen("/home/andrew/Technopark/Cxx/HW2/dynamicVersion/src/Vectors.txt", "r")) == NULL) {
        fprintf(stderr, "Error: Failed to open file Vectors.txt!\n");
        return ERROR;
    }
    if (fscanf(rFile, "%zu", &numVectors) == EOF) {
        fprintf(stderr, "Error while reading file Vector.txt!");
        return ERROR;
    }
    if (!(arrVec = (rVector *)malloc(numVectors * sizeof(rVector)))) {
        printf("Error: can't allocate memory!");
        return ERROR;
    }
    while (!feof(rFile)) {
        for (size_t j = 0; j < numVectors; ++j) {
            fscanf(rFile, "%lf%lf%lf", &arrVec[j].x, &arrVec[j].y, &arrVec[j].z);
        }
    }
    if (fclose(rFile)) {
        fprintf(stderr, "Failed to close file Vectors.txt!\n");
        return ERROR;
    }
    //функция кластеризации
    rVector *centroids = cMassCentroids(arrVec, &numVectors, NUMCLUSTERS, &numThreads);
    if (centroids == NULL) {
        fprintf(stderr, "Clusterization faild!\n");
        return ERROR;
    } else {
        printf(
            "Clusterization completed!\nYou can find the result in "
            "dynamic_Clusterization.txt.\n");
    }
    free(centroids);
    free(arrVec);
    clock_gettime(CLOCK_REALTIME, &mt2);
    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    printf("Затрачено время:\n %ld нс", tt);
    return 0;
}

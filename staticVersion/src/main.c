//
// Created by andrew on 31.10.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "kMeans.h"

#define ERROR -1

const size_t NUMCLUSTERS = 33;

int main() {
    struct timespec mt1, mt2;
    long int tt;
    clock_gettime(CLOCK_REALTIME, &mt1);
    size_t numVectors;
    rVector *arrVec = NULL;
    FILE *rFile;
    if ((rFile = fopen("/home/andrew/Technopark/Cxx/HW2/staticVersion/src/Vectors.txt", "r")) == NULL) {
        fprintf(stderr, "Error: Failed to open file Vectors.txt!\n");
        return ERROR;
    }
    if (fscanf(rFile, "%zu", &numVectors) == EOF) {
        fprintf(stderr, "Error while reading file Vector.txt!");
        return ERROR;
    }
    if (!(arrVec = (rVector *)malloc(numVectors * sizeof(rVector)))) {
        fprintf(stderr, "Error: can't allocate memory!");
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
    rVector *centroids = cMassCentroids(arrVec, &numVectors, NUMCLUSTERS);
    if (centroids == NULL) {
        fprintf(stderr, "Clusterization faild!\n");
        return ERROR;
    } else {
        printf(
            "Clusterization completed!\nYou can find the result in "
            "static_Clusterization.txt.\n");
    }
    free(centroids);
    free(arrVec);
    clock_gettime(CLOCK_REALTIME, &mt2);
    tt = 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
    printf("Затрачено время:\n %ld нс", tt);
    return 0;
}

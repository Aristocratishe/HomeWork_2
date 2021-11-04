//
// Created by andrew on 03.11.2021.
//
#include <gtest/gtest.h>

extern "C" {
#include "kMeans.h"
}

TEST(STATIC_TASK_TEST, ERROR) {
    size_t numVectors = 0;
    const size_t NUMCLUSTERS = 0;
    rVector *arrVec = NULL;
    rVector *centroids = cMassCentroids(arrVec, &numVectors, NUMCLUSTERS);
    EXPECT_TRUE(centroids == NULL);
    free(centroids);
}

TEST(STATIC_VERSION_TEST, BUILD_CLUSTERS_1) {
    const rVector arrVec[] = {{4, 1, 3}, {8, 2, 1}, {9, 5, 10}, {3, 12, 4}, {5, 8, 1}, {16, 2, 14}};
    size_t numVectors = 6;
    const size_t NUMCLUSTERS = 2;
    rVector *centroids = cMassCentroids((rVector *)arrVec, &numVectors, NUMCLUSTERS);
    EXPECT_TRUE(centroids != NULL);
    free(centroids);
}

TEST(STATIC_VERSION_TEST, BUILD_CLUSTERS_2) {
    const rVector arrVec[] = {
        {17.51935, 4.83933, 7.31391},  {18.61197, 14.67663, 3.97585}, {6.28084, 8.38299, 10.54547},
        {12.83125, 6.65387, 3.00175},  {3.00069, 7.32514, 7.92534},   {10.14032, 14.32039, 15.46236},
        {4.36395, 16.93418, 19.32989}, {9.79816, 2.65788, 12.40173},  {5.75201, 1.33823, 16.93058},
        {16.23622, 6.35485, 14.99310}, {17.06317, 7.16398, 12.07397}, {3.20934, 0.00995, 13.63433},
        {4.23398, 8.33680, 17.55979},  {3.08422, 1.40629, 1.11867},   {15.28839, 7.11091, 9.05751}};
    size_t numVectors = 15;
    const size_t NUMCLUSTERS = 3;
    rVector *centroids = cMassCentroids((rVector *)arrVec, &numVectors, NUMCLUSTERS);
    EXPECT_TRUE(centroids != NULL);
    free(centroids);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include "ransac.h"
#include "calcinverse.h"
#include <vector>
#include <math.h>
#include <time.h>
#include <cmath>
#include <iostream>

int const numRows = 640;
int const numColumns = 480;

using namespace std;

RANSAC::RANSAC() {}

vector<vector<int>> RANSAC::loadImage()
{
    //Create random image
    srand(time(NULL));
    vector<vector<int>> image;

    image.resize(numRows);
    for (int i = 0; i < numRows; ++i)
    {
        image[i].resize(numColumns, 0);
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            image[i][j] = rand() % (1 - 0 + 1);
        }
    }

    return image;
}

void RANSAC::printImage(vector<vector<int>> image)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }
}

vector<int> RANSAC::randomSample()
{
    vector<int> arr;
    arr.resize(4);
    srand(time(NULL));

    //Generate random rows and columns
    for (int i = 0; i < 4; i++)
    {
        arr[i] = rand() % (10 - 1 + 1) + 1;
    }

    return arr;
}

vector<double> RANSAC::fitLine(int rowPoint1, int colPoint1, int rowPoint2, int colPoint2)
{
    double rowP1 = static_cast<double>(rowPoint1);
    double colP1 = static_cast<double>(colPoint1);
    double rowP2 = static_cast<double>(rowPoint2);
    double colP2 = static_cast<double>(colPoint2);

    vector<double> p = {1.0, 1.0};
    vector<vector<double>> A = {
                             {rowP1, 1.0},
                             {rowP2, 1.0}
                            };
    vector<vector<double>> q = {
                             {colP1},
                             {colP2}
                            };

    //Solve linear system equation A^(-1)*q=p
    CalcInverse calcinv;
    vector<vector<double>> inverseA = calcinv.getInverse(A);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                p[k] = inverseA[i][k] * q[k][j];
            }
        }
    }

    return p;
}

double RANSAC::getConsistencyScore(vector<int> indices, double threshold, int a, int b)
{
    double score = 0;
    double squaredError;
    int rowsNum = indices.size() / 2;

    for (int i = 0; i < rowsNum; i+=2)
    {
        int error = a * indices[i] + b - indices[i+1];
        squaredError = pow(error, 2);

        if (squaredError < threshold)
        {
            score++;
        }
    }

    return score;
}

vector<int> RANSAC::getNonZeroIdx(vector<vector<int>> image)
{
    vector<int> nonZeros;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            if (image[i][j] == 1)
            {
                nonZeros.push_back(i);
                nonZeros.push_back(j);
            }
        }
    }

    return nonZeros;
}

vector<int> RANSAC::calcRansac(vector<vector<int>> image, int numOfIters, double threshold)
{
    int best_a = 0;
    int best_b = 0;
    vector<int> best_a_b;
    double maxScore = -1.0;
    vector<int> nonZeros = getNonZeroIdx(image);

    for (int i = 0; i < numOfIters; i++)
    {
        vector<int> randowPoint = randomSample();
        vector<double> a_b = fitLine(randowPoint[0], randowPoint[1], randowPoint[2], randowPoint[3]);
        double score = getConsistencyScore(nonZeros, threshold, a_b[0], a_b[1]);

        if (score > maxScore)
        {
            maxScore = score;
            best_a = a_b[0];
            best_b = a_b[1];
        }
    }

    best_a_b.resize(2);
    best_a_b[0] = best_a;
    best_a_b[1] = best_b;

    return best_a_b;
}

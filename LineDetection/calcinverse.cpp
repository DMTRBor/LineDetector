#include "calcinverse.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <stdexcept>

using namespace std;

CalcInverse::CalcInverse() {}

double CalcInverse::getDeterminant(vector<vector<double>> vect)
{
    if(vect.size() != vect[0].size())
    {
        throw runtime_error("Matrix is not quadratic");
    }
    int dimension = vect.size();

    if(dimension == 0)
    {
        return 1;
    }

    if(dimension == 1)
    {
        return vect[0][0];
    }

    //Formula for 2x2-matrix
    if(dimension == 2)
    {
        return vect[0][0] * vect[1][1] - vect[0][1] * vect[1][0];
    }

    double result = 0;
    int sign = 1;
    for(int i = 0; i < dimension; i++)
    {
        //Submatrix
        vector<vector<double>> subVect(dimension - 1, vector<double> (dimension - 1));
        for(int m = 1; m < dimension; m++)
        {
            int z = 0;
            for(int n = 0; n < dimension; n++)
            {
                if(n != i)
                {
                    subVect[m-1][z] = vect[m][n];
                    z++;
                }
            }
        }

        //recursive call
        result = result + sign * vect[0][i] * getDeterminant(subVect);
        sign = -sign;
    }

    return result;
}

vector<vector<double>> CalcInverse::getTranspose(vector<vector<double>> matrix1)
{
    //Transpose-matrix: height = width(matrix), width = height(matrix)
    vector<vector<double>> solution(matrix1[0].size(), vector<double> (matrix1.size()));

    //Filling solution-matrix
    for(size_t i = 0; i < matrix1.size(); i++)
    {
        for(size_t j = 0; j < matrix1[0].size(); j++)
        {
            solution[j][i] = matrix1[i][j];
        }
    }
    return solution;
}

vector<vector<double>> CalcInverse::getCofactor(vector<vector<double>> vect)
{
    if(vect.size() != vect[0].size())
    {
        throw std::runtime_error("Matrix is not quadratic");
    }

    vector<vector<double>> solution(vect.size(), vector<double> (vect.size()));
    vector<vector<double>> subVect(vect.size() - 1, vector<double> (vect.size() - 1));

    for(size_t i = 0; i < vect.size(); i++)
    {
        for(size_t j = 0; j < vect[0].size(); j++)
        {
            int p = 0;
            for(size_t x = 0; x < vect.size(); x++)
            {
                if(x == i)
                {
                    continue;
                }
                int q = 0;

                for(size_t y = 0; y < vect.size(); y++)
                {
                    if(y == j)
                    {
                        continue;
                    }

                    subVect[p][q] = vect[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = pow(-1, i + j) * getDeterminant(subVect);
        }
    }
    return solution;
}

vector<vector<double>> CalcInverse::getInverse(vector<vector<double>> vect)
{
    if(getDeterminant(vect) == 0)
    {
        throw runtime_error("Determinant is 0");
    }

    double d = 1.0/getDeterminant(vect);
    vector<vector<double>> solution(vect.size(), vector<double> (vect.size()));

    for(size_t i = 0; i < vect.size(); i++)
    {
        for(size_t j = 0; j < vect.size(); j++)
        {
            solution[i][j] = vect[i][j];
        }
    }

    solution = getTranspose(getCofactor(solution));

    for(size_t i = 0; i < vect.size(); i++)
    {
        for(size_t j = 0; j < vect.size(); j++)
        {
            solution[i][j] *= d;
        }
    }

    return solution;
}

void CalcInverse::printMatrix(vector<vector<double>> vect)
{
    for(size_t i = 0; i < vect.size(); i++)
    {
        for(size_t j = 0; j < vect[0].size(); j++)
        {
            cout << setw(8) << vect[i][j] << " ";
        }
        cout << "\n";
    }
}

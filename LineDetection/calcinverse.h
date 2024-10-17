#ifndef CALCINVERSE_H
#define CALCINVERSE_H
#include <vector>

class CalcInverse
{
public:
    CalcInverse();
    void printMatrix(std::vector<std::vector<double>> vect);
    std::vector<std::vector<double>> getInverse(std::vector<std::vector<double>> vect);

private:
    double getDeterminant(std::vector<std::vector<double>> vect);
    std::vector<std::vector<double>> getTranspose(std::vector<std::vector<double>> matrix1);
    std::vector<std::vector<double>> getCofactor(std::vector<std::vector<double>> vect);
};

#endif // CALCINVERSE_H

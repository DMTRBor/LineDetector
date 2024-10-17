#ifndef RANSAC_H
#define RANSAC_H
#include <vector>
#include <string>

typedef unsigned char unchar;

class RANSAC
{
public:
    RANSAC();
    // std::vector<std::vector<unsigned int>> loadImage(std::string fileName);
    std::vector<std::vector<int>> loadImage(std::string fileName);
    void printImage(std::vector<std::vector<int>> image);
    std::vector<int> calcRansac(std::vector<std::vector<int>> image, int numOfIters, double threshold);

private:
    std::vector<int> randomSample();
    std::vector<double> fitLine(int rowPoint1, int colPoint1, int rowPoint2, int colPoint2);
    std::vector<int> getNonZeroIdx(std::vector<std::vector<int>> image);
    double getConsistencyScore(std::vector<int> indices, double threshold, int a, int b);
};

#endif // RANSAC_H
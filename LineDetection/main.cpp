#include <iostream>
#include <string>
#include "ransac.h"

using namespace std;
typedef unsigned char unchar;

int main()
{
    string imagePath = "";
    bool isPrintImage = false;

    int numOfIters = 20;
    double threshold = 2;
    RANSAC ransac;

    vector<vector<int>> image = ransac.loadImage(imagePath);
    if (isPrintImage)
    {
        ransac.printImage(image);
    }

    vector<int> best_ab = ransac.calcRansac(image, numOfIters, threshold);
    cout << "Best a is: " << best_ab[0] << endl;
    cout << "Best b is: " << best_ab[1] << endl;

    return 0;
}

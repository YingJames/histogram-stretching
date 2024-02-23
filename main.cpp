#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>

#include "runFromParameters.hpp"
#include "utils.hpp"
#include "roi.hpp"
#include "rotateFlip.hpp"

using namespace std;
using namespace cv;

// void save_image(Mat tgt, string output_name);
vector<vector<string>> getParametersFromFile();

#define MAXLEN 256
int main()
{
    vector<vector<string>> parameters = getParametersFromFile();
    loopParams(parameters);
    return 0;
}

vector<vector<string>> getParametersFromFile()
{
    vector<vector<string>> parameters;
    vector<string> tempParameter;

    std::ifstream file("parameters.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: parameters.txt");
    }

    string line;
    while (getline(file, line))
    {
        vector<string> temp;
        stringstream ss(line);

        // remove comments and empty lines
        if (line.empty() || line[0] == '#')
            continue;

        string token;
        while (getline(ss, token, ' '))
        {
            temp.push_back(token);
        }

        parameters.push_back(temp);
    }
    file.close();
    return parameters;
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "utils.hpp"

using std::vector;
using namespace cv;

#define MAXLEN 256
int main()
{
    vector<vector<std::string>> parameters = getParametersFromFile();
    loopParams(parameters);
    return 0;
}

vector<vector<std::string>> getParametersFromFile()
{
    vector<vector<std::string>> parameters;
    vector<std::string> tempParameter;

    std::ifstream file("parameters.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: parameters.txt");
    }

    std::string line;
    while (getline(file, line))
    {
        vector<std::string> temp;
        std::stringstream ss(line);

        // remove comments and empty lines
        if (line.empty() || line[0] == '#')
            continue;

        std::string token;
        while (getline(ss, token, ' '))
        {
            temp.push_back(token);
        }

        parameters.push_back(temp);
    }
    file.close();
    return parameters;
}

#include <bits/stdc++.h>

std::vector<std::vector<int>> getCSVvector(std::string CSVFile)
{
    std::vector<std::vector<int>> content;
    std::string line;
    std::fstream file(CSVFile);

    while (getline(file, line))
    {
        std::vector<int> lineContent;
        for (size_t i = 0; i < line.length(); ++i)
        {
            int currentNum = 0;
            bool sign = true;
            for (; isdigit(line[i]) || line[i] == '-'; ++i)
            {
                if (line[i] == '-')
                {
                    sign = false;
                }
                else
                {
                    currentNum *= 10;
                    currentNum += line[i] - '0';
                }
            }
            lineContent.push_back(sign ? currentNum : -currentNum);
        }
        content.push_back(lineContent);
    }

    return content;
}

int main()
{
    auto info = getCSVvector("test.csv");
    /* 
    -1,-2,-3,-4
    -1,0,1,2
    -1,-1,-1,-1
    -1,-1,-1,5
    */
    assert(info[0][0] == -1);

    assert(info[1][1] == 0);

    assert(info[3][3] == 5);
}
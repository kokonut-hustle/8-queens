#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unordered_set>

using namespace std;

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i = 0; i < v.size(); i++) {
            seed ^= hasher(v[i]) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

void random_input(vector<int> &inp)
{
    for (int i = 0; i < 8; i++)
    {
        inp.push_back(rand() % 8 + 1);
        // inp.push_back(1);
    }
}

void file_input(vector<int> &inp)
{
    ifstream fin;
    fin.open("input.txt");
    int temp;
    for (int i = 0; i < 8; i++)
    {
        fin >> temp;
        inp.push_back(temp);
    }
    fin.close();
}

void output(vector<int> &inp)
{
    for (int i = 0; i < 8; i++)
        cout << inp[i] << " ";
    cout << endl;
}

int cal_h(vector<int> &inp)
{
    int res = 0;
    for (int i = 0; i < 8; i++)
        for(int j = i+1; j < 8; j++)
        {
            if (inp[i] == inp[j])
                ++res;
        }

    for (int i = 0; i < 8; i++)
        for(int j = i+1; j < 8; j++)
        {
            if (inp[i] + i == inp[j] + j)
                ++res;
        }

    for (int i = 0; i < 8; i++)
        for(int j = i+1; j < 8; j++)
        {
            if (inp[i] - i == inp[j] - j)
                ++res;
        }

    return res;
}

vector<int> next_state(unordered_set<vector<int>, VectorHash> &us, vector<int> inp)
{
    for (int i = 0; i < 8; i++)
    {
        vector<int> res;
        for (int k = 0; k < 8; k++)
            res.push_back(inp[k]);
        for (int j = 1; j <= 8; j++)
        {
            res[i] = j;
            if (us.find(res) == us.end())
            {
                us.insert(res);
                return res;
            }
        }
    }
}

void draw(vector<int> &inp)
{
    for (int i = 0; i <= 16; i++)
    {
        if (i % 2 == 0)
            cout << "-----------------" << endl;
        else
        {
            for (int j = 0; j < 8; j++)
            {
                cout << "|";
                if (inp[j] - 1 == i / 2)
                    cout << "x";
                else 
                    cout << " ";
            }
            cout << "|" << endl;
        }
    }
}

int main()
{
    vector<int> inp;
    random_input(inp);
    // file_input(inp);
    cout << "random input" << endl;
    output(inp);

    int h = cal_h(inp);
    unordered_set<vector<int>, VectorHash> us;
    us.insert(inp);
    int t = 0;
    while (h != 0) 
    {
        ++t;
        inp = next_state(us, inp);
        h = cal_h(inp);
        // if (t % 100000 == 0)
        // {
        //     cout << "temp state" << endl;
        //     output(inp);
        //     cout << h << endl;
        // }
    }

    cout << "solution" << endl;
    output(inp);

    draw(inp);

    return 0;
}
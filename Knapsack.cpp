#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

int Solver(int N, vector<int> datas, vector<int> W, int ker)
{
    vector<int> arr_1(ker+1, 0);
    vector<int> arr_2(ker+1, 0);
    for (int i=1; i<=N; i++)
    {
        vector<int> mass = arr_1;
        arr_1 = arr_2;
        arr_2 = mass;
        for (int j=0; j<=ker; j++)
        {
            arr_2[j] = arr_1[j];
            if (j - W[i-1] >= 0)
                arr_2[j] = max(arr_2[j], arr_1[j-W[i-1]] + datas[i-1]);
        }
    }

    int res = 0;

    for (int i=ker; i>=0; i--)
        if (arr_2[i] != 0)
        {
            res = arr_2[i];
            break;
        }
    return res;
}

int main()
{
    string path = "C:/Users/Максим/Desktop/Knapsack/data";
    auto iter = filesystem::directory_iterator(path);
    vector<filesystem::path> arr;
    copy_if(filesystem::begin(iter), filesystem::end(iter), std::back_inserter(arr),
        [](const auto& entry)
        {
            return filesystem::is_regular_file(entry);
        });

    for (auto& i : arr)
    {
        ifstream fin;
        fin.open(i.string());
        cout << i.string() << endl;
        int N, ker;
        fin >> N >> ker;
        vector<int> datas;
        vector<int> W;

        for (int i=0; i<N; i++)
        {
            int val, wght;
            fin >> val >> wght;
            datas.push_back(val);
            W.push_back(wght);
        }
        int max = Solver(N, datas, W, ker);
        cout << max << endl;
    }
    return 0;
}
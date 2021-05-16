#include <bits/stdc++.h>
using namespace std;

string printProcessSec(vector<int> arr, bool reqMode, int processNumber)
{
    string processes = "";
    int n = arr.size();

    processes += '<';
    if(reqMode)
        processes += "P"+to_string(processNumber)+"req,";
    for (int i = 0; i < n; i++)
    {
        processes += ("P" + to_string(arr[i]));
        if (i != n - 1)
            processes += ',';
        else
            processes += '>';
    }
    return processes;
}
void printNeedMat(vector<vector<int>> Need)
{
    for (int i = 0; i < Need.size(); i++)
    {
        for (int j = 0; j < Need[0].size(); j++)
        {
            cout << Need[i][j] << " ";
        }
        cout << endl;
    }
}

void fillUpInstancesMat(vector<vector<int>> Allocation, vector<int> Available, vector<int> &instances)
{

    int m = Allocation[0].size();
    int n = Allocation.size();
    for (int col = 0; col < m; col++)
    {
        int sum = 0;
        for (int row = 0; row < n; row++)
        {
            sum += Allocation[row][col];
        }
        instances[col] = sum + Available[col];
    }
}

void getNeedMat(vector<vector<int>> Allocation, vector<vector<int>> Max, vector<vector<int>> &Need)
{

    int m = Allocation[0].size();
    int n = Allocation.size();
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            Need[row][col] = Max[row][col] - Allocation[row][col];
        }
    }
}

bool LTE(vector<int> first, vector<int> second)
{
    for (int i = 0; i < first.size(); i++)
    {
        if (first[i] > second[i])
            return false;
    }
    return true;
}

void increaseMat_By_(vector<int> &mat1, vector<int> mat2)
{
    for (int i = 0; i < mat1.size(); i++)
    {
        mat1[i] += mat2[i];
    }
}
void decreaseMat_By_(vector<int> &mat1, vector<int> mat2)
{
    for (int i = 0; i < mat1.size(); i++)
    {
        mat1[i] -= mat2[i];
    }
}

bool isSafe(vector<vector<int>> Need, vector<vector<int>> Allocation, vector<int> Work, vector<int> &processOrder)
{
    int n = Need.size();
    int m = Work.size();

    vector<bool> Finish(n, false);

    bool edited = true;
    while (edited)
    {
        edited = false;
        for (int i = 0; i < n; i++)
        {
            if (!Finish[i] && LTE(Need[i], Work))
            {
                Finish[i] = true;
                processOrder.push_back(i);
                increaseMat_By_(Work,Allocation[i]);
                edited = true;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (!Finish[i])
            return false;
    }

    return true;
}

void safeAlgorithm(vector<vector<int>> Need, vector<vector<int>> Allocation, int requestProcess, vector<int> Work)
{
    vector<int> processOrder;
    bool safe = isSafe(Need, Allocation, Work, processOrder);
    string answer;
    if (requestProcess < 0)
        answer = safe ? "Yes , Safe state " : "No";
    else
        answer = safe ? "Yes request can be granted with safe state , Safe state " : "No";
    cout << answer;
    if (safe)
        cout << printProcessSec(processOrder, requestProcess >= 0,requestProcess) << endl;
    else
        cout << endl;
}

void resource_request_algorithm(vector<int> request, vector<vector<int>> Need, vector<vector<int>> Allocation, vector<int> Available, int processNumber)
{
    if (!LTE(request, Need[processNumber]))
    {
        cout << "No" << endl;
        return;
    }
    if (!LTE(request, Available))
    {
        cout << "No" << endl;
        return;
    }
    decreaseMat_By_(Available,request);
    increaseMat_By_(Allocation[processNumber],request);
    decreaseMat_By_(Need[processNumber],request);

    safeAlgorithm(Need,Allocation,processNumber,Available);

}

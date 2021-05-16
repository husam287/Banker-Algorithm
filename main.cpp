#include <bits/stdc++.h>
#include "banker-algorithm.h"

using namespace std;

int main()
{
    // ifstream file1("matrices.txt");
    // cin.rdbuf(file1.rdbuf());

    int n; //process
    cout<<"Enter Number Of Processes: ";
    cin >> n;
    int m; //resorces
    cout<<endl<<"Enter Number Of Resources: ";
    cin >> m;
    cout<<endl;

    vector<vector<int>> Allocation(n, vector<int>(m));
    vector<vector<int>> Max(n, vector<int>(m));
    vector<int> Available(m);

    cout << "Please Enter Allocation Matrix" << endl;
    //fill Allocation matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> Allocation[i][j];
        }
    }

    cout << "Please Enter Max Matrix" << endl;
    //fill Max matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> Max[i][j];
        }
    }

    cout << "Please Enter Available Matrix" << endl;
    //fill Available matrix
    for (int j = 0; j < m; j++)
    {
        cin >> Available[j];
    }

    //filling instances matrix
    vector<int> instances(m);
    fillUpInstancesMat(Allocation, Available, instances);

    vector<vector<int>> Need(n, vector<int>(m));
    getNeedMat(Allocation, Max, Need);

    cout<<endl;
    cout << "####################\nNeed Matrix\n####################" << endl;
    printNeedMat(Need);

    cout << "______________________________" << endl;
    cout << "1: Check Safety\n2: Enter a request from a process\n3: Exit" << endl;
    cout << "______________________________" << endl;

    while (1)
    {
        int op;
        cin >> op;

        vector<int> request(m);
        int processNumber;
        switch (op)
        {
        case 1:
            safeAlgorithm(Need, Allocation, -1, Available);
            break;

        case 2:
            cout<<"Enter The Process Number: ";
            cin>>processNumber;
            cout<<endl<<"Enter The Request Vector: ";
            for (int i = 0; i < m; i++)
            {
                cin >> request[i];
            }
            cout<<endl;
            resource_request_algorithm(request, Need, Allocation, Available, processNumber);
            break;

        default:
            return 0;
        }
    }

    return 0;
}
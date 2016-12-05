#include <iostream>
#include <queue>

using namespace std;

struct Objek
{
    long weight, profit;
};

struct Node
{
    long weight, profit, level, bound;
};

double pperw(Objek a)
{
    return (double) a.profit/a.weight;
}

Objek* bubblesort(Objek arr[], long n)
{
    bool tuker = true;
    long j = 0;
    while (tuker)
    {
        tuker = false;
        j++;
        for (long i=0; i<n-j; i++)
        {
            if (pperw(arr[i]) < pperw(arr[i+1]))
            {
                Objek tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                tuker = true;
            }
        }
    }
    return arr;
}

long bound(Node u, long n, long W, Objek arr[])
{
    if (u.weight >= W)
    {
        return 0;
    }
    long profit_bound = u.profit;
    long j = u.level + 1;
    long totweight = u.weight;
    while ((j < n) && (totweight + arr[j].weight <= W))
    {
        totweight += arr[j].weight;
        profit_bound += arr[j].profit;
        j++;
    }
    if (j < n)
    {
        profit_bound += (W - totweight) * pperw(arr[j]);
    }
    return profit_bound;
}

long knapsack(long W, Objek arr[], long n)
{
    bubblesort(arr, n);
    queue<Node> Q;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    Q.push(u);
    long maxprofit = 0;
    while (!Q.empty())
    {
        u = Q.front();
        Q.pop();

        if (u.level == -1)
        {
            v.level = 0;
        }

        if (u.level == n-1)
        {
            continue;
        }
        v.level = u.level + 1;
        v.weight = u.weight + arr[v.level].weight;
        v.profit = u.profit + arr[v.level].profit;
        if (v.weight <= W && v.profit > maxprofit)
        {
            maxprofit = v.profit;
        }
        v.bound = bound(v, n, W, arr);
        if (v.bound > maxprofit)
        {
            Q.push(v);
        }
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, arr);
        if (v.bound > maxprofit)
        {
            Q.push(v);
        }
    }
    return maxprofit;
}

int main()
{
    long n,k;
    long* w = NULL;
    long* p = NULL;
    Objek* arr = NULL;

    cout << "input : " << endl;
    cin >> n;
    w = new long[n];
    p = new long[n];
    arr = new Objek[n];
    for (long i=0; i<n; i++)
    {
        cin >> w[i] >> p [i];
        arr[i].weight = w[i];
        arr[i].profit = p[i];
    }
    cin >> k;

    cout << "output : " << endl;
    cout << knapsack(k, arr, n) << endl;
    cin.get(); cin.get();
    return 0;
}

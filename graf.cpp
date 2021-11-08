#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;

ifstream in("ctc.in");
ofstream out("ctc.out");

const int maxi = 100001;
const bool problema = 1; //0 pt problema bfs

class Graf
{
private:
    int n, m, s;
    vector<int> v[maxi];

public:
    Graf(bool tip);
    void bfs();                                     //bfs
    void dfs(int nod, int viz[]);                   //nr componente conexe
    void nrconex();                                 //-----
    void dfstop(int nod, int viz[], stack<int> &s); //sortare topologica
    void sortaret();                                //-----
    void ctc();                                     //nr componente tare conexe
    void ordine(int nod, int viz[], stack<int> &s); //-----
    void dfsctc(int nod, int viz[], int ok);        //-----
    Graf trans();                                   //-----
};

Graf::Graf(bool tip) //true pt orientat
{
    int i;
    in >> n >> m;
    if (problema == 0)
        in >> s;
    for (i = 1; i <= m; i++)
    {
        int x, y;
        in >> x >> y;
        v[x].push_back(y);
        if (tip == false)
            v[y].push_back(x);
    }
}

void Graf::bfs()
{
    int i;
    int dist[n + 1];
    for (i = 1; i <= n; i++)
        dist[i] = -1;
    dist[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        int nc = q.front();                //nod curent
        for (i = 0; i < v[nc].size(); i++) //parcurgerm vecinii lui nc
        {
            if (dist[v[nc][i]] == -1)
            {
                q.push(v[nc][i]);
                dist[v[nc][i]] = dist[nc] + 1;
            }
        }
        q.pop();
    }

    for (i = 1; i <= n; i++)
        out << dist[i] << " ";
    out.close();
}

void Graf::dfs(int nod, int viz[])
{
    viz[nod] = 1;
    int i;
    for (i = 0; i < v[nod].size(); i++) //parcurgem vecinii nodului, se marcheaza toata componenta conexa ca fiind vizitata
    {
        if (viz[v[nod][i]] == 0)
        {
            dfs(v[nod][i], viz);
        }
    }
}

void Graf::nrconex()
{
    int k = 0, i;
    int viz[n + 1] = {0};
    for (i = 1; i <= n; i++)
        if (viz[i] == 0)
        {
            dfs(i, viz);
            k++;
        }
    out << k;
}

void Graf::dfstop(int nod, int viz[], stack<int> &s)
{
    viz[nod] = 1;
    int i;
    for (i = 0; i < v[nod].size(); i++)
    {
        if (viz[v[nod][i]] == 0)
            dfstop(v[nod][i], viz, s);
    }
    s.push(nod);
}

void Graf::sortaret()
{
    int i;
    stack<int> s;
    int viz[n + 1] = {0};
    for (i = 1; i <= n; i++)
        if (viz[i] == 0)
            dfstop(i, viz, s);

    while (!s.empty())
    {
        out << s.top() << " ";
        s.pop();
    }
}

void Graf::dfsctc(int nod, int viz[], int ok)
{
    viz[nod] = 1;
    if (ok == 1)
        out << nod << " ";
    int i;
    for (i = 0; i < v[nod].size(); i++)
    {
        if (viz[v[nod][i]] == 0)
            dfsctc(v[nod][i], viz, ok);
    }
}

Graf Graf::trans()
{
    int i;
    Graf g(true);
    for (i = 1; i <= n; i++)
    {
        vector<int>::iterator j;
        for (j = v[i].begin(); j != v[i].end(); j++)
            g.v[*j].push_back(i);
    }
    return g;
}

void Graf::ordine(int nod, int viz[], stack<int> &s)
{
    viz[nod] = 1;
    for (int i = 0; i < v[nod].size(); i++)
        if (viz[v[nod][i]] == 0)
            ordine(v[nod][i], viz, s);
    s.push(nod);
}

void Graf::ctc()
{
    int i, k = 0, ok = 0;
    stack<int> s;
    stack<int> s2;
    int viz[n + 1] = {0};
    for (i = 1; i <= n; i++)
        if (viz[i] == 0)
            ordine(i, viz, s);
    Graf gr = trans();
    for (i = 1; i <= n; i++)
        viz[i] = 0;
    s2 = s;
    while (!s.empty())
    {
        int nod = s.top();
        s.pop();
        if (viz[nod] == 0)
        {
            gr.dfsctc(nod, viz, ok);
            k++;
        }
    }
    ok = 1;
    out << k << endl;
    for (i = 1; i <= n; i++)
        viz[i] = 0;
    while (!s2.empty())
    {
        int nod = s2.top();
        s2.pop();
        if (viz[nod] == 0)
        {
            gr.dfsctc(nod, viz, ok);
            out << endl;
        }
    }
}

int main()
{
    Graf g(true);
    g.ctc();

    return 0;
}

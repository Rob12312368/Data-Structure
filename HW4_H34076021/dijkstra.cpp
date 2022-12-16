#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;
typedef struct edge{
    char v1;
    char v2;
    int weight;
    bool marked;

}edge;
typedef struct distance{
    char v;
    int dis;
}dist;
ofstream outfile;

int dijk(edge earr[],dist answer[],char sv,int edgecount)
{
    for(int i=0;i<edgecount;i++)
    {
        answer[i].dis = 100000;
        answer[i].v = -1;
    }
    int index = 0;
    answer[index].v = sv;
    answer[index].dis = 0;
    index++;
    string checked;
    string temp;
    checked += sv;
    temp = checked;
    while(checked.size()>0)
    {
        for(int i=0;i<edgecount;i++)
        {
            if(checked.find(earr[i].v1)!=string::npos)//spread to new edges connected to the visited vertices
            {
                int found;
                int found2;
                for(int j=0;j<index;j++)//find the current vertex's accumulated distance
                {
                    if(answer[j].v == earr[i].v1)
                    {
                        found = j;
                    }
                    if(answer[j].v == earr[i].v2)
                    {
                        found2 = j;
                    }
                }
                if(checked.find(earr[i].v2)!=string::npos)//spread to visited vertices
                {
                    if(answer[found].dis+earr[i].weight<answer[found2].dis)
                        answer[found2].dis = answer[found].dis+earr[i].weight;
                }
                else{ //spread to new vertices
                    answer[index].v = earr[i].v2;
                    answer[index].dis = answer[found].dis+earr[i].weight;
                    temp+=earr[i].v2;
                    index++;
                }
            }
        }
        checked = temp;
        temp.clear();
    }
    return index;
}
int main()
{
    int edgecount;
    string filename;
    cout << "Enter file name: ";
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    outfile.open("output_p.txt");
    if(!infile.is_open())
    {
        cout << "infile open error";
        return 0;
    }
    if(!outfile.is_open())
    {
        cout << "outfile open error";
        return 0;
    }

    string line;
    getline(infile,line);
    edgecount = stoi(line);
    //cout << edgecount << endl;

    edge edgearr[edgecount];
    dist answer[edgecount];
    for(int i=0;i<edgecount;i++)
    {
        char edge[10];
        char s,e; //start and end of an edge
        int w;
        char *token;
        getline(infile,line);
        strcpy(edge,line.c_str());
        token = strtok(edge," "); //tokenize the string

        int j = 0;
        while( token != NULL )
        {
            if(j==0)
                edgearr[i].v1 = token[0];
            else if(j == 1)
                edgearr[i].v2 = token[0];
            else
                edgearr[i].weight = atoi(token);
            j++;
            token = strtok(NULL, " ");
        }
        edgearr[i].marked = false;
        //cout << edgearr[i].v1 << "..." << edgearr[i].v2 << "..." << edgearr[i].weight << endl;
    }

    char startv;
    getline(infile,line);
    startv = line[0];
    //cout << startv << endl;

    int funback = dijk(edgearr,answer,startv,edgecount);
    for(int i=0;i<funback;i++)
    {
        cout << answer[i].v << " " << answer[i].dis << endl;
    }
    outfile.close();
    return 0;
}

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
ofstream outfile;

int prim(edge earr[],edge answer[],char sv,int edgecount)
{
    string alpha;
    int bound;
    char lastalpha = earr[edgecount-1].v2;
    char firstalpha = earr[0].v1;
    /*if(earr[edgecount-1].v1>earr[edgecount-1].v2)
        lastalpha = earr[edgecount-1].v1;
    else
        lastalpha = earr[edgecount-1].v2;
    if(earr[0].v1<earr[0].v2)
        firstalpha = earr[0].v1;
    else
        firstalpha = earr[0].v2;*/

    for(int i=0;i<edgecount;i++)
    {
        if(earr[i].v1<firstalpha)
            firstalpha = earr[i].v1;
        if(earr[i].v2>lastalpha)
            lastalpha = earr[i].v2;
    }
    alpha += sv;

    bound = (int)(lastalpha-firstalpha);
    for(int i=0;i<bound;i++)
    {
        int smallest=100000;
        int ans = 0;
        for(int j=0;j<edgecount;j++)
        {
            if((earr[j].marked == false) && ((alpha.find(earr[j].v1)!=string::npos) || (alpha.find(earr[j].v2)!=string::npos)))//pick new edges connected to the selected vertices
            {
                if((alpha.find(earr[j].v1)!=string::npos) && (alpha.find(earr[j].v2)!=string::npos))
                {
                    continue;
                }
                if(earr[j].weight<smallest)
                {
                    ans = j;
                    smallest = earr[j].weight;
                }
            }
        }
        if(alpha.find(earr[ans].v1)!=string::npos)//string contains the element
        {
            alpha+=earr[ans].v2;
        }
        else{
            alpha+=earr[ans].v1;
        }
        earr[ans].marked = true;
        answer[i].v1 = earr[ans].v1;
        answer[i].v2 = earr[ans].v2;
        answer[i].weight = earr[ans].weight;
        cout << alpha << endl;
    }
    return bound;
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
    edge answer[edgecount];
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

    int ans = prim(edgearr,answer,startv,edgecount);

    for(int i=0;i<ans-1;i++)
    {
        int smallest = answer[i].weight;
        int index = i;
        for(int j=i+1;j<ans;j++)
        {
            if(answer[j].weight<smallest)
            {
                smallest = answer[j].weight;
                index = j;
            }
        }
        edge temp;
        temp = answer[i];
        answer[i] = answer[index];
        answer[index] = temp;

        if(answer[i].v1>answer[i].v2)
        {
            char t = answer[i].v1;
            answer[i].v1 = answer[i].v2;
            answer[i].v2 = t;
        }
    }

    for(int i=0;i<ans;i++)
    {
        cout << answer[i].v1 << " " << answer[i].v2 << " " << answer[i].weight << endl;
        outfile << answer[i].v1 << " " << answer[i].v2 << " " << answer[i].weight << endl;
    }
    outfile << startv;

    outfile.close();
    return 0;
}

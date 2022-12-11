#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <unistd.h>
using namespace std;
typedef struct elements{ //the struct for method2
    int m,n, value;
}elements;
void printmatrix(ofstream& outfile, int** matrix, int rows, int columns) //print all the non-zero element in a matrix
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            if(matrix[i][j]!=0)
            {
                outfile << "(" << i << "," << j << "," << matrix[i][j] << ") " << "becomes"
                << " (" << j << "," << i << "," << matrix[i][j] << ") " << "in the transpose";
                outfile << endl;
            }
        }
    }
}
void transpose(int** matrix, int** transposed, int rows, int columns) //exchange the x and y and put them into another matrix
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<columns;j++)
        {
            transposed[j][i] = matrix[i][j];
        }
    }
}
void transposeStruct(elements* e, elements* transposede) /*the proposed solution in the textbook, which scans every column
and non-zero element. If there are any elements in that column, exchange its x and y  to transpose*/
{
    int n = e[0].value;
    transposede[0].m = e[0].n;
    transposede[0].n = e[0].m;
    transposede[0].value = n;

    if(n>0)
    {
        int current = 1;
        for(int i=0;i<e[0].n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(e[j].n == i)
                {
                    transposede[current].m = e[j].n;
                    transposede[current].n = e[j].m;
                    transposede[current].value = e[j].value;
                    current++;
                }
            }
        }
    }
}
int main()
{
    int rows,columns;
    int counttime = 0; //for counting looping times
    int** matrix; //for traditional method
    int** transposed;
    elements* e; //for method2
    elements* transposede;
    vector <elements> store; //for storing all the non-zero elements
    string oneline;
    ifstream file("p1.in");
    ofstream outfile("p1.out");
    while(getline(file,oneline))
    {
        if(counttime == 0)//allocate space based on the given dimension
        {
            sscanf(oneline.c_str(),"%d%d",&rows,&columns);
            matrix = (int**)malloc(sizeof(int*)*rows);
            transposed = (int**)malloc(sizeof(int*)*columns);
            for(int i=0;i<rows;i++)
            {
                matrix[i] = (int*)calloc(columns,sizeof(int*));
            }
            for(int i=0;i<columns;i++)
            {
                transposed[i] = (int*)calloc(rows,sizeof(int*));
            }
        }
        else //fill all the elements into 2d matrix and vector
        {
            int row, column, value;
            sscanf(oneline.c_str(),"%d%d%d",&row,&column,&value);
            matrix[row][column] = value;
            elements temp;
            temp.m = row;
            temp.n = column;
            temp.value = value;
            store.push_back(temp);
        }

        counttime++;
    }
    //plug matrix size and element count into the beginning of the vector
    elements first;
    first.m = rows;
    first.n = columns;
    first.value = counttime-1;
    store.insert(store.begin(),first);

    //allocate memory for struct array for method2
    e = (elements*)malloc(sizeof(elements)*store[0].value);
    transposede = (elements*)malloc(sizeof(elements)*store[0].value);
    //put the data from the vector into the struct array
    for(int i=0;i<store.size();i++)
    {
        e[i].m = store[i].m;
        e[i].n = store[i].n;
        e[i].value = store[i].value;
    }
    file.close();

    printmatrix(outfile,matrix,rows,columns);

    auto t_start = chrono::steady_clock::now();
    transpose(matrix, transposed, rows, columns);
    auto t_end = chrono::steady_clock::now();
    outfile << chrono::duration_cast<chrono::nanoseconds>(t_end - t_start).count() << "ns" << endl;

    t_start = chrono::steady_clock::now();
    transposeStruct(e,transposede);
    t_end = chrono::steady_clock::now();
    outfile << chrono::duration_cast<chrono::nanoseconds>(t_end - t_start).count() << "ns" << endl;

    outfile.close();
    /*please note that difference between the time of two methods will only appear as the dimension of the matrix is
    big enough, for example, 100*100*/
    return 0;
}

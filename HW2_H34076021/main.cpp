/*This program is an implementation of the Rat in A Maze problem solved by using
stack. For more reference, please read the PDF in this repository*/
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
typedef struct offsets{
    int row;
    int col;
}offsets;
typedef struct element{
    int row;
    int col;
    int dir;
}ele;
void inioff(offsets off[]){ //initialize nine direction defined in the assignment requirement
    off[0].row = 0; off[0].col = 0;
    off[1].row = 0; off[1].col = 1;
    off[2].row = 1; off[2].col = 1;
    off[3].row = 1; off[3].col = 0;
    off[4].row = 1; off[4].col = -1;
    off[5].row = 0; off[5].col = -1;
    off[6].row = -1; off[6].col = -1;
    off[7].row = -1; off[7].col = 0;
    off[8].row = -1; off[8].col = 1;
}
void print(ofstream& o,stack<ele>& mystack, int* counter)//use recursive to print out elements in a stack from bottom to top
{
    if (mystack.empty())
        return;
    ele x = mystack.top();
    mystack.pop();
    print(o,mystack,counter);
    cout << *counter << ":" << x.row << "," << x.col << endl;
    o << *counter << ":" << x.row << "," << x.col << endl;
    *counter = *counter + 1;
    mystack.push(x);
}
int main()
{
    //declare and initialize variables and read the file
    offsets off[9];
    stack<ele> mystack; //for memorizing the solution when there is one
    stack<ele> record; //for memorizing all the coordinates that have been explored
    int exitrow = 15; int exitcol = 16; //the exit defined in the assignment
    int dim = 17;
    int maze[dim][dim];
    int mark[dim][dim];
    int k=0,counter=0;
    ifstream file;
    ofstream output("output.txt");
    string oneline;
    string filename;

    //read user input
    cout <<"enter filename: ";
    cin >> filename;
    file.open(filename);
    if(!file)
    {
        cerr << "can not open the file";
        exit(1);
    }

    //for reading the txt file line by line and store numbers into a matrix
    while(getline(file,oneline))
    {
        for(int j=0;j<dim;j++)
        {
            maze[k][j] = oneline[j]-48;
            mark[k][j] = 0;
        }

        k++;
    }
    file.close();

    for(int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
    //initialize offset array and push the starting point into the stack
    inioff(off);
    mark[1][0] = 1;
    ele e;
    e.row = 1;
    e.col = 0;
    e.dir = 0;
    mystack.push(e);

    //trying to find a solution part
    while(!mystack.empty())
    {
        ele temp = mystack.top();
        mystack.pop();
        int i = temp.row; int j = temp.col; int d = temp.dir;
        /*The following if means a temporary direction 8 solution was found, and I have to add
        the coordinate into the record stack again, as it has been popped out and will not
        get into the loop.*/
        if(d == 10)
        {
            record.push(temp);
        }
        while(d<9)
        {
            int g = i+off[d].row; int h = j+off[d].col; //the new coordinate
            if(g==exitrow && h==exitcol) //if it is the exit, print the path
            {
                print(output,mystack,&counter);
                cout << counter << ":" << i << "," << j << endl;
                output << counter << ":" << i << "," << j << endl;
                counter++;
                cout << counter << ":" << exitrow << "," << exitcol << endl;
                output << counter << ":" << exitrow << "," << exitcol << endl;
                cout << "successfully escaped!!";
                output << "successfully escaped!!";
                output.close();
                exit(0);
            }
            /*if it is not the exit but may be a right one, then add it into the stack
            and update the current coordinate */
            if((g>=0)&&(h>=0)&&(!maze[g][h])&&(!mark[g][h]))
            {
                mark[g][h] = 1;
                temp.row = i; temp.col = j;
                if (d!=8)
                    temp.dir = d+1;
                else
                    temp.dir = d+2;
                mystack.push(temp);
                record.push(temp);
                i = g; j = h; d = 0;
            }
            else //if it is not an available coordinate (a wall or out of the bound)
            {
                if(d==8) //for adding the current coordinate into the stack even though it is a deadend
                {
                    mark[g][h] = 1;
                    temp.row = i; temp.col = j; temp.dir = d+1;
                    mystack.push(temp);
                    record.push(temp);
                }
                d++;
            }
         }
    }
    /* if no solution exists, print the record and show the following message*/
    print(output,record,&counter);
    cout << "Failed to escape." << endl;
    output << "Failed to escape." << endl;
    output.close();
}

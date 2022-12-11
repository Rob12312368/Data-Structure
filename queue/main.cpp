#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;
//circular queue implementation
class Queue{
    private:
        int *top;
        int *down;
        int len;
        int n;

    public:
        Queue()
        {
            len = 2;
            top = (int*)malloc(sizeof(int)*len);
            down = top;
            n = 0;
        }
        bool checkFull(){
            if((top == down) && (n>0)){
                cout << "FULL";
                return true;
            }
            return false;
        }
        bool checkEmpty(){
            if((top == down) && (n<=0)){
                cout << "EMPTY";
                return true;
            }
            return false;
        }
        void addq(int element)
        {
            if(!checkFull())
            {
                *top = element;
                n++;
                if(n==len)
                    top = top - (len-1);
                else
                    top++;
            }
        }
        void deleteq()
        {
            if(!checkEmpty())
            {
                cout << *down;
                n--;
                if(n==0)
                    down = down - (len-1);
                else
                    down++;
            }
        }
};

int main()
{
    Queue q;
    q.addq(10);
    q.addq(20);
    q.addq(30);
    q.deleteq();
    q.deleteq();
    q.deleteq();
    q.addq(10);
    q.addq(20);
    q.addq(30);
    q.deleteq();
    q.deleteq();
    q.deleteq();
    return 0;
}

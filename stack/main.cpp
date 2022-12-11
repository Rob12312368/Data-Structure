#include <iostream>
#include <cstdlib>
using namespace std;

class Stack{
    private:
        int *top;
        int n;
        int len;
    public:
        Stack()
        {
            len = 3;
            n = 0;
            top = (int*)malloc(sizeof(int)*(len+1));
        }
        bool checkFull(){
            if(n==len)
            {
                cout<<"FULL";
                return true;
            }
            else{
                return false;
            }
        }
        bool checkEmpty(){
            if(n==0)
            {
                cout<<"EMPTY";
                return true;
            }
            else{
                return false;
            }
        }
        void add(int element)
        {
            if(!checkFull())
            {
                *top = element;
                n++;
                top++;
            }
        }
        int pop()
        {
            if(!checkEmpty())
            {
                top--;
                n--;
                cout << *top;
            }
        }


};
int main()
{
    Stack stack;
    stack.add(5);
    stack.add(10);
    stack.add(15);
    stack.add(20);
    stack.pop();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.add(100);
    stack.add(200);
    stack.pop();
}

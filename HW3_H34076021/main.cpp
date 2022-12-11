#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <queue>
using namespace std;
typedef struct node
{
    int value;
    struct node* left;
    struct node* right;
}node;

node* top = NULL;
node* pre = NULL;
queue<node*> q;
ofstream outfile;
void BSTinsert(int num)
{
    if(top == NULL) //add first node into the tree
    {
        top = (node*)malloc(sizeof(node)); //set top node's value, left, and right pointer
        top->value = num;
        top->left = NULL;
        top->right = NULL;
        cout << "Number " << num << " is inserted."<< endl;
        outfile << "Number " << num << " is inserted."<< endl;
    }
    else{
        node* cur = top;
        while((cur!=NULL)) //loop to the child of leaf
        {
            pre = cur;
            if(num<cur->value) //if smaller than current go left
            {
                cur = cur->left;
            }
            else if(num>cur->value) //otherwise go right
            {
                cur = cur->right;
            }
            else //same number already in the tree
            {
                cout << "Error! Number " << num << " exists." << endl;
                outfile << "Error! Number " << num << " exists." << endl;
                return;
            }
        }
        //create a leaf node
        cur = (node*)malloc(sizeof(node));
        cur->value = num;
        cur->right = NULL;
        cur->left = NULL;
        //if new node bigger than its parent, it is a right child
        if(cur->value>pre->value)
        {
            pre->right = cur;
        }
        //otherwise a left child
        else if(cur->value < pre->value)
        {
            pre->left = cur;
        }
        cout << "Number " << num << " is inserted."<< endl;
        outfile << "Number " << num << " is inserted."<< endl;
    }
}

node* BSTsearch(int num)
{
    node* cur = top;
    while(cur!=NULL)
    {
        if(cur->value == num) //found the value
        {
            return cur;
        }
        pre = cur;
        if(num > cur->value)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }

    }
    return NULL; //not found
}
int lrchild(node* cur)//to see which kind of child cur is
{
    if(pre->right == cur)//cur is pre's right child
    {
        return 1;
    }
    else if(pre->left == cur)//cur is pre's left child
    {
        return 0;
    }
}
void BSTdelete(int num)
{
    node* found = BSTsearch(num);
    if(found == NULL)
    {
        cout << "Number " << num << " is not exist." << endl;
        outfile << "Number " << num << " is not exist." << endl;
        return;
    }
    else{
        if(found->right==NULL && found->left==NULL) //leaf
        {
            free(found);//delete the leaf node
            if(lrchild(found)==0)
            {
                pre->left = NULL;//concate its parent to null
            }
            else{
                pre->right = NULL;
            }
        }
        else if(found->right==NULL) //has left tree
        {
            if(lrchild(found)==0)
            {
                pre->left = found->left;//concate its parent to its left sub tree
                free(found);
            }
            else{
                pre->right = found->left;
                free(found);
            }
        }
        else if(found->left==NULL) //has right tree
        {
            if(lrchild(found)==0)
            {
                pre->left = found->right;//concate its parent to its right sub tree
                free(found);
            }
            else{
                pre->right = found->right;
                free(found);
            }
        }
        else //two sub tree
        {
            node* go = found->right; //move to right child
            node* goprev = found->right;
            while(go->left!=NULL)//move to the leftmost child
            {
                go = go->left;
            }
            if(go == found->right)//if no left child
            {
                found->value = go->value;
                found->right = go->right;
                free(go);
            }
            else{ //if there are at least one left child
                while(goprev->left->left!=NULL)//use goprev to concate deleted node's right sub tree
                {
                    goprev = goprev->left;
                }
                found->value = go->value;
                goprev->left = go->right;
                free(go);
            }
        }
        cout << "Number " << num << " is deleted." << endl;
        outfile << "Number " << num << " is deleted." << endl;
    }
    return;
}
void BSTprintpre(node* cur) //preorder
{
    if(cur == NULL)
    {
        return;
    }
    cout << cur->value << " ";
    outfile << cur->value << " ";
    BSTprintpre(cur->left);
    BSTprintpre(cur->right);
}
void BSTprintin(node* cur) //inorder
{
    if(cur == NULL)
    {
        return;
    }
    int a = cur->value;
    BSTprintin(cur->left);
    cout << cur->value << " ";
    outfile << cur->value << " ";
    BSTprintin(cur->right);
}
void BSTprintpost(node *cur) //post order
{
    if(cur == NULL)
    {
        return;
    }
    BSTprintpost(cur->left);
    BSTprintpost(cur->right);
    cout << cur->value << " ";
    outfile << cur->value << " ";
}
void BSTprintlevel(node* cur)
{
    q.push(cur); //push the top
    while(q.size()!=0)
    {
        int s = q.size();
        while(s>0)
        {
            node* temp = q.front();
            cout << temp->value << " ";
            outfile << temp->value << " ";
            if(temp->left!=NULL) //if the element in the front has left child, add to the queue
                q.push(temp->left);
            if(temp->right!=NULL)
                q.push(temp->right);
            q.pop();
            s--;
        }
    }
}
int main()
{
    string filename;
    cout << "Enter file name: ";
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    outfile.open("output.txt");
    outfile << "File name: " << filename << endl << endl;
    if(!infile.is_open())
    {
        cout << "open error";
        return 0;
    }

    string hint = "(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint 4 kinds of orders.\n(E)xit\n";
    string line;
    while(getline(infile,line))
    {
        cout << hint << endl;
        outfile << hint << endl;
        if(line.length()==1) //if it is the command
        {
            char c = toupper(line[0]); //turn into upper case
            char nodes[1000];
            if(c=='I') //insert
            {
                cout << "Insert:" << endl;
                outfile << "Insert:" << endl;
                getline(infile,line);
                strcpy(nodes,line.c_str());
                char *token;
                token = strtok(nodes," "); //tokenize the string
                while( token != NULL )
                {
                    if(strcmp(token,"-1")) //if it is not "-l"
                    {
                        BSTinsert(stoi(token));
                        //cout << token << endl;
                    }
                    token = strtok(NULL, " ");
                }
                cout << endl;
                outfile << endl;
            }
            else if(c=='D') //delete
            {
                cout << "Delete:" << endl;
                outfile << "Delete:" << endl;
                getline(infile,line);
                strcpy(nodes,line.c_str());
                char *token;
                token = strtok(nodes," ");
                while( token != NULL )
                {
                    if(strcmp(token,"-1"))
                    {
                        BSTdelete(stoi(token));
                        //cout << token << endl;
                    }
                    token = strtok(NULL, " ");
                }
                cout << endl;
                outfile << endl;
            }
            else if(c=='S') //search
            {
                cout << "Search:" << endl;
                outfile << "Search:" << endl;
                getline(infile,line);
                strcpy(nodes,line.c_str());
                char *token;
                token = strtok(nodes," ");
                while( token != NULL )
                {
                    if(strcmp(token,"-1"))
                    {
                        if(BSTsearch(stoi(token))!=NULL) //the node was found
                        {
                            cout << "Bingo! " << token << " is found." << endl;
                            outfile << "Bingo! " << token << " is found." << endl;
                        }
                        else{
                            cout << "Sorry! " << token << " is not found." << endl;
                            outfile << "Sorry! " << token << " is not found." << endl;
                        }
                        //cout << token << endl;
                    }
                    token = strtok(NULL, " ");
                }
                cout << endl;
                outfile << endl;
            }
            else if(c=='P') //print
            {
                cout << "Print:" << endl; outfile << "Print:" << endl;
                cout << "The tree in prefix order: "; outfile << "The tree in prefix order: ";
                BSTprintpre(top);
                cout << endl; outfile << endl;
                cout << "The tree in infix order: "; outfile << "The tree in infix order: ";
                BSTprintin(top);
                cout << endl; outfile << endl;
                cout << "The tree in post order: "; outfile << "The tree in post order: ";
                BSTprintpost(top);
                cout << endl; outfile << endl;
                cout << "The tree in level order: "; outfile << "The tree in level order: ";
                BSTprintlevel(top);
                cout << endl; outfile << endl;
                cout << endl; outfile << endl;
            }
            else if(c=='E') //exit
            {
                cout << "Exit" << endl;
                outfile << "Exit" << endl;
                return 0;
            }

        }
    }

    infile.close();
    outfile.close();
    return 0;



}

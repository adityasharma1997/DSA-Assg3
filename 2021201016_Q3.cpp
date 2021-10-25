#include<iostream>
#include<string.h>
using namespace std;


struct Trie{

    struct Trie *arr[26];
    bool isEnd;
    string value;

};

struct Trie *makenode(void){

    struct Trie *temp = new Trie;

    for(int i=0;i<26;i++){
        temp->arr[i]=NULL;

    }
    temp->isEnd=false;

    return temp;
}

void insert(struct Trie *root,string word){
    struct Trie *temp=root;
    for(char c:word){
        if(temp->arr[c-'a']==NULL){         //if that char is not present we will make a new node
            temp->arr[c-'a']=makenode();
        }
        temp=temp->arr[c-'a'];      //pointing to next char
    }
    temp->isEnd=true;
    temp->value=word;         //word is present and will be stored
}

void dfs(char **board,int i,int j,string *ans,Trie *root,bool **visited,int row,int col,int &start){
    if(i<0){
        return;
    }
    if(j<0){
        return;
    }
    if(i>=row){
        return;
    }
    if(j>=col){
        return;
    }
    if(visited[i][j]==true){
        return;
    }

    int index=board[i][j]-'a';
    if(root->arr[index]==NULL){
        return;
    }
    Trie *temp=root->arr[index];
    if(temp->isEnd==true){
        string s=temp->value;
        ans[start++]=s;
        temp->isEnd=false; //making sure we don't get duplicate words.
    }
    visited[i][j]=true;
    dfs(board,i-1,j,ans,temp,visited,row,col,start);
    dfs(board,i+1,j,ans,temp,visited,row,col,start);
    dfs(board,i,j-1,ans,temp,visited,row,col,start);
    dfs(board,i,j+1,ans,temp,visited,row,col,start);
    visited[i][j]=false;
    


}

int main(){


    struct Trie *root=makenode();
        int len;
        string words[len];
        cin>>len;
        
        for(int i=0;i<len;i++){
            cin>>words[i];
        }
        
        for(int i=0;i<len;i++){
            insert(root,words[i]);
        }

        int row;
        int col;
       cin>>row>>col;
       char **board;
       board = new char *[row];
       for(int i=0;i<row;i++){
           board[i]=new char[col];
       }
       char c;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                cin>>c;
                board[i][j]=c;
            }
        }
        bool **visited;
        visited=new bool*[row];
        for(int i=0;i<row;i++){
            visited[i]=new bool[col];
        }
         for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                visited[i][j]=false;
            }
        }
          string ans[len];
        int start=0;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                dfs(board,i,j,ans,root,visited,row,col,start);
            }
        }
       string temp;
       for(int i=0;i<start;i++){
           for(int j=i+1;j<start;j++){
               if(ans[i]>ans[j]){
                   temp=ans[i];
                   ans[i]=ans[j];
                   ans[j]=temp;
               }
           }
       }
        
        for(int i=0;i<start;i++){
            cout<<ans[i]<<" ";
            
        }
        return 0;
}
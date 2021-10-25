#include<bits/stdc++.h>

using namespace std;

void bfs(vector<vector<int>> &mat,vector<vector<int>> &visit){
    queue<pair<int,int>> q;
    int row=mat.size();
    int col=mat[0].size();
    q.push({1,0});
    visit[1][0]=1;
    while(!q.empty()){
        int first=q.front().first;
        int second=q.front().second;
        //moving up
        if(first-1 >=0 && visit[first-1][second]==-1){
            q.push({first-1,second});
            mat[first-1][second]=mat[first][second]+1;
            visit[first-1][second]=1;
        }
        //moving down
        if(first+1<row && visit[first+1][second]==-1){
            q.push({first+1,second});
            mat[first+1][second]=mat[first][second]+1;
            visit[first+1][second]=1;
        }
        //moving left
        if(second-1>=0 && visit[first][second-1]==-1){
            q.push({first,second-1});
            mat[first][second-1]=mat[first][second]+1;
            visit[first][second-1]=1;
        }
        //moving right
        if(second+1<col && visit[first][second+1]==-1){
            q.push({first,second+1});
            mat[first][second+1]=mat[first][second]+1;
            visit[first][second+1]=1;
        }

        q.pop();

        
    }
    return;
}

int main(){
    int n,m;
    cin>>n>>m;
    // char odr[7][8]={{'#','#','#','#','#','#','#','#'},{'.','.','.','.','.','.','.','#'},{'#','#','#','#','#','#','.','#'},{'#','.','#','.','#','.','.','#'},
    // {'#','R','#','.','.','#','.','#'},{'#','.','.','R','.','.','A','#'},{'#','#','#','#','#','#','#','#'}};

    char **grid;
    grid=new char *[n];
    for(int i=0;i<n;i++){
        grid[i]=new char[m];
    }

    char ch;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>ch;
            grid[i][j]=ch;
        }
    }


    vector<vector<int>> mat(n,vector<int>(m,0));
    vector<vector<int>> visit(n,vector<int>(m,-1));
    vector<pair<int,int>> riders;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]=='#'){
                mat[i][j]=-1;
                visit[i][j]=1;
            }else if(grid[i][j]=='R'){
                riders.push_back({i,j});
                
            }
        }    
    }
    bfs(mat,visit);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    int min=INT_MAX;
    for(int i=0;i<riders.size();i++){
        int x=riders[i].first;
        int y=riders[i].second;
        if(x==1 && y==0){
            cout<<"NO";
            return 0;
        }
        if(min>mat[x][y]){
            min=mat[x][y];
        }
    }

    int val=mat[n-2][m-2];
    if(val==-1){
        cout<<"NO";
    }else if(min<val && min!=0){
        cout<<"NO";
    }else{
        cout<<"YES"<<endl;
        cout<<val<<endl;
    }


    return 0;
}
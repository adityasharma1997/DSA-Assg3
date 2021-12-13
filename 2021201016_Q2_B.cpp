#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<pair<int,int>>> &adj,vector<pair<int,string>> &result,vector<int> &visit,int source,int dest,vector<string> &temp,int &count){


        visit[source]=1;
        if(source==dest){
            string abhi;
            for(int i=0;i<temp.size();i++){
               abhi+=temp[i];
            }
            result.push_back(make_pair(count,abhi));
           
            abhi.clear();
        }
        else{
            for(int i=0;i<adj[source].size();i++){
                int y=adj[source][i].first;
                if(visit[y]==0){
                    visit[y]=1;
                    int dist=adj[source][i].second;
                    temp.push_back(to_string(adj[source][i].first));
                    temp.push_back(" ");
                    count=count+dist;
                    dfs(adj,result,visit,y,dest,temp,count);
                    count=count-dist;
                    temp.pop_back();
                    temp.pop_back();
                }
            }
        }
        visit[source]=0;
        return;
}
int main(){
int n,e;
    cin>>n>>e;
    vector<vector<pair<int,int>>> adj(n);
    int a,b,c,k;

    for(int i=0;i<e;i++){
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
    }
    cin>>k;
    vector<pair<int,string>> result;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            string s=to_string(i);
            s=s+" ";
            vector<int> visit(5,0);
            vector<string> temp;
            temp.push_back(s);
            int count=0;
            dfs(adj,result,visit,i,j,temp,count);
        }
    }
    sort(result.begin(),result.end());
    cout<<endl;
    for(int i=0;i<k;i++){
        
            cout<<result[i].second;
            
        cout<<endl;
    }
    


}
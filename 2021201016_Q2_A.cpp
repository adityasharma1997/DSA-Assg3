#include<bits/stdc++.h>

using namespace std;
# define MAX 10000000


void solution(vector<vector<pair<int,int>>> &adj,vector<int> &parents,vector<bool> &visit,vector<int> &dist,int source,vector<vector<int>> &result){
    
    int vert=parents.size();
    for(int i=0;i<vert;i++){
        int first_time=-1;
        for(int j=0;j<vert;j++){
            if(visit[j]==false){
                if(first_time==-1 || dist[j]<dist[first_time]){             //choosing the vertex with min weight
                    first_time=j;
                }
            }
        }


        if(dist[first_time]!=MAX){
            visit[first_time]=true;
            for(int j=0;j<adj[first_time].size();j++){
                int second=adj[first_time][j].second;
                int pos=adj[first_time][j].first;
                if(dist[first_time] + second <=dist[pos]){
                    if(dist[first_time] + second == dist[pos]){
                    if(parents[pos]>first_time){
                        parents[pos]=first_time; //case when both have same weight but not sorted lexographical
                    }
                }else{
                    dist[pos] = dist[first_time] + second;
                    parents[pos]=first_time;      // case when it have lesser weight
                    }
                }
            }
        }else{
            break;
        }
    }

    for(int i=0;i<vert;i++){
        vector<int> temp;
            int j=i;
            while(j!=source){
                temp.push_back(j);
                j=parents[j];

            }
            temp.push_back(source);
            result.push_back(temp);
    }
   
}


int main(){
    int n,e;
    cin>>n>>e;
    vector<vector<pair<int,int>>> adj(n);
    int a,b,c;
    for(int i=0;i<e;i++){
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
    }
    vector<int> parents(n,-1);   //to store parents node
    vector<bool> visit(n,false);        //if visited
    vector<int> dist(n,MAX);        //updating the distance
    vector<vector<int>> result;     //store the result
    int source;
    cin>>source;
    dist[source]=0;
    parents[source]=0;
    solution(adj,parents,visit,dist,source,result);
    for(int i=0;i<result.size();i++){
        if(i!=source){
            cout<<"Path from"<<i<<": ";
            for(int j=0;j<result[i].size();j++){
                if(j==result[i].size()-1){
                    cout<<result[i][j];
                    break;
                }
                cout<<result[i][j]<<"->";
            }
            cout<<endl;
        }
    }
    return 0;
}
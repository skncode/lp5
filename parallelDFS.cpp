#include <iostream>
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;


const int MAX= 100000;
vector<int> graph[MAX];
bool visited[MAX];

void dfs(int node){
    stack<int> s;
    s.push(node);
    
    while(!s.empty()){
        int curr_node = s.top();
        
        if(!visited[curr_node]){
            visited[curr_node] = true;
            cout<<curr_node<<" ";
            s.pop();
        
            
            #pragma omp parallel for
            for(int i =0; i<graph[curr_node].size(); i++){
                int adj_node = graph[curr_node][i];
                if(!visited[adj_node]){
                    
                    s.push(adj_node);
                    // cout<<"pushed adj element :"<<adj_node<<endl;
                }
            }
        }
    }
}

int main(){
    cout<<"Enter no. of nodes, edges and starting node"<<endl;
    int n , e, start_node;
    cin>>n >>e >> start_node;
    cout<<"Enter pair of edges"<<endl;
    int u, v;
    
    for(int i=0; i< e; i++){
        cin>> u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        
    }
    
    #pragma omp parallel for
    for(int i=0 ;i< n;i++){
        visited[i] = false;
    }
    
    dfs(start_node);
    return 0;
}
/*
	Author: G.Kavitha
	Roll no. CS15B057
*/
/*
Input Format

The first line has the values of N and E which is followed by E lines, each specifying the cost between two stations. 

N E
station1 station2 C 
station1 station2 C 
station1 station2 C
..

Output:
Min cost to travel from station 1 to station N 
*/

#include<bits/stdc++.h>
using namespace std;
const int N=50005;
const int INF=1e9;

class Graph{
	//number of vertices
	int V;
	//adjacency list representation to hold the neighbour and the fare for reaching that neighbour
	vector<pair<int,int> > adj[N];
	//hold the cumulative cost for reaching vertex i from 1
	vector<int> mincost;
	bool vis[N];

	public:

	//Constructor
	Graph(int n){
		this->V=n;
		for(int i=0;i<n;i++){
			mincost.push_back(INF);
			vis[i]=false;
		}
	}

	//Function to add edge between u and v with fare(u,v) = c
	void AddEdge(int u,int v,int c){
		adj[u].push_back(make_pair(v,c));
		adj[v].push_back(make_pair(u,c));
	}

	//Function that finds the min_cost from vertex 1 to vertex u 
    void FindMinCost(int s){
		priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > pq;
		mincost[s]=0;
		pq.push(make_pair(0,s));
		while(!pq.empty()){
			pair<int,int> top=pq.top();
			pq.pop();
			int u=top.second;
			int cum_cost=top.first;
			for(int i=0;i<adj[u].size();i++){
				int v=adj[u][i].first;
				int fare=adj[u][i].second;
				int temp=mincost[u]+max(0,fare-mincost[u]);
				if(mincost[v]>temp){
					mincost[v]=temp;
					pq.push(make_pair(temp,v));
				}
			}
		}
	}

	//Function to return the MinCost
	int getMinCost(int u){
		return mincost[u];
	}
};

//Main
int main(){
	int n,m;
	cin>>n>>m;
	
	Graph G(n);
	
	//Reading in the edges
	for(int i=0;i<m;i++){
		int u,v,c;
		cin>>u>>v>>c;
		u--;
		v--;
		G.AddEdge(u,v,c);
	}

	//Finding the min_cost path from 1 to n
	G.FindMinCost(0);
	int ans=G.getMinCost(n-1);

	if(ans==INF) 
		cout<<"NO PATH EXISTS\n";
	else 
		cout<<ans<<"\n";

	return 0;
}
/*
	Author: G.Kavitha
	Roll No. CS15B057
*/

// Program to solve the puzzle.

/*
The puzzle is represented as a string of length N with 0-9 being the only valid characters.
Each digit represents a unique color
The player starts at the leftmost tile and has to reach the rightmost tile.
The player can only move towards adjacent tiles, or choose to teleport to any tile with the same color. 

Output:
solves for the minimum number of jumps needed to solve this puzzle.
*/


#include<bits/stdc++.h>
using namespace std;

const int N=1005;
const int INF=100005;

// Class for the graph
class Graph{
	//Number of vertices
	int V;
	//Storing the graph using adjancency list format
	vector<int> adj[N];
	//Storing the bfs distance from source to each vertex
	int bfs_dist[N];

	public:
	Graph(int n){
		this->V=n;
	}
	void add_edge(int u,int v);
	void add_edges(vector<int> pos[10]);
	void init_bfs();
	void bfs(int s);
	int get_dist(int n);
};

//Adding an edge between node u and node v
void Graph::add_edge(int u,int v){
	adj[u].push_back(v);
	adj[v].push_back(u);
}

//Function to add the edges between the adjacent tiles
//and between the tiles having the same color
void Graph::add_edges(vector<int> pos[10]){
	//Creating edges for adjacent positions
	for(int i=0;i<V-1;i++)
		add_edge(i,i+1);
	
	for(int i=0;i<10;i++){
		int n=pos[i].size();
		for(int j=0;j<n-1;j++){
			for(int k=j+1;k<n;k++){
				add_edge(pos[i][j],pos[i][k]);
			}
		}
	}
	
}

//Initialise bfs_distances
void Graph::init_bfs(){
	for(int i=0;i<V;i++)
		bfs_dist[i]=INF;
}

void Graph::bfs(int s){
	init_bfs();
	//queue is used here to perform the bfs
	queue<int> q;

	//Setting bfs_dist of source s as 0
	q.push(s);
	bfs_dist[s]=0;

	while(!q.empty()){
		int u=q.front();
		q.pop();

		for(int i=0;i<adj[u].size();i++){
			int v=adj[u][i];
			if(bfs_dist[v]==INF){//Not visited so far
				bfs_dist[v]=1+bfs_dist[u];
				q.push(v);
			}
		}
	}
}

int Graph::get_dist(int n){
	return bfs_dist[n];
}

int main(){
	//arrray to hold the final string
	int arr[N];	
	for(int i=0;i<N;i++) 
		arr[i]=-1;

	//vector to hold the positions of each color
	vector<int> pos[10];
	
	//Reading in the input
	for(int i=0;i<10;i++){
		int a;
		cin>>a;
		while(a!=-1){
			pos[i].push_back(a);
			arr[a]=i;
			cin>>a;
		}
	}
	
	int n;
	//Dispaying the string found
	for(n=0;arr[n]!=-1;n++){
		cout<<arr[n];
	}
	cout<<"\n";

	//Create the graph and add all its edges to it
	Graph G(n);
	G.add_edges(pos);

	//Perform a breadth first search on the graph and display the answer
	G.bfs(0);
	cout<<G.get_dist(n-1)<<"\n";

	return 0;
}
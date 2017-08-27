/*
	Author: G.Kavitha
	Roll No. CS15B057
*/

// Program for playing the minesweeper game.
/*
Input Format
	square_grid_dimension no._of_mines(M)
	M values indicating locations of mines
	loc 1
	loc 2
	loc 3
	..
	..

Output is "Won" if all the cells except the mines have been revealed.
		   "Lost" if a mine has been revealed. - A number "x" where x
		   is the number of cells that have been revealed up to this point which are not mines.
*/ 

#include<bits/stdc++.h>
using namespace std;

class MineSweeper{
	//size of grid and the number of mines and number of cells revealed
	int n,m,found;

	//the position of the mines
	vector<bool> mines;
	
	vector<bool> revealed;//whether cell has been revealed
	vector<int> neigh;//the number of mines near it

	//function to find the 8 (or lesser) adjacent cells near it
	vector<int> adjNeigh(int loc){
		vector<int> res;
		int a=loc/n;
		int b=loc%n;
		if(b-1>=0) res.push_back(loc-1);
		if(b+1<n) res.push_back(loc+1);
		if(a-1>=0) res.push_back(loc-n);
		if(a+1<n) res.push_back(loc+n);
		if(a-1>=0&&b-1>=0) res.push_back(loc-n-1);
		if(a-1>=0&&b+1<n) res.push_back(loc-n+1);
		if(a+1<n&&b-1>=0) res.push_back(loc+n-1);
		if(a+1<n&&b+1<n) res.push_back(loc+n+1);
		return res;
	}

	//function to populate the neighbours of the mine, by adding 1 to the neighbours' neigh[]
	void populateNeigh(int loc){
		vector<int> adj;
		adj=adjNeigh(loc);
		for(int i=0;i<adj.size();i++){
			neigh[adj[i]]++;
		}
	}

	public:

		//Constructor
		MineSweeper(int N,int M){
			n=N;
			m=M;
			found=0;
			mines.assign(n*n,false);
			revealed.assign(n*n,false);
			neigh.assign(n*n,0);
		}

		//function to return the number of cells revealed so far
		int getFound(){
			return found;
		}

		//function to insert the mine, and populate the neighbours
		void insertMine(int loc){
			mines[loc]=true;
			populateNeigh(loc);
		}
	
		//function to check if the given cell is a mine
		bool isMine(int a,int b){
			int loc=a*n+b;
			if(mines[loc]) 
				return true;
			return false;
		}

		//function to reveal the cell (a,b)
		void reveal(int a,int b){
			int loc=a*n+b;
			
			//if already revealed or (a,b) is a mine
			if(revealed[loc]||mines[loc]) 
				return;
			
			//increment tjhe number of cells revealed
			found++;
			revealed[loc]=true;
			
			//if (a,b) has mines in its neighbouring cells
			if(neigh[loc]>0) 
				return;
			
			//traverse its neighbours and reveal their cells
			vector<int> adj=adjNeigh(loc);
			for(int i=0;i<adj.size();i++)
				reveal(adj[i]/n,adj[i]%n);
		}
};

int main(){
	int N,M;
	int a,b;
	cin>>N>>M;
	MineSweeper ms(N,M);
	for(int i=0;i<M;i++){
		cin>>a;
		ms.insertMine(a);
	}
	bool game_over=false;
	while(cin>>a>>b){
		if(game_over)
			continue;
		if(ms.isMine(a,b)){
			cout<<"Lost\n";
			game_over=true;
			continue;
		}
		ms.reveal(a,b);
		int x=ms.getFound();
		
		if(M==N*N-x){
			cout<<"Won\n";
			game_over=true;
			continue;
		}

		cout<<x<<"\n";
	}
	return 0;
}
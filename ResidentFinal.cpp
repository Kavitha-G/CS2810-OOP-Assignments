/*
	Author : G..Kavitha
	Roll No.: CS15B057
*/

// Program for finding out how many of your immediate friends are uninfected,
// and whether you are the Final uninfected Resident of the hotel.
/*
Input Format:

N (number of residents)
G (max generations for any strain)
S (number of strain types)
M (minimum number of strains for total infection)
< NxN adjacency matrix >
< S indices for the initially infected residents >

Output:
<# of immediate friends safe>
<GAME OVER | RESIDENT FINAL | *empty*>

*/
#include<bits/stdc++.h>
using namespace std;
# define l int
# define vi vector<l>
vector<vi> adj;
vector<set<l> > inf;
l n,g,s,m;

int main(){
	cin>>n>>g>>s>>m;
	for(l i=0;i<n;i++){
		vi v;
		set<l> s;
		adj.push_back(v);
		inf.push_back(s);
	}
	l a;
	for(l i=0;i<n;i++){
		for(l j=0;j<n;j++){
			cin>>a;
			if(a==1)
				adj[i].push_back(j);
		}
	}
	queue<pair<l,l> > q;
	for(l i=0;i<s;i++){
		cin>>a;
		inf[a].insert(i);
		q.push(make_pair(a,i));
	}
	q.push(make_pair(-1,-1));
	while(q.size()>1&&g){
		pair<l,l> p=q.front();
		q.pop();
		l b=p.first;
		l i=p.second;
		if(b==-1){
			g--;
			q.push(make_pair(-1,-1));
			continue;
		}
		for(l j=0;j<adj[b].size();j++){
			l v=adj[b][j];
			if(inf[v].find(i)!=inf[v].end())
				continue;
			inf[v].insert(i);
			q.push(make_pair(v,i));
		}
	}
	l rem=0;
	for(l i=1;i<n;i++){
//		cout<<i<<' '<<inf[i].size()<<"\n";
		if(inf[i].size()<m) rem++;
	}
	l ans=0;
	for(l i=0;i<adj[0].size();i++){
		l v=adj[0][i];
		if(inf[v].size()<m) {
			ans++;
		}
	}
	cout<<ans<<"\n";
	if(inf[0].size()>=m) cout<<"GAME OVER\n";
	else if(rem==0)  cout<<"RESIDENT FINAL\n";	
	return 0;
}
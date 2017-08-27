/* 
	Author: G.Kavitha
	Roll No. CS15B057
*/

/*
Input Format

# of all adjacent landing points
...
...
# of Breather points
...
...
Krishh'sSpeed Kaya'sSpeed
Krishh'sStartingPoint Kaya'sStartingPoint

Note: First entry of the first adjacent landing pt. pair indicates peak of the mountain.

Given these inputs(total landing points, breather points, speeds and initial position),
output is whether there is a possibility for them to meet at some mountain.
    Yes and print the time taken (in minutes) to meet from the start.
    No and print time taken(in minutes) just after they go past each other.
*/

#include<bits/stdc++.h>
using namespace std;

//class for landing point
class LandingPoint{
	public:
	int id;
	LandingPoint* parent;
	vector<LandingPoint*> adj;
	bool breather;
	int visit_time;
	bool actual_visit;
	LandingPoint(){
		parent=NULL;
		this->breather=false;
		this->actual_visit=false;
	}
	void insertAdj(LandingPoint*);
};

//insert adjacent node
void LandingPoint::insertAdj(LandingPoint* a){
	(this->adj).push_back(a);
}

//id to landingpoint*
map<int,LandingPoint*> id2point;

//class for mountain
class Mountain{
	public:
	LandingPoint* root;
	vector<LandingPoint*> path;
	void setRoot(LandingPoint*);
	void setParents(LandingPoint*,int);
};

//set the root
void Mountain::setRoot(LandingPoint* r){
	this->root=r;
}

//get the parents by dfs
void Mountain::setParents(LandingPoint* l,int p){
	int n=(l->adj).size();
	int ID=(l->id);
	LandingPoint* v=NULL;
	for(int i=0;i<n;i++){
		v=(l->adj)[i];
		if(v->id==p) 
			continue;
		v->parent=l;
		this->setParents(v,ID);
	}
}

//class for superhero
class SuperHero{
	int speed;
	int cur_time;
	int cur_pos;
	int dir;
	LandingPoint* curr_lpt;
	LandingPoint* prev_lpt;
	LandingPoint* initial_lpt;
	Mountain* m;
	public:
	SuperHero(Mountain* M,int a,int v){
		m=M;
		initial_lpt=id2point[a];
		speed=v;
		cur_time=0;
		curr_lpt=initial_lpt;
		prev_lpt=NULL;
	}
	void goToPeak();
	LandingPoint* lca(SuperHero a);
	void findPath(SuperHero a);
	void Init(int a){
		dir=a;
		if(dir==1) cur_pos=0;
		else cur_pos=(m->path).size()-1;
	}
	void next(){
		if(curr_lpt->breather&&curr_lpt!=prev_lpt){
			prev_lpt=curr_lpt;
			return;
		}
		prev_lpt=curr_lpt;
		cur_pos+=dir*speed;
		if(cur_pos<0) curr_lpt=NULL;
		else if(cur_pos>=(m->path).size()) curr_lpt=NULL;
		else curr_lpt=(m->path)[cur_pos];
	}
	int getpos(){
		return cur_pos;
	}
};

//go to root and flip the visited variable
void SuperHero::goToPeak(){
	LandingPoint* cur=initial_lpt;
	cur->actual_visit=!(cur->actual_visit);
	while(cur!=m->root){
		cur=cur->parent;
		cur->actual_visit=!(cur->actual_visit);
	}
}

//find the lca 
LandingPoint* SuperHero::lca(SuperHero a){
	LandingPoint* cur=this->initial_lpt;
	while(cur->actual_visit==false){
		cur=cur->parent;
	}
	return cur;
}

//find the path
void SuperHero::findPath(SuperHero a){
	a.goToPeak();
	LandingPoint* l=lca(a);
	a.goToPeak();
	LandingPoint* cur=this->initial_lpt;
	while(cur!=l){
		(m->path).push_back(cur);
		cur=cur->parent;
	}
	(m->path).push_back(l);
	stack<LandingPoint*> st;
	cur=a.initial_lpt;
	while(cur!=l){
		st.push(cur);
		cur=cur->parent;
	}
	while(!st.empty()){
		(m->path).push_back(st.top());
		st.pop();
	}
}

//main
int main(){
	int n;
	int a,b;
	cin>>n;
	Mountain* M=new Mountain;
	for(int i=0;i<n;i++){
		cin>>a>>b;
		LandingPoint *A,*B;
		if(id2point.find(a)==id2point.end()){
			A=new LandingPoint;
			id2point[a]=A;
			A->id=a;
		}
		else
			A=id2point[a];
		if(id2point.find(b)==id2point.end()){
			B=new LandingPoint;
			id2point[b]=B;
			B->id=b;
		}
		else
			B=id2point[b];
		if(i==0) 
			M->setRoot(A);
		A->insertAdj(B);
		B->insertAdj(A);
	}

	M->setParents(M->root,-1);
	
	cin>>b;
	while(b--){
		cin>>a;
		LandingPoint* l=id2point[a];
		(l->breather)=true;
	}
	
	int v1,v2;
	
	cin>>v1>>v2;
	cin>>a>>b;
	
	SuperHero Krish(M,a,v1),Kaya(M,b,v2);
	
	Krish.findPath(Kaya);

//	cerr<<(M->path).size()<<"\n";

	Krish.Init(1);
	Kaya.Init(-1);

	int t=0;
	while(Krish.getpos()<Kaya.getpos()){
		Krish.next();
		Kaya.next();
		t++;
	}

	if(Krish.getpos()==Kaya.getpos()) cout<<"Yes\n";
	else cout<<"No\n";

	cout<<t<<'\n';
	return 0;
}

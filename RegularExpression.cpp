/*
	Author: G.Kavitha
	Roll No. CS15B057
*/

// Program that takes in input as a regex.

/*
	Given a input pattern, "matched" is printed if it matches the regex, 
	else "unmatched" is printed. 
	Regular expression will only contain numbers, | (OR), * (Star), + (Plus), e (Epsilon) and small parenthesis.
	A NFA (Non Deterministic Finite Automata) is built for matching.

	Input Format
		<Regex>
		<String1>
		<String2>
		...
*/

#include<iostream>
#include<vector>
#include<string>
#include<bits/stdc++.h>
using namespace std;

//class for state
class state{
	public:
	//holds the transions corresponding to each alphabet
	vector<state*> delta[10]; 
	void transition(state* s,int c);
};
class nfa{
	public:
	//initial state,final states, and set of all states
	state* q0;
	vector<state*> F;
	vector<state*> Q;

	void copy(nfa n);
	void build(string s);
	void create(char c);
	nfa Union(nfa b);
	nfa Concat(nfa b);
	nfa Plus();
	nfa Kleene();
	bool match(string s);
	
};
//Checks if the character is an operand or operator
//Returns true if it is an operator
bool isOp(char c){
	if(c=='e') return false;
	if(c<='9'&&c>='1') return false;
	return true;
}

void nfa::copy(nfa n){
	map<state*,state*> cp;
	this->Q.clear();
	this->F.clear();
	for(int i=0;i<n.Q.size();i++){
		state* s=new state;
		cp[(n.Q)[i]]=s;
		(this->Q).push_back(s);
	}
	for(int i=0;i<n.Q.size();i++){
		state* x=(n.Q)[i];
		for(int a=0;a<10;a++){
			for(int j=0;j<(x->delta)[a].size();j++){
				cp[x]->transition(cp[(x->delta)[a][j]],a);
			}
		}
	}
	this->q0=cp[n.q0];
	for(int i=0;i<(n.F).size();i++)
		(this->F).push_back(cp[(n.F)[i]]);
}

//Function to build the nfa from the postfix regex s
void nfa::build(string s){
	stack<nfa> S;
	int n=s.length();
	for(int i=0;i<n;i++){
		if(isOp(s[i])){
				if(s[i]!='*'&&s[i]!='+'){
					nfa n1=S.top();
					S.pop();
					nfa n2=S.top();
					S.pop();
					nfa n3;
					if(s[i]=='|')
						n3=n1.Union(n2);
					else
						n3=n2.Concat(n1);
					S.push(n3);
				}
				else{
					nfa n1=S.top();
					S.pop();
					nfa n3;
					if(s[i]=='+') 
						n3=n1.Plus();
					else 
						n3=n1.Kleene();
					S.push(n3);
				}
		}
		else{
			nfa n1;
			n1.create(s[i]);
			S.push(n1);
		}			
	}
	(*this)= S.top();
	int tot=(this->Q).size();
	for(int i=0;i<tot;i++){
		(this->Q)[i]->transition((this->Q)[i],0);
	}
	return;
}

//helper function to convert the alphabet to integer
int num(char c){
	if(c=='e') return 0;
	return c-'0';
}

//Function to insert a transition delta(this,n)=s2
void state::transition(state* s2,int n){
	(this->delta)[n].push_back(s2);
}	

//Function to create the nfa given a single alphabet or e
void nfa::create(char c){
	state* s1=new state;
	state* s2=new state;
	int n=num(c);
	s1->transition(s2,n);
	this->q0=s1;
	(this->F).push_back(s2);
	(this->Q).push_back(s1);
	(this->Q).push_back(s2);
}

//Function to return the union of this with b
nfa nfa::Union(nfa b){
	nfa c;
	state* s1=new state;
	state* s2=new state;
	s1->transition(this->q0,0);
	s1->transition(b.q0,0);
	int n=(this->F).size();
	for(int i=0;i<n;i++)
		((this->F)[i])->transition(s2,0);
	n=(b.F).size();
	for(int i=0;i<n;i++)
		((b.F)[i])->transition(s2,0);
	c.q0=s1;
	(c.F).push_back(s2);
	(c.Q).push_back(s1);
	(c.Q).push_back(s2);
	for(int i=0;i<(*this).Q.size();i++) 
		(c.Q).push_back(((*this).Q)[i]);
	for(int i=0;i<b.Q.size();i++)
		(c.Q).push_back((b.Q)[i]);
	nfa r;
	r.copy(c);
	return r;
}

//Function to return the concatenation of this with b
nfa nfa::Concat(nfa b){
	nfa c;
	state* s2=new state;
	int n=(this->F).size();
	for(int i=0;i<n;i++)
		((this->F)[i])->transition(b.q0,0);
	n=(b.F).size();
	if(n!=1){
		for(int i=0;i<n;i++)
			((b.F)[i])->transition(s2,0);
	}
	c.q0=(this->q0);
	if(n!=1) {
		(c.F).push_back(s2);
		(c.Q).push_back(s2);
	}
	else{
		(c.F).push_back((b.F)[0]);
	}
	for(int i=0;i<(*this).Q.size();i++) 
		(c.Q).push_back(((*this).Q)[i]);
	for(int i=0;i<b.Q.size();i++)
		(c.Q).push_back((b.Q)[i]);
	nfa r;
	r.copy(c);
	return r;
}

//Function to return (this)+
nfa nfa::Plus(){
	nfa c,t,r;
	c.copy(*this);
	t.copy(c);
	c=c.Concat(t);
	r.copy(c);
	t.copy(c);
	(c.F)[0]->transition(t.q0,0);
	(c.F)[0]=(t.F)[0];
	for(int i=0;i<t.Q.size();i++)
		c.Q.push_back((t.Q)[i]);
		
	state* f=new state;
	nfa p;
	int tot=248;
	vector<state*> fin;
	fin.push_back((c.F)[0]);
	for(int i=0;i<tot;i++){
		p.copy(r);
		(c.F)[0]->transition(p.q0,0);
		(c.F)[0]=(p.F)[0];
		for(int i=0;i<p.Q.size();i++)
			c.Q.push_back((p.Q)[i]);
		fin.push_back((c.F)[0]);
	}
	tot=249;
	for(int i=0;i<tot;i++){
		fin[i]->transition(f,0);
	}
	
	(c.F).clear();
	(c.F).push_back(f);
	(c.Q).push_back(f);
	return c;
}

//Function to return (this)*
nfa nfa::Kleene(){
	nfa c;
	state* s1=new state;
	state* s2=new state;
	state* s3=new state;
	state* s4=new state;

	s1->transition(s2,0);
	s3->transition(s1,0);
	s3->transition(s4,0);
	s1->transition(s4,0);

	s2->transition(this->q0,0);
	int n=(this->F).size();
	for(int i=0;i<n;i++)
		((this->F)[i])->transition(s3,0);

	c.q0=s1;
	(c.F).push_back(s4);
	(c.Q).push_back(s1);
	(c.Q).push_back(s2);
	(c.Q).push_back(s3);
	(c.Q).push_back(s4);
	for(int i=0;i<(*this).Q.size();i++) 
		(c.Q).push_back(((*this).Q)[i]);
	return c;
}

//Function which returns true if string s is accepted by nfa, 
//false otherwise
bool nfa::match(string s){
	set<state*> curr,Prev;
	int n=s.length();
	curr.clear();
	curr.insert(this->q0);
	
	//Eps-closure
	do{
		Prev=curr;
		for(set<state*>::iterator it=Prev.begin();it!=Prev.end();++it){
			int tot=((*it)->delta)[0].size();
			for(int i=0;i<tot;i++)
				curr.insert(((*it)->delta)[0][i]);
		}
	}while(Prev.size()!=curr.size());
		
	Prev=curr;
	for(int i=0;i<n;i++){
		Prev=curr;
		curr.clear();
		int a=num(s[i]);
		for(set<state*>::iterator it=Prev.begin();it!=Prev.end();++it){
			state* S=(*it);
			int tot=(S->delta)[a].size();
			for(int j=0;j<tot;j++)
				curr.insert((S->delta)[a][j]);			
		}

		//Eps-closure
		do{
			Prev=curr;
			for(set<state*>::iterator it=Prev.begin();it!=Prev.end();++it){
				int tot=((*it)->delta)[0].size();
				for(int i=0;i<tot;i++)
					curr.insert(((*it)->delta)[0][i]);
			}
		}while(Prev.size()!=curr.size());
	}
	sort((this->F).begin(),(this->F).end());
	int j=0;
	int tot=(this->F).size();
	
	for(set<state*>::iterator it=Prev.begin();it!=Prev.end();++it){
		while(j<tot&&((this->F)[j]<(*it))) j++;
		if(j==tot) return false;
		if((this->F)[j]==*it) 
			return true;
	}
	return false;
}

//returns the priority of the operator
int priority(char c){
	switch(c){
		case ')': return 6;
		case '*': return 5;
		case '+': return 4;
		case '.': return 3;
		case '|': return 2;
		case '(': return 1;
		default: return 0;
	}
}

//Function to convert infix regex to postfix regex
string postfix(string s){
	stack<char> S;
	string res=s+s+s;
	int j=0;
	int n=s.length();
	s=s+s+s;
	for(int i=0;i<n-1;i++){
		bool yes=false;
		if(!isOp(res[i])){
			if(res[i+1]=='(') yes=true;
			if(!isOp(res[i+1])) yes=true;
		}
		if(res[i]==')'||res[i]=='*'||res[i]=='+'){
			if(!isOp(res[i+1])) yes=true;
			if(res[i+1]=='(') yes=true;
		}
		s[j++]=res[i];
		if(yes) s[j++]='.';
	}
	s[j++]=res[n-1];
	n=j;
	s=s.substr(0,j);
	j=0;
	for(int i=0;i<n;i++){
		if(!isOp(s[i])){
			res[j++]=s[i];
			continue;
		}
		if(s[i]==')'){
			while(!S.empty()&&S.top()!='('){
				char c=S.top();
				S.pop();
				res[j++]=c;
			}
			S.pop();
			continue;
		}
		if(s[i]=='('){
			S.push(s[i]);
			continue;
		}
		int cur_pr=priority(s[i]);
		int top_pr=-1;
		if(!S.empty()) top_pr=priority(S.top());
		if(cur_pr>top_pr){
			S.push(s[i]);
			continue;
		}
		while(top_pr>=cur_pr){
			char c=S.top();
			S.pop();
			res[j++]=c;
			if(S.empty()) top_pr=-1;
			else top_pr=priority(S.top());
		}
		S.push(s[i]);
	}
	while(!S.empty()){
		res[j++]=S.top();
		S.pop();
	}
	return res.substr(0,j);
}

//Main function
int main(){
	nfa N;
	string regex;
	cin>>regex;
	regex=postfix(regex);
// 	cout<<regex<<"\n";
	N.build(regex);
	string s;
	while(cin>>s){
		if(N.match(s)) cout<<"matched\n";
		else cout<<"not matched\n";
	}
	return 0;
}
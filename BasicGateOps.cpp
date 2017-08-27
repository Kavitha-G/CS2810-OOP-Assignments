/*
	Author: G.Kavitha
	Roll No CS15B057
*/

// Performs AND, OR, XOR, NAND operations. 
// Provides the output of a network of gates.

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <bits/stdc++.h>
using namespace std;

//Class Basic gate - base class
class BasicGate{
	
	public:
	//Holds the inputs to gate as vector of BasicGate* 
	vector<BasicGate* > inputs;

	//virtual keyword used to enable overloading	
	virtual int output()=0;

	//Function for Operator Overloading
	void operator+=(BasicGate* b){
		(this->inputs).push_back(b);
		return;
	}
		
};

//Gates AND,OR,NAND,NOR,XOR,EMIT are publicly inherited from base class BasicGate

class AND:public BasicGate{
	//variable to hold the result/output of the basic gate
	int res;
	public:
	//function to compute and return the result/output of the basic gate
	int output();

};

int AND::output(){
	res=1;
	for(int i=0;i<inputs.size();i++){
		res=res&((inputs[i])->output());
	}
	return res;
}

class OR:public BasicGate{
	//variable to hold the result/output of the basic gate
	int res;

	public:
	//function to compute and return the result/output of the basic gate
	int output();

};

int OR::output(){
	res=0;
	for(int i=0;i<inputs.size();i++){
		res=res|((inputs[i])->output());
	}
	return res;
}

class XOR:public BasicGate{
	//variable to hold the result/output of the basic gate
	int res;

	public:
	//function to compute and return the result/output of the basic gate
	int output();

};

int XOR::output(){
	res=0;
	for(int i=0;i<inputs.size();i++){
		res=res^((inputs[i])->output());
	}
	return res;
}

class NAND:public BasicGate{
	//variable to hold the result/output of the basic gate
	int res;

	public:
	//function to compute and return the result/output of the basic gate
	int output();

};

int NAND::output(){
	res=1;
	for(int i=0;i<inputs.size();i++){
		res=(res&((inputs[i])->output()));
	}
	return (1^res);
}

class NOR:public BasicGate{
	//variable to hold the result/output of the basic gate
	int res;

	public:
	//function to compute and return the result/output of the basic gate
	int output();

};

int NOR::output(){
	res=0;
	for(int i=0;i<inputs.size();i++){
		res=(res|((inputs[i])->output()));
	}
	return (1^res);
}

class EMIT:public BasicGate{
	//variable to hold the result/output of the basic gate
	int res;

	public:
	//Constructor
	EMIT(int a){
		res=a;
	}
	//function to compute and return the result/output of the basic gate
	int output();
	
};

int EMIT::output(){
	return res;
}

//stl map that holds the mappings from the gate id to the pointer to the gate
map<string,BasicGate*> gate;

//returns the type of gate (AND,OR,XOR,NAND..) by taking in as argument the id of the gate
string getGateType(string s){
	string res="";
	int i=0;

	while(s[i]<='Z'&&s[i]>='A'){
		i++;
	}
	
	res=s.substr(0,i);
	return res;
}
	
//Gets the pointer to the basic gate if it has already been declared else creates a new gate
BasicGate* getBasicGate(string S){
	
	//Getting the type of the gate
	string s=getGateType(S);

	if(gate.find(S)==gate.end()){//create new gate if gate didn't exist
		if(s=="AND") {
			AND* a=new AND;
			gate[S]=a;
		}
		else if(s=="OR"){
			OR* a=new OR;
			gate[S]=a;
		}
		else if(s=="XOR"){
			XOR* a=new XOR;
			gate[S]=a;
		}	
		else if(s=="NAND"){
			NAND* a=new NAND;
			gate[S]=a;
		}	
		else if(s=="NOR"){
			NOR* a=new NOR;
			gate[S]=a;
		}	
		else if(s=="EMIT"){
			int c;
			if(S=="EMIT0") c=0;
			else c=1;			
			EMIT* a=new EMIT(c);
			gate[S]=a;
		}	
	}

	//Returning the pointer to the BasicGate
	return gate[S];
}

//Function to parse the input and read the input and return a pointer to the final output gate
BasicGate* read(){
	string s,s1,s2;
	string a,b,A;

	cin>>s>>A;
	s=s+A;//ID of the output gate

	while(cin>>s1>>a>>s2>>b){
		s1=s1+a;//Input Gate ID
		s2=s2+b;//Output Gate ID
		
		//Getting the BasicGate pointers
		BasicGate* b1=getBasicGate(s1);
		BasicGate* b2=getBasicGate(s2);
	
		//adding to the vector of inputs
		(*b2)+=b1;
	}

	//Getting the output gate pointer
	BasicGate* B=getBasicGate(s);

	return B;
}

//Main function
int main() {
	BasicGate *last_gate = read();
	cout << last_gate->output() <<endl;
	return 0;
}

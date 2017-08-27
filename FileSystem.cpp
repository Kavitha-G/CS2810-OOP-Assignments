/***********************************************
****** DRIVER PROGRAM FOR OOAIA EXAM 1 *********
********* TO IMPLEMENT FILE SYSTEM *************
*** COMPILE USING: g++ driver.cpp -std=c++14 ***
************************************************/

// Program that mimics the working of Linux terminal.
/*
    mkdir - Creates an empty directory. Takes one argument: name of the directory.
    touch - Creates an empty file. Takes one argument: name of the file
    cd - Change to specified directory. Takes one argument: name of directory.
    pwd - Prints the path to current working directory. No arguments.
    rm - Removes a folder or a file. Takes one argument: name of file or folder.
    ls - Prints the contents of the current directory (first all the folders in alphabetical order,
    	 followed by all the files in alphabetical order). No arguments

    Input Format
		cmd1 arg1
		cmd2 arg2
		... 
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

class Folder{
	string name;
	Folder* par;
	map<string,Folder*> subdir;
	set<string> files;
	public:
		Folder(string s,Folder* p){
			name=s;
			par=p;
		}
		void mkdir(string s);
		void touch(string s);
		void cd(string s,vector<Folder*>&env);
		void pwd(vector<Folder*> env);
		void rm(string s);
		void ls();
};

void Folder::mkdir(string s){
	if(subdir.find(s)!=subdir.end()){
		cout<<"Exists\n";
		return;
	}
	Folder* f=new Folder(s,this);
	subdir[s]=f;
}

void Folder::touch(string s){
	if(files.find(s)!=files.end()){
		cout<<"Exists\n";
		return;
	}
	files.insert(s);
}

void Folder::cd(string s,vector<Folder*>&env){
	if(s==".."){
		if(!env.empty()) 
			env.pop_back();
		return;
	}
	if(subdir.find(s)==subdir.end()){
		cout<<"Does not exist\n";
		return;
	}
	env.push_back(subdir[s]);
}

void Folder::pwd(vector<Folder*> env){
	for(int i=0;i<env.size();i++){
		cout<<"/"<<env[i]->name;
	}
	if(env.size()==0) cout<<"/";
	cout<<"\n";
}

void Folder::rm(string s){
	if(subdir.find(s)!=subdir.end()){
		map<string,Folder*>::iterator it=subdir.find(s);
		subdir.erase(it);
	}
	else if(files.find(s)!=files.end()){
		set<string>::iterator it=files.find(s);
		files.erase(it);
	}
	else{
		cout<<"Does not exist\n";
	}
}

void Folder::ls(){
	for(map<string,Folder*>::iterator it=subdir.begin();it!=subdir.end();++it){
		cout<<it->first<<" ";
	}
	for(set<string>::iterator it=files.begin();it!=files.end();++it)
		cout<<(*it)<<" ";
	cout<<"\n";
}

int main() {

	//Create a home folder called '/' which does not have 
	//a parent directory. 
	Folder home("/",NULL);
	Folder* cur=NULL;

	//Store the path to the current directory 
	vector<Folder*> env;

	//Map for commands to use switch-case
	string str_arr[]={"mkdir","touch","cd","pwd","rm","ls"};
	map<string,int> cmd_map;
	int i=0;
	for(auto &val:str_arr) cmd_map[val]=i++;
	
	//Taking commands as input
	string inp;
	while(getline(cin,inp)) {
		stringstream ss(inp);
		string cmd, arg;
		ss>>cmd>>arg;
		if(env.empty()) cur=&home;
		else cur=env.back();
		switch(cmd_map[cmd]){
			//mkdir
			case 0:
				(*cur).mkdir(arg);
				break;

			//touch
			case 1: 
				(*cur).touch(arg);
				break;

			//cd
			case 2: 
				(*cur).cd(arg,env);
				break;
				
			//pwd
			case 3: 
				(*cur).pwd(env);
				break;

			//rm
			case 4: 
				(*cur).rm(arg);
				break;

			//ls
			case 5: 
				(*cur).ls();
				break;
			
			//Other
			default: cout<<"Invalid Command"<<endl; break;
		}
	}
	return 0;
}
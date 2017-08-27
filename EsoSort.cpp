/*
	Author: G.Kavitha
	Roll No. CS15B057
*/

// Program which performs eso sort on the input.

/*
Input Format

position1 salary_per_hour1
position2 salary_per_hour2
...
employee_id1 name1 position1
employee_id2 name2 position2
...
sorting_algorithm
employee_id1 week_num1 hours_per_week1
employee_id2 week_num2 hours_per_week2
... 

*/
#include <iostream>
#include <map>
#include <string>
#include <bits/stdc++.h>
using namespace std;

//STL map from position of type string to salary_per_hour
map<string,int> pos_to_sal;

//STL map from position of type string to rank as per hierarchy
map<string,int> pos_to_rank;

//Class Employee
class Employee{
	public:	
	string pos;
	int sal_per_hr;
	string empID;
	string name;
	int salary;
	
	//Operator Overloading for operator <
	//Returns boolean value	
	bool operator<(const Employee& e){
		if(this->salary!=e.salary) //then return as per salary
			return ((this->salary)>e.salary);

		if(pos_to_rank[this->pos]!=pos_to_rank[e.pos]) //then return as per rank or position
			return (pos_to_rank[this->pos]<pos_to_rank[e.pos]);

		if(this->name!=e.name)//Return as per the alphabetical ordering of names
			return ((this->name)<(e.name));

		return ((this->empID)<e.empID);//Return as per employee ID
	}
	
	//Operator Overloading for operator >
	//Returns boolean value
	bool operator>(const Employee& e){
		return (!((*this)<e));
	}
	
	//Function declarations
	void insert(string id,string Name,string Pos);
	void update_sal(int hrs);
};

//Function to insert the fields for an object of employee class
void Employee::insert(string id,string Name,string Pos){
	this->empID=id;
	this->name=Name;
	this->pos=Pos;
	this->sal_per_hr=pos_to_sal[Pos];
	this->salary=0;
}

//Function to update the value of the salary based on the number of hrs worked per week
void Employee::update_sal(int hrs){
	(this->salary)+=hrs*(this->sal_per_hr);
}

//Function to merge two vectors e1 and e2 and store in e
template<typename T>
int merge(vector<T> &e,vector<T> &e1,vector<T> &e2){
	int i=0,j=0,k=0;//to iterate over e1,e2,e
	int ans=0;//stores the number of inversions

	int n1=e1.size();
	int n2=e2.size();

	for(;i<n1&&j<n2;){
		if(e1[i]<e2[j]) 
			e[k++]=e1[i++];
		else {
			ans+=(n1-i);
			e[k++]=e2[j++];
		}
	}

	while(i<n1){ 
		e[k++]=e1[i++];
	}

	while(j<n2){
		e[k++]=e2[j++];
	}

	return ans;
}

//Function to perform merge sort and return the number of swaps
template<typename T>
int merge_sort(vector<T> &e){
	int ans=0;
	int n=e.size();

	if(n==0||n==1) 
		return 0;

	vector<T> e1,e2;
	int i;
	for(i=0;i<((n+1)/2);i++) 
		e1.push_back(e[i]);

	for(;i<n;i++)
		e2.push_back(e[i]);

	ans+=merge_sort(e1);
	ans+=merge_sort(e2);

	ans+=merge(e,e1,e2);

	return ans;
}

//Function to perform insertion sort and return the number of swaps
template<typename T>
int insertion_sort(vector<T> &e){
	int ans=0;
	int n=e.size();

	for(int i=1;i<n;i++){
		int j=i;
		T temp=e[i];
		while(j>0&&temp<e[j-1]){
			e[j]=e[j-1];
			j--;
			ans++;
		}
		e[j]=temp;
	}

	return ans;
}	
	
//Function to perform selection sort and return the number of swaps
template<typename T>
int selection_sort(vector<T> &e){
	int ans=0;
	int n=e.size();

	for(int i=0;i<n;i++){
		T mini=e[i];
		int idx=i;
		for(int j=i+1;j<n;j++){
			if(e[j]<mini){
				mini=e[j];
				idx=j;
			}
		}
		if(idx!=i){
			ans++;
			swap(e[i],e[idx]);
		}
	}

	return ans;
}

//Function to print the employee ids of the employees
template<typename T>
void print(vector<T> e){	
	int len=e.size();

	for(int i=0;i<len;i++)
		cout<<e[i].empID<<" ";
	cout<<"\n";
}

//Function to convert a given string to its integer equivalent
int toNum(string s){
	int n=s.length();
	int ans=0;

	for(int i=0;i<n;i++){
		ans=ans*10;
		ans+=(s[i]-'0');
	}

	return ans;
}

//Function to check if the given string is a number
bool isNum(string s){
	if(s[0]<='9'&&s[0]>='0') 
		return true;
	else
		return false;
}

//Function to read in the input
pair<vector<Employee>,string> read(){
	pair<vector<Employee>,string> res;
	map<string,int> ID_to_loc;

	string pos,sal,temp; //Variables 
	int counter=1;
	string s;//Variable to hold the entire line

	while(getline(cin,s)){
		stringstream ss(s);

		temp="";
		ss>>pos>>sal>>temp;

		if(temp==""){//Only 2 strings as required
			pos_to_sal[pos]=toNum(sal);
			pos_to_rank[pos]=counter;
			counter++;
		}
		else 
			break;
	}

	string name,ID;
	ID=pos;
	name=sal;
	pos=temp;

	Employee E;
	E.insert(ID,name,pos);//Update the fields	
	ID_to_loc[ID]=(res.first).size();//store the location of that ID in the vector
	(res.first).push_back(E);//Insert into the vector<Employee>

	while(getline(cin,s)){
		stringstream ss(s);

		pos="";
		ss>>ID>>name>>pos;

		if(pos!=""){//3 strings as required
			Employee E;
			E.insert(ID,name,pos);//Update the fields			 
			ID_to_loc[ID]=(res.first).size();//store the location of that ID in the vector
			(res.first).push_back(E);//Insert into the vector<Employee>
		}
		else 
			break;
	}

	res.second=ID;//Storing the sort type into res.second
	
	string week_no;
	int hrs;

	while(cin>>ID>>week_no>>hrs){//Till end of input
		int loc=ID_to_loc[ID];//find location in vector	
		(res.first)[loc].update_sal(hrs);//Update total salary
	}

	return res;
}

int main() {
	pair<vector<Employee>, string> records = read();
	int (*sort)(vector<Employee>&); //Function pointer
	
	if(records.second=="Merge")
		sort = merge_sort;
	else if(records.second=="Insertion")
		sort = insertion_sort;
	else 
		sort = selection_sort;
	
	cout<<sort(records.first)<<endl;
	print(records.first);

	return 0;
}
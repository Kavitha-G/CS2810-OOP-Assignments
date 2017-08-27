/*
	Author: G.Kavitha
	Roll No. CS15B057
*/

// Program for implementing BigInteger Arithmetic.
/*

    Arithmetic Operators:
        Addition '+' (add)
        Subtraction '-' (sub)
        Mutliplication '*' (mul)
        Division '/' (div)
        Modulus '\%' (mod)
        Factorial '!' (fac)
        Power '\^' (pow)
    Comparison Operators:
        Equals '==' (eq)
        Not Equals '!=' (neq)
        Greater than Equals '>=' (geq)
        Less than Equals '<=' (leq)

     Input Format
		operator-keyword1 number1 number2
		operator-keyword2 number1 number2
		operator-keyword3 number1 number2 
		...
*/	

#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

//Class BigInt
class BigInt{
	//vector of integers to hold the big integer
	vector<int> a;
	//if sign=1, then the number is +ve, else if sign is -1, number is -ve
	int sign;
	
	public:

	//constructor
	BigInt(){
		sign=1;
	}

	//constructor to initialise the vector a
	BigInt(string s){
		int i=0;
		if(s=="") {
			sign=1;
			return;
		}
		if(s[0]=='-') {
			sign=-1; 
			i++;
		}
		else 
			sign=1;

		for(;i<s.length();i++)
			a.push_back(s[i]-'0');
	}

	//Function to return the length i.e, the number of digits in the BigInt
	int len(){
		return a.size();
	}

	//Function to get the sign of the BigInt
	int getsign(){
		return sign;
	}

	//Function to set the sign of the BigInt
	void setsign(int i){
		sign=i;
	}

	//Function to return the vector of digits of the BigInt
	vector<int> getNum(){
		return a;
	}

	//Function to store the vector of digits of the BigInt
	void storeNum(vector<int> v){
		a=v;
	}
	
	//Function to append n zeros
	void appendzr(int n){
		for(int i=0;i<n;i++)
			a.push_back(0);
	}

	//Function to append number n to the vector of digits
	void appendNum(int n){
		a.push_back(n);
	}

	//Function to correct to remove the leading zeros
	void correct(){
		int j=0;
		while(j<a.size()&&a[j]==0) 
			j++;
		
		int n=a.size();
		if(j==n) {
			sign=1;
			j--;
		}
		for(int i=0;i<n-j;i++)
			a[i]=a[i+j];
		while(j--){
			a.pop_back();
		}
	}

	//Function declarations of the overloaded operators
	BigInt operator +(BigInt b);
	BigInt operator -(BigInt b);
	BigInt operator *(BigInt b);
	BigInt operator /(BigInt b);
	BigInt operator %(BigInt b);
	BigInt operator !();
	BigInt operator ^(BigInt b);
	bool operator ==(BigInt b);
	bool operator >=(BigInt b);
	bool operator !=(BigInt b);
	bool operator <=(BigInt b);
	
	//Helper Function to multiply the BigInt by a single number from 0 to 9
	BigInt mult(int i);

	//Function to print the Big Integer
	void printInt(){
		if(sign==-1) cout<<"-";
		for(int i=0;i<a.size();i++)
			cout<<a[i];
		cout<<"\n";
	}
};

//Function which overloads operator + for adding 2 BigInts
BigInt BigInt::operator +(BigInt B){
	bool flip=false;
	
	if(sign*B.getsign()>0){//both positive or both negative
		
		if(sign<0){
			flip=true;
		}
		
		vector<int> res,b;
		b=B.getNum();

		int n=max(a.size(),b.size())+1;
		res.assign(n,0);

		if(b.size()>a.size()) 
			swap(a,b);//a holds larger number now

		int n1=a.size(),n2=b.size();

		int c=0;//holds carry
	
		for(int i=0;i<n2;i++){
			int r=c+a[n1-i-1]+b[n2-i-1];
			res[--n]=r%10;
			c=r/10;
		}

		for(int i=n2;i<n1;i++){
			int r=c+a[n1-i-1];
			res[--n]=r%10;
			c=r/10;
		}

		res[--n]=c;
		
		BigInt C;
		C.storeNum(res);
		C.correct();

		C.setsign(1);
		if(flip)
			C.setsign(-1);
		
		return C;
	}

	if(sign<0){
		sign=1;
		return B-(*this);
	}

	B.setsign(1);
	return (*this)-B;
}

//Function which overloads operator - for suntracting 2 BigInts
BigInt BigInt::operator -(BigInt B){
	bool flip=false;
	
	if(sign*B.getsign()>0){//both positive or both negative
		if(!((*this)>=B)) 
			flip=true; 
		
		vector<int> res,b;
		b=B.getNum();

		if(sign>0){
			if(!((*this)>=B)) swap(a,b);
		}
		else{
			if(!((*this)<=B)) swap(a,b);
		}

		int n=max(a.size(),b.size())+1;
		res.assign(n,0);

		int n1=a.size(),n2=b.size();
	
		for(int i=0;i<n2;i++){
			int r=a[n1-i-1]-b[n2-i-1];
			if(r<0) {
				r+=10;
				int j=n1-i-2;
				while(j>=0&&a[j]==0){
					a[j]=9;
					j--;
				}
				a[j]--;
			}
			res[--n]=r;
		}

		for(int i=n2;i<n1;i++){
			int r=a[n1-i-1];
			res[--n]=r;
		}
		
		BigInt C;
		C.storeNum(res);
		C.correct();

		C.setsign(1);
		if(flip)
			C.setsign(-1);
		
		return C;
	}

	if(sign<0){
		sign=1;
		BigInt C=B+(*this);
		C.setsign(-1);
		return C;
	}

	B.setsign(1);
	return (*this)+B;
}

//Function which overloads *
BigInt BigInt::operator *(BigInt B){
	bool flip=false,fl=false;
	if(sign*(B.getsign())<0) flip=true;
	vector<int> b=B.getNum();
	BigInt res("0");
	if(b.size()>a.size()){
		fl=true; 
		swap(a,b);
	}
	int n=b.size();
	for(int i=0;i<n;i++){
		BigInt C=(*this).mult(b[n-i-1]);
		C.appendzr(i);
		res=res+C;
	}
	if(flip) res.setsign(-1);
	else res.setsign(1);
	if(fl) swap(a,b);
	return res;
}

//Function which overloads /
BigInt BigInt::operator /(BigInt B){
	bool flip=false;
	bool flB=false;
	BigInt one("1");
	if(sign*(B.getsign())<0) flip=true;
	if(B.getsign()<0) {
		flB=true;
		B.setsign(1);
	}
	BigInt res("");
	BigInt temp("");
	for(int i=0;i<a.size();i++){
		temp.appendNum(a[i]);
		temp.correct();
		for(int j=1;j<=10;j++){
			if(!(B.mult(j)<=temp)) {
				res.appendNum(j-1);
				temp=temp-B.mult(j-1);
				break;
			}
		}
	}
	res.correct();
	if(flB) B.setsign(-1);
	if(flip) {
		res.setsign(-1);
		res.correct();
		if((res*B)!=(*this)) res=res-one;
	}
	else res.setsign(1);
	return res;
}

//Function to multiply a BigInt with a digit
BigInt BigInt::mult(int n){
	if(n==0) return BigInt("0");
	vector<int> res;
	int k=this->len();
	res.assign(k+1,0);
	int j=k+1;
	int c=0;
	for(int i=0;i<k;i++){
		int r=c+a[k-i-1]*n;
		res[--j]=r%10;
		c=r/10;
	}
	res[--j]=c;
	if(res[0]==0){
		for(int i=0;i<k;i++)
			res[i]=res[i+1];
		res.pop_back();
	}
	BigInt C;
	C.storeNum(res);
	C.setsign(this->sign);
	
	return C;
}

//Function which overloads % for 2 BigInts
BigInt BigInt::operator %(BigInt B){
	BigInt C=(*this)/B;
	C=B*C;
	C=(*this)-C;
	C.correct();
	if(B.getsign()==-1){
		if(C.getsign()==1){
			vector<int> c=C.getNum();
			if(c[0]!=0)
				C=C-B;
		}
	}
	else{
		if(C.getsign()==-1)
			C=C+B;
	}
	return C;
}

//Function which overloads ! for BigInt
BigInt BigInt::operator !(){
	BigInt res("1");
	BigInt cmp("1");
	while((*this)>=cmp){
		res=res*(*this);
		(*this)=(*this)-cmp;
	}
	return res;
}

//Function which overloads ^ for BigInt
BigInt BigInt::operator ^(BigInt B){
	BigInt x("1");
	BigInt cmp("1");
	BigInt div("2");
	while(B>=cmp){
		if(B%div==cmp)
			x=(*this)*x;
		(*this)=(*this)*(*this);
		B=B/div;
	}
	return x;
}

//Function which overloads == to compare 2 BigInts
bool BigInt::operator ==(BigInt B){
	if(sign*(B.getsign())<0){
		return false;
	}
	vector<int> b=B.getNum();
	
	if(b.size()!=a.size())
		return false;

	for(int i=0;i<b.size();i++){
		if(a[i]!=b[i]) return false;
	}

	return true;
}

//Function which overloads !=
bool BigInt::operator !=(BigInt B){
	return (!((*this)==B));
}

//Function which overloads >=
bool BigInt::operator >=(BigInt B){
	if((*this)==B) return true;
	if(sign*(B.getsign())<0){
		if(sign<0) return false;
		else return true;
	}
	if(sign<0){
		if(a.size()<B.len()) return true;
		else if(a.size()>B.len()) return false;
		vector<int> b=B.getNum();
		for(int i=0;i<a.size();i++){
			if(a[i]>b[i]) return false;
			else if(a[i]<b[i]) return true;
		}
	}
	
	if(a.size()<B.len()) return false;
	else if(a.size()>B.len()) return true;
	vector<int> b=B.getNum();
	for(int i=0;i<a.size();i++){
		if(a[i]>b[i]) return true;
		else if(a[i]<b[i]) return false;
	}
	return true;
}

//Function to overload <=
bool BigInt::operator <=(BigInt B){
	if((*this)==B) return true;
	if((*this)>=B) return false;
	return true;
}

//function to compute the result i.e. s1 (op) s2 and return it
BigInt compute(string op,string s1,string s2){
	BigInt b1(s1);
	BigInt b2(s2);
	BigInt tr("1");
	BigInt fal("0");
	
	if(op=="add") return b1+b2;
	else if(op=="sub") return b1-b2;
	else if(op=="mul") return b1*b2;
	else if(op=="div") return b1/b2;
	else if(op=="mod") return b1%b2;
	else if(op=="fac") return !b1 ;
	else if(op=="pow") return b1^b2;
	else if(op=="neq"){ 
		if(b1!=b2) return tr;
		else return fal;
	}
	else if(op=="geq"){
		if(b1>=b2) return tr;
		else return fal;
	}
	else if(op=="leq"){
		if(b1<=b2) return tr;
		else return fal;
	}
	else if(op=="eq"){
		if(b1==b2) return tr;
		else return fal;
	}
	return fal;
}

int main(){
	string op,s1,s2;

	//Read in data, compute result and print it;
	while(cin>>op>>s1){
		if(op!="fac") cin>>s2;
		BigInt res=compute(op,s1,s2);
		res.printInt();
	}

	return 0;
}
/*
	Author: G.Kavitha
	Roll No. CS15B057
*/

// Program that performs convolution.

/*
Dimension of original matrix
Followed by elements
Dimension of kernel
Followed by elements 

This constrained version of convolution applies convolution operation a number of times until convolution
is not possible on resultant matrix with respect to the same kernel.

The output is the final resultant matrix. 
*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T> class Matrix;

//class for the MatOp
template <typename T>
class MatOp {
	public: 
		virtual void operator()(Matrix<T> &m) = 0;
};

//class for the Matrix
template <typename T>
class Matrix {
	private:
		vector<T> data;
		int r,c;
	public:
		void apply(MatOp<T>& op) { op(*this); }
		
		//constructor
		Matrix<T>(int m,int n){
			r=m;
			c=n;
			data.assign(m*n,0);
		}

		Matrix<T>(){}

		//Function to copy the contents of an object
		void copy(Matrix<T> m){
			this->r=m.rows();
			this->c=m.cols();
			this->data.clear();
			(this->data).assign(r*c,0);
			for(int i=0;i<r*c;i++){
				(this->data)[i]=m(i/c,i%c);
			}
		}

		int rows() { return r; }
		int cols() { return c; }
		
		//operator overloading for ()
		int operator()(int m,int n)const {
			return data[m*c+n];
		}
		int & operator()(int m,int n){
			return data[m*c+n];
		}

		//function to print a matrix
		void print(){
			for(int i=0;i<r;i++){
				for(int j=0;j<c;j++){
					cout<<data[i*c+j]<<" ";
				}
				cout<<"\n";
			}
	}
};

//class for clamping to 0
template<typename T>
class Clamp:public MatOp<T>{
	void operator()(Matrix<T>& orig){
		int r=orig.rows();
		int c=orig.cols();
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				if(orig(i,j)<0)
					orig(i,j) = 0;
			}
		}
	}
};
Clamp<int> clamp;//functor

//class for convolution
template<typename T>
class Conv:public MatOp<T>{
	//the kernel to be used
	Matrix<int> kernel;
	
	public:
	//setting the kernel
	void setKernel(Matrix<T> k){
		kernel.copy(k);
	}

	void operator()(Matrix<T>& orig){
		int m=orig.rows();
		int n=orig.cols();
		int p=kernel.rows();
		int q=kernel.cols();
		
		Matrix<int> res(m-p+1,n-q+1);
		for(int i=0;i<m-p+1;i++){
			for(int j=0;j<n-q+1;j++){
				int ans=0;
				for(int u=i,x=0;u<i+p;u++,x++){
					for(int v=j,y=0;v<j+q;v++,y++){
						ans+=orig(u,v)*kernel(x,y);
					}
				}
				res(i,j)=ans;
			}
		}
		orig.copy(res);
	}
};
Conv<int> conv;//fuunctor

//class for the iterative convolution with clamping
template<typename T>
class ItConv:public MatOp<T>{
	//kernel to be used for the convolution
	Matrix<int> kernel;

	public:
	//setting the kernel
	void setKernel(Matrix<T> k){
		kernel.copy(k);
	}

	void operator()(Matrix<T>& orig){
		int m=orig.rows();
		int n=orig.cols();
		int p=kernel.rows();
		int q=kernel.cols();
		
		while(p<=m&&q<=n){
			orig.apply(conv);
			orig.apply(clamp);
			m=orig.rows();
			n=orig.cols();
		//	orig.print();
		}
		orig.apply(clamp);
	}
};
ItConv<int> itconv;//functor

int main() {
	    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int m,n;
	cin>>m>>n;
	
	//read in data
	Matrix<int> orig(m,n);
	int a;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin>>a;
			orig(i,j)=a;
		}
	}

	int p,q;
	cin>>p>>q;

	Matrix<int> kernel(p,q);
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			cin>>a;
			kernel(i,j)=a;
		}
	}

	//set the kernel
	itconv.setKernel(kernel);
	conv.setKernel(kernel);

	//Apply the iterative convolution and print the result
	orig.apply(itconv);
	orig.print();

	return 0;
}
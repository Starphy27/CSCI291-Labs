#include<iostream>
#include<iomanip>
#include <cstdlib> 
using namespace std;


void print_real( float number, int fieldspace, int precision);

int main(void){
float  a, b;
cout<<" Please input two real numbers";
cin>>a>>b;	

print_real(a,7,3);
print_real(b,7,3);
// call the function update_scale with ONLY the actual parameters a  and b
print_real(a,7,3);
print_real(b,7,3);
	
}

/* complete the body of the function */
void print_real( float number, int fieldspace, int precision){

}

// add the function defintion (header+body) of the template function update_scale

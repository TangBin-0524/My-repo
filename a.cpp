#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0;char ch;
	while((ch=getchar())<'0'||ch>'9');
	while(isdigit(ch))
		x=x*10+(ch^48),ch=getchar();
	return x;
}
void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
typedef long long ll;
#define fi first
#define se second
const int INF=INT_MAX;
inline void ckmax(int &x,int y){x=x<y?y:x;}
int main()
{
	cout<<"Hello World"<<endl;
	return 0;
}


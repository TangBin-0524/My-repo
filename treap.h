#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
int rt,num,n;
struct treap_node
{
	int ls,rs,key,pri,cnt,sze;
#define lc(x) t[x].ls
#define rc(x) t[x].rs
#define v(x) t[x].key
#define p(x) t[x].pri
#define c(x) t[x].cnt
#define s(x) t[x].sze
}t[N];
inline void upt(const int &k){s(k)=s(lc(k))+s(rc(k))+c(k);}
inline void Zig(int &k)//右旋
{
	int y=lc(k);
	lc(k)=rc(y); rc(y)=k;
	s(y)=s(k); upt(k); k=y;
}
inline void Zag(int &k)//左旋
{
	int y=rc(k);
	rc(k)=lc(y); lc(y)=k;
	s(y)=s(k); upt(k); k=y;
}
inline void Insert(int &k,const int &key)
{
	if(!k){
		k=++num;
		v(k)=key;p(k)=rand();
		c(k)=s(k)=1;lc(k)=rc(k)=0;
		return;
	}
	else ++s(k);
	if(v(k)==key)++c(k);
	else if(key<v(k))
	{
		Insert(lc(k),key);
		if(p(lc(k))<p(k))Zig(k);
	}
	else{
		Insert(rc(k),key);
		if(p(rc(k))<p(k))Zag(k);
	}
}
inline void Delete(int &k,const int &key)
{
	if(v(k)==key)
	{
		if(c(k)>1)--c(k),--s(k);
		else if(!lc(k)||!rc(k))k=lc(k)+rc(k);
		else if(p(lc(k))<p(rc(k)))Zig(k),Delete(k,key);
		else Zag(k),Delete(k,key);
		return;
	}
	--s(k);
	if(key<v(k))Delete(lc(k),key);
	else Delete(rc(k),key);
	return;
}
inline int QueryPre(const int &key)
{
	int x=rt,res=INT_MIN;
	while(x)
	{
		if(v(x)<=key)res=v(x),x=rc(x);
		else x=lc(x);
	}
	return res;
}
inline int QueryNxt(const int &key)
{
	int x=rt,res=INT_MAX;
	while(x)
	{
		if(v(x)>=key)res=v(x),x=lc(x);
		else x=rc(x);
	}
	return res;
}
inline int QueryKth(int k)
{
	int x=rt;
	while(x){
		if(s(lc(x))<k&&s(lc(x))+c(x)>=k)return v(x);
		if(s(lc(x))>=k)x=lc(x);
		else k-=s(lc(x))+c(x),x=rc(x);
	}
	return 0;
}
inline int QueryRank(const int &key)
{
	int x=rt,res=1;
	while(x){
		//cout<<':'<<x<<lc(x)<<rc(x)<<v(x)<<endl;
		if(key==v(x))return res+s(lc(x));
		if(key<v(x))x=lc(x);
		else res+=s(lc(x))+c(x),x=rc(x);
	}
	return res;
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5,M=355;
int n,m;
struct mat
{
	int v[2][2];
	mat(bool isE=false)
	{
		v[0][0]=v[1][1]=isE;
		v[1][0]=v[0][1]=0;
	}
	mat operator*(const mat& rhs)const
	{
		mat ans;
		ans.v[0][0]=(v[0][0]*rhs.v[0][0]+v[0][1]*rhs.v[1][0]);
		ans.v[1][0]=(v[1][0]*rhs.v[0][0]+v[1][1]*rhs.v[1][0]);
		ans.v[0][1]=(v[0][0]*rhs.v[0][1]+v[0][1]*rhs.v[1][1]);
		ans.v[1][1]=(v[1][0]*rhs.v[0][1]+v[1][1]*rhs.v[1][1]);
		return ans;
	}
	friend istream& operator>>(istream& in,mat& x)
	{
		return in>>x.v[0][0]>>x.v[0][1]>>x.v[1][0]>>x.v[1][1];
	}
	friend ostream& operator<<(ostream& out,const mat& x)
	{
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				out<<x.v[i][j]<<' ';
		return out;
	}
};
struct node
{
	int op;
	mat l,r;
	friend istream& operator>>(istream& in,node& nd)
	{
		in>>nd.op;
		if(nd.op==1)in>>nd.l,nd.r=mat(true);
		else if(nd.op==2)in>>nd.r,nd.l=mat(true);
		else nd.l=nd.r=mat(true);
		return in;
	}
}op[N];
int len;
struct block
{
	int l,r,neg,sz;
	mat suml[M],sumr[M];
	void build(int idx)
	{
		l=idx*len,r=min(l+len-1,n-1),neg=sz=0;
		deque<int>st;
		for(int i=l;i<=r;i++)
		{
			if(op[i].op!=3)st.push_back(i);
			else if(st.empty())neg++;
			else st.pop_back();
		}
		sz=st.size();
		suml[0]=sumr[0]=mat(true);
		for(int i=0;i<st.size();i++)
		{
			suml[i+1]=op[st[i]].l*suml[i];
			sumr[i+1]=sumr[i]*op[st[i]].r;
		}
	}
}blk[M];
mat query(int l,int r)
{
	int blkl=l/len,blkr=r/len;
	if(blkl==blkr)
	{
		deque<int>st;
		for(int i=l;i<=r;i++)
		{
			if(op[i].op!=3)st.push_back(i);
			else if(!st.empty())st.pop_back();
		}
		mat L=mat(true),R=mat(true);
		for(int i=0;i<st.size();i++)
		{
			L=op[st[i]].l*L;
			R=R*op[st[i]].r;
		}
		return L*R;
	}
	else{
		int neg=0;
		deque<int>st;
		for(int i=blk[blkr].l;i<=r;i++)
		{
			if(op[i].op!=3)st.push_back(i);
			else if(st.empty())neg++;
			else st.pop_back();
		}
		mat L=mat(true),R=mat(true);
		for(int i=0;i<st.size();i++)
		{
			L=op[st[i]].l*L;
			R=R*op[st[i]].r;
		}
		for(int i=blkr-1;i>=blkl+1;i--)
		{
			if(blk[i].sz<=neg)neg-=blk[i].sz+blk[i].neg;
			else{
				L=L*blk[i].suml[blk[i].sz-neg];
				R=blk[i].sumr[blk[i].sz-neg]*R;
				neg=blk[i].neg;
			}
		}
		st.clear();
		for(int i=l;i<=blk[blkl].r;i++)
		{
			if(op[i].op!=3)st.push_back(i);
			else if(!st.empty())st.pop_back();
		}
		while(neg&&!st.empty())neg--,st.pop_back();
		for(int i=st.size()-1;i>=0;i--)
		{
			L=L*op[st[i]].l;
			R=op[st[i]].r*R;
		}
		return L*R;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	len=max(1,(int)sqrt(n));
	for(int i=0;i<n;i++)cin>>op[i];
	for(int i=0;i<n;i+=len)blk[i/len].build(i/len);
	while(m--)
	{
		int v,idx,l,r;
		cin>>v;
		if(v==1)
		{
			cin>>idx;cin>>op[--idx];
			blk[idx/len].build(idx/len);
		}
		else{
			cin>>l>>r;
			cout<<query(--l,--r)<<endl;
		}
	}
	return 0;
}


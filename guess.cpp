#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<fstream>
#define IL inline
#define re register
#define LL long long
using namespace std;

bool in(char ch)
{
	if(ch<='z'&&ch>='a') return 1;
	if(ch<='Z'&&ch>='A') return 1;
	return 0;
}

bool exclude(string a,string b,string c)//a中没有b中的任何字母,a中没有c中不同位置的任何字母 
{
	for(unsigned i=0;i<a.size();i++)
	for(unsigned j=0;j<b.size();j++)
	if(a[i]==b[j]){
		//cout<<"当前单词为"<<a<<"，重复字母为"<<a[i]<<endl;
		return 0;//猜错的字母不可能有 
	}
	
	map<char,int>lib;
	for(unsigned int i=0;i<c.size();i++) if(c[i]!='*') lib[c[i]]++;
	for(unsigned int i=0;i<a.size();i++) if(c[i]=='*'&&lib.find(a[i])!=lib.end()) return 0;
	
	return 1;
}

vector<string>word;

string t;
int main()
{
	ifstream fin("word.txt");
	ofstream fout("word.his",ios::app);
	ifstream his("word.his");
	
	if(his.peek()==EOF) cout<<"没有查询历史\n";
	else while(his.peek()!=EOF) his>>t,word.push_back(t);
	
	cout<<"读取数据库...\n";
	while(fin.peek()!=EOF){
		string w;
		getline(fin,t);
		int post=0;
		while(!in(t[post])) post++;
		while(in(t[post])) w.push_back((t[post]>'z')?(t[post]-'z'+'a'):t[post]),post++;
		word.push_back(w); 
	}
	cout<<"读取完毕！\n";
	while(true){
		string q,o;
		cout<<"输入你想补全的残缺的单词,未知部分用*代替。\n";
		cin>>q;
		getchar();//读取刚刚剩下的一个空格 
		cout<<"输入已经猜错了的字母，没有的话直接按下回车键\n";
		getline(cin,o);
		bool succ=0;
		int total=0;
		map<string,int>lib;
		int count[27];
		memset(count,0,sizeof(count));
		for(unsigned int i=0;i<word.size();i++)
		{
			if(lib.find(word[i])==lib.end())
			if(q.size()==word[i].size()&&exclude(word[i],o,q))
			{
				bool flag=1;
				for(unsigned int j=0;j<q.size();j++)
				{
					if(q[j]!='*'&&q[j]!=word[i][j]){
						flag=0;
						break;
					}
				}
				if(flag){
					succ=1;
					lib[word[i]]++;
					cout<<++total<<"\t"<<word[i]<<endl;
					for(unsigned int j=0;j<word[i].size();j++) count[((word[i][j]>'z')?word[i][j]-26:word[i][j])-'a']++;
				}
			}
		}
		if(!succ){
			cout<<"单词没有找到啊~你知道答案么？（yes/no）";
			string know;cin>>know;
			if(know=="y"||know=="yes"){
				cout<<"请输入答案："; 
				string ans; 
				cin>>ans;
				cout<<"好哒，它已经被保存了\n";
				fout<<ans<<endl; 
			}
		}
		else{
			cout<<"共计"<<total<<"个符合条件的单词\n";
			for(int i=0;i<26;i++) cout<<(char)(i+'a')<<" "<<count[i]<<endl;
		}
		cout<<endl<<endl<<endl;
	}
	return 0;
}



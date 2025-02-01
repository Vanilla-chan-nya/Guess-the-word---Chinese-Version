#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
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
	if (ch <= 'z' && ch >= 'a') return 1;
	if (ch <= 'Z' && ch >= 'A') return 1;
	return 0;
}

bool exclude(string a, string b, string c)//a中没有b中的任何字母,a中没有c中不同位置的任何字母 
{
	for (unsigned i = 0; i < a.size(); i++)
		for (unsigned j = 0; j < b.size(); j++)
			if (a[i] == b[j]) {
				//cout<<"当前单词为"<<a<<"，重复字母为"<<a[i]<<endl;
				return 0;//猜错的字母不可能有 
			}

	map<char, int>lib;
	for (unsigned int i = 0; i < c.size(); i++) if (c[i] != '*') lib[c[i]]++;
	for (unsigned int i = 0; i < a.size(); i++) if (c[i] == '*' && lib.find(a[i]) != lib.end()) return 0;

	return 1;
}

vector<string>word;

string t;
int main()
{
	ifstream fin("word.txt");
	ofstream fout("word.his", ios::app);
	ifstream his("word.his");

	if (his.peek() == EOF) cout << "没有查询历史\n";
	else while (his.peek() != EOF) his >> t, word.push_back(t);

	cout << "读取数据库...\n";
	while (fin.peek() != EOF) {
		string w;
		getline(fin, t);
		int post = 0;
		while (!in(t[post]) && post < t.size()) post++;
		while (in(t[post]) && post < t.size()) w.push_back((t[post] < 'a') ? (t[post] - 'A' + 'a') : t[post]), post++;
		word.push_back(w);
	}
	cout << "读取完毕！\n";
	set<char>have,no;
	unsigned int len=8;
	string yes="";
	for(unsigned int i=0;i<len;i++) yes.push_back('*');
	while(true)
	{
		cout<<"cls|clear|add x|del x|yes 1h2e3l4l5o|save str"<<endl<<"-----------------------------------------------"<<endl;
		string op;
		cin>>op;
		if(op=="clear"||op=="cls")
		{
			system("cls");
			have.clear();
			no.clear();
			yes="";
			for(unsigned int i=0;i<len;i++) yes.push_back('*');
		}
		else if(op=="add")
		{
			string str;
			cin>>str;
			for(unsigned int i=0;i<str.size();i++)
			{
				have.insert(str[i]);
			}
		}
		else if(op=="del")
		{
			string str;
			cin>>str;
			for(unsigned int i=0;i<str.size();i++)
			{
				no.insert(str[i]);
			}
		}
		else if(op=="yes")
		{
			string str;
			cin>>str;
			for(unsigned int i=0;i<str.size();i+=2)
			{
				int idx=str[i]-'0';
				if(idx<=5&&idx>=1) yes[idx-1]=str[i+1];
			}
		}
		else if(op=="save")
		{
			string ans;
			cin >> ans;
			cout << "好哒，它已经被保存了\n";
			fout << ans << endl;
		}
		else if(op=="len")
		{
			int x;cin>>x;
			len=x;
			cout<<"长度已经被修改为"<<len<<endl;
			yes="";
			for(unsigned int i=0;i<len;i++) yes.push_back('*');
		}
		vector<string>maybe;
		for(unsigned int i=0;i<word.size();i++)
		{
			//check word[i]
			if(word[i].size()==len)
			{
				//yes
				bool succ=1;
				for(unsigned int j=0;j<len;j++)
				{
					if(yes[j]=='*'||yes[j]==word[i][j]) continue;
					else succ=0;
				}
				if(succ==0) continue;
				//have
				for(char ch='a';ch<='z';ch++)
				{
					if(have.find(ch)!=have.end())
					{
						//in word[i]?
						bool flag=0;
						for(unsigned int j=0;j<len;j++) if(word[i][j]==ch) flag=1;
						if(flag==0)
						{
							succ=0;
							break;
						}
					}
					else if(no.find(ch)!=no.end())
					{
						//not in word[i]?
						bool flag=0;
						for(unsigned int j=0;j<len;j++) if(word[i][j]==ch) flag=1;
						if(flag==1)
						{
							succ=0;
							break;
						}
					}
				}
				if(succ==0) continue;
				maybe.push_back(word[i]);
			}
		}
		cout<<"当前可能的结果有 "<<maybe.size()<<" 个"<<endl;
		if(maybe.size()<=10)
		{
			for(unsigned int i=0;i<maybe.size();i++) cout<<i+1<<". "<<maybe[i]<<endl;
			cout<<endl;
		}
		else
		{
			cout<<"随机输出几个吧："<<endl;
			random_shuffle(maybe.begin(),maybe.end());
			for(unsigned int i=0;i<6;i++) cout<<i+1<<". "<<maybe[i]<<endl;
			cout<<endl;
		}
	}
	return 0;
}


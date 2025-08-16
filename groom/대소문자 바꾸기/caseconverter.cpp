#include <iostream>
using namespace std;
string case_converter(string str);

int main(){
	string str;
	int n;
	
	cin >> n >> str;
	str = case_converter(str);
	cout << str;
	return 0;	
}

string case_converter(string str)
{
	for(int i=0;i < str.length();i++)
		{
			if(str[i] <= 90)
			{
				for(int x=65;x<=90;x++)
				{
					if(str[i] == x)
					{
						str[i]+=32;
					}
				}
			}
			else
			{
				for(int x=97;x<=122;x++)
					{
						if(str[i] == x)
						{
							str[i]-=32;
						}
					}
			}
		}
	return str;
}

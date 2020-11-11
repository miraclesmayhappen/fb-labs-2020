#include "Header.h"

//modulus count
int mod(int a, int b)
{
	return (a % b + b) % b;
}

// text to int conversion and vice versa
vector<int> text_to_num(string& text)
{
	string tmp;
	vector<int> numtext(text.length(), 0);

	for (int i = 0; i < text.length(); i++)
	{
		tmp = text.substr(i, 1);
		numtext.at(i) = AlphNum[tmp];
		tmp.clear();

	}
	return numtext;
}

string num_to_text(vector<int>& numtext)
{
	string text;
	for (int i = 0; i < numtext.size(); i++)
	{
		text += NumAlph[numtext.at(i)];
	}
	return text;
}

//Extended Euclidean Algorithm

int gcd(int a, int b)
{
	if (a == 0)
	{
		return b;
	}
	//recursive
	return gcd(b % a, a);
}


//Inverse Modulo
int inverse_mod (int a, int m)


////frequencies
 //letters
//bigrams
void ngramm_freq_nocoverup(string& str, map <string, float>& mp, int n)
{
	string tmpstr;
	int i = 0;
	while (i < str.length() && i + n != str.length() - 1)
	{

		tmpstr = str.substr(i, n);
		mp[tmpstr] ++;
		tmpstr.clear();
		i += n;
	}

}

map<string, float> perc_freq(int length, map<string, float>& mp, bool nocover)
{
	map<string, float> map_fr;
	if (nocover == true)
	{
		length = length / 2;
	}
	else
	{
		length -= 1;
	}
	for (map<string, float>::const_iterator it = mp.begin(); it != mp.end(); ++it)
	{
		map_fr.insert({ it->first, (it->second / length) });
	}

	return map_fr;
}
//5 bigrams



pair<int, int> getkey(int a, int b)
{
	return make_pair(a, b);
}
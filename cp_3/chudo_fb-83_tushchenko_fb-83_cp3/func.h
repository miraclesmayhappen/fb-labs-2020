#include "sidefunc.h"

//encode
vector<int> encode(string& text, pair<int, int> &key)
{
	int a = key.first;
	int b = key.second;
	string let1, let2;
		int x,y, y1, y2;
		vector<int> encnum;
	for (int i = 0; i+1 < text.length(); i+=2)
	{
		//get 2 letters
		let1 = text.substr(i, 1); // x1
		let2 = text.substr(i + 1, 1); //x2
		// X = x1 * m + x2
		x = AlphNum[let1] * alpha_size + AlphNum[let2];
		// Y = a*X + b mod m^2
		y = mod(x * a + b, pow(alpha_size, 2));
		// Y = y1*m + y2
		y1 = y / alpha_size;
		y2 = y % alpha_size;
		encnum.push_back(y1);
		encnum.push_back(y2);
		let1.clear(); let2.clear();
		y1 = 0; y2 = 0;
	}

	if (text.length() % 2 != 0)
	{
		let1 = text.substr(text.length()-1, 1);
		x = AlphNum[let1] * alpha_size;
		y = mod(x * a + b, pow(alpha_size, 2));
		y1 = y / alpha_size;
		encnum.push_back(y1);
	}



	return encnum;
}

string encode(string& text, pair<int, int> &key)
{
	vector<int> encrnum = encode(text, key);
	return num_to_text(encrnum);
}


//decode
vector<int> decode(vector<int>& textnum, pair<int, int>& key)
{
	int a = key.first;
	int b = key.second;
	string let1, let2;
	int x, y, x1, x2;
	vector<int> decnum;
	int a_inv = inverse_mod(a, alpha_size);


	for (int i = 0; i + 1 < textnum.size(); i += 2)
	{
		// Y = y1 * m + y2
		// textnum.at(i) = y1
		// textnum.at(i+1) = y2
		y = textnum.at(i) * alpha_size + textnum.at(i + 1);
		// X = a^-1 * (Y - b) mod m
		x = mod(a_inv * (y - b), alpha_size);
		// X = x1 * m + x2
		x1 = x / alpha_size;
		x2 = x % alpha_size;

		decnum.push_back(x1);
		decnum.push_back(x2);

	}

	if (textnum.size() % 2 != 0)
	{
		y = textnum.back() * alpha_size;
		x = mod(a_inv * (y - b), alpha_size);
		x1 = x / alpha_size;
		decnum.push_back(x1);
	}

	return decnum;
}

vector<int> decode(string& text, pair<int, int> &key)
{
	vector<int> textnum = text_to_num(text);
	return decode(textnum, key);
}

string decode(vector<int>& textnum, pair<int, int>& key)
{
	vector<int> decnum = decode(textnum, key);
	return num_to_text(decnum);
}

string decode(string& text, pair<int, int>& key)
{
	vector<int> decnum = decode(text, key);
	return num_to_text(decnum);
}

//find key
//pair<int,int> crackkey()




//test lang
bool test_forbidden_bigrams(string& text)
{
	vector<string> forbidden;
	{
	forbidden.push_back("àü");
	forbidden.push_back("îü");
	forbidden.push_back("åü");
	forbidden.push_back("èü");
	forbidden.push_back("îû");
	forbidden.push_back("àû");
	forbidden.push_back("åû");
	forbidden.push_back("ôá");
	forbidden.push_back("ôâ");
	forbidden.push_back("ôã");
	forbidden.push_back("ôæ");
	forbidden.push_back("õæ");
	}

	for (int i = 0; i < forbidden.size(); i++)
	{
		size_t found = text.find(forbidden.at(i));
		if (found != string::npos)
		{
			return false;
		}
	}

	return true;
}


//linear

vector<int> linear(int a, int b, int m)
{
	int d = gcd(a, m);
	vector<int> res;
	if (d == 1)
	{
		int x = mod(inverse_mod(a) * b, m);
		res.push_back(x);
	}
	else 
		if (d > 1)
		{
			if (b % d != 0)
			{
				cout << "No Solutions for equation:  " << a << " * x = " << b << " (mod " << m << ")" << endl;
				
			}
			else
			{
				int a1 = a / d;
				int b1 = b / d;
				int m1 = m / d;
				int x = mod(inverse_mod(a1) * b1, m1);
				res.push_back(x);
				for (int i = 1; i < d - 1; i++)
				{
					x += m1;
					res.push_back(x);
				}
			}
		}

	return res;
}
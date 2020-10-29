#include "Header.h"

int mod(int a, int b) // eto ne ya velosiped pridumala, ono ne schitalo <0
{
	return (a % b + b) % b;
}

void cleanup(string& str)
{

	for (int i = 0; i < str.length(); i++)
	{

	//	//replace ¸
		if (str.at(i) == '¸' || str.at(i) == '¨') { str.at(i) = 'å'; }


		//set to lowercase
		if (str.at(i) >= -64 && str.at(i) <= -33)
		{
			str.at(i) += 32;
		}

		//	//cleanup all non-letter symbols but spaces
	if (!(str.at(i) >= -32 && str.at(i) <= -1))
	{
		str.at(i) = 127;
	}

	}



	str.erase(std::remove(str.begin(), str.end(), 127), str.end());


	replace(str.begin(), str.end(), '\n', ' ');
	//erase double spaces
	//size_t ds = str.find("  ");
	//while (ds != std::string::npos)
	//{
	//	str.erase(ds, 1);
	//	ds = str.find("  ");
	//}
	//str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	cout << "cleaning done" << endl;

}

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

//inline string key_string(string& key, int text_length)
//{
//	string keystr;
//	for (int i = 0; i < text_length; i++)
//	{
//		keystr += key.at(i%key.length());
//	}
//
//	return keystr;
//}

 string encode(string& text, string& key)
{
	vector<int> encoded(text.length(), 0);
	vector<int> keynum = text_to_num(key);
	vector<int> textnum = text_to_num(text);
	for (int i = 0; i < textnum.size(); i++)
	{
		encoded.at(i) = (textnum.at(i) + keynum.at(i % (keynum.size())))%32;
	}

	string encodedstr = num_to_text(encoded);

	return encodedstr;
}

 string decode(string& encoded, string& key)
 {
	 vector<int> decoded(encoded.length(), 0);
	 vector<int> keynum = text_to_num(key);
	 vector<int> textnum = text_to_num(encoded);
	 for (int i = 0; i < textnum.size(); i++)
	 {
//		 cout << textnum.at(i) << " - " << keynum.at(i % (keynum.size())) << " = " << mod(textnum.at(i) - keynum.at(i % (keynum.size())), 32) << endl;
		 decoded.at(i) = mod(textnum.at(i)-keynum.at(i % (keynum.size())), 32);
	 }

	 string decodedstr = num_to_text(decoded);

	 return decodedstr;

 }



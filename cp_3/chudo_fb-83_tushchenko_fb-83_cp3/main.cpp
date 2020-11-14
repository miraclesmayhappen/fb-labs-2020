#include "func.h"

int main()
{
	setlocale(LC_CTYPE, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	string encoded = readfile(fin, "D:\\cryptolab3\\test.txt");
	cleanup(encoded);
	//vector<int> encrnum = encode(text, key);
	//string encoded = num_to_text(encrnum);

	//cout << "open text :" << text << endl;
	//cout << "encrypted with key (" << key.first << ", " << key.second << ") : " << endl;
	//cout << encoded << endl;


	vector<pair<int, int>> evalkeys = evalkey(encoded);
	vector<pair<int, int>> foundkey = testkeys(evalkeys, encoded);

	vector<int> encrnum = text_to_num(encoded);

	for (int i = 0; i < foundkey.size(); i++)
	{
		vector<int> decnum = decode(encrnum, foundkey.at(i));
		string decoded = num_to_text(decnum);
		writefile(decoded, fout, "decodemy.txt");
	}






	system("pause");
	return 0;

}
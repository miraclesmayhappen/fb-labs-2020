#include "func.h"


int main()
{
	setlocale(LC_CTYPE, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//in-out streams
	ofstream fout;
	ifstream fin;

	//string to read file, path, key	
	string text, path, key;


	path = "encode.txt";

	//get filename to read
	//while (path == "")
	//{
	//	cout << "Enter filename to encode:	";
	//	getline(cin, path);
	//}

	//read file
	{	fin.open(BASE_DIR + path);

	//check for file open failure
	if (fin.fail())
	{
		std::cout << "Error opening input file" << endl;
		fin.close();
		return -1;
	}
	else
	{
		std::cout << "Input file is opened successfully" << endl;
	}

	getline(fin, text, '\0');
	std::cout << "file reading is completed" << endl;

	//close input stream
	fin.close();
	}


	string mydecode;

	{	fin.open("D:\\cryptolab2\\decode.txt");

	//check for file open failure
	if (fin.fail())
	{
		std::cout << "Error opening input file" << endl;
		fin.close();
		return -1;
	}
	else
	{
		std::cout << "Input file is opened successfully" << endl;
	}

	getline(fin, mydecode, '\0');
	std::cout << "file reading is completed" << endl;

	//close input stream
	fin.close();
	}

	//clean text string
	cleanup(text);
	cout << text << endl;



	cout << "Enter key	";
	getline(cin, key);
	cleanup(key);
	cout << endl << "Your key: " << key << endl;


	string encoded = encode(text, key);
//	cout << "Encoded text:" << endl << encoded << endl;
	{	fout.open("encode_result.txt");
	if (!fout.fail())
	{
		fout << encoded;
	}
	fout.close(); }


	string decoded = decode(encoded, key);
//	cout << "Decoded text:" << endl << decoded << endl;
	{	fout.open("decode_result.txt");
	if (!fout.fail())
	{
		fout << decoded;
	}
	fout.close(); }

	double encode_index = conformity_index(encoded);
	double decoded_index = conformity_index(decoded);
	cout << "Conformity index:" << endl << "Encoded:	" << encode_index << endl << "Decoded:	" << decoded_index << endl;

	vector<int> encoded_num = text_to_num(encoded);
	//cout << "Encoded in num" << endl;
	//cout_vector(encoded_num);
	vector<int> mydecode_num = text_to_num(mydecode);

	int keylength = eval_r(mydecode_num, 30);
	string crackedkey = crack_key(mydecode_num, keylength);

	cout << "Cracked key:	"<< crackedkey << endl;
	cout << "Wanna edit cracked key?  0/1" << endl;
	int answ;
	cin >> answ;
	string variantdecoded;

	if (answ == 1)
	{
		string mykey;
		cout << "Enter edited key:	";
		cin.ignore();
		getline(cin, mykey);	
		variantdecoded = decode(mydecode, mykey);
	}
	else {
		variantdecoded = decode(mydecode, crackedkey);
	}

	//string mykey = "вшекспирбуря";


	{	fout.open("variantdecode_result.txt");
	if (!fout.fail())
	{
		fout << variantdecoded;
	}
	fout.close(); }

	system("PAUSE");
	return 0;
}
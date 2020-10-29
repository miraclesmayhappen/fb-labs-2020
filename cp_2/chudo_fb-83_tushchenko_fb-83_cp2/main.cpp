#include "func.h"
//#include "Header.h"

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


	//clean text string
	cleanup(text);
	cout << text << endl;



	cout << "Enter key	";
	getline(cin, key);
	cleanup(key);
	cout << endl << "Your key: " << key << endl;


	string encoded = encode(text, key);
	cout << "Encoded text:" << endl << encoded << endl;


	string decoded = decode(encoded, key);
	cout << "Decoded text:" << endl << decoded << endl;








	system("PAUSE");
	return 0;
}
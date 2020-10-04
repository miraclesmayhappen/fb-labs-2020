#include "Header.h"

//some cleanup
void clean_string(string &str)
{


	for (int i = 0; i < str.length(); i++)
	{

		//cleanup all non-letter symbols but spaces
		if ((str.at(i) > 32 && str.at(i) < 65) || (str.at(i) > 90 && str.at(i) < 97) || (str.at(i) > 127 && str.at(i) < 255) /*|| str.at(i) == char("�")*/)
		{
			str.at(i) = 127;
		}
		


		//replace �, �
		if (str.at(i) == '�') { str.at(i) = '�'; }
		if (str.at(i) == '�' || str.at(i) == '�') { str.at(i) = '�'; }


		//set to lowercase

		{		// ya znayu chto reshenie ne samoe elegantnoe no zato rabochee
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
			if (str.at(i) == '�') { str.at(i) = '�'; }
		}


	}
	str.erase(std::remove(str.begin(), str.end(), char("�")), str.end());
	str.erase(std::remove(str.begin(), str.end(), 127), str.end());
	size_t ds = str.find("  ");
	while (ds != std::string::npos)
	{
		str.erase(ds, 1);
		ds = str.find("  ");
	}


	replace(str.begin(), str.end(), '\n', ' ');
	cout << "cleaning done" << endl;
}

// nu tut nazvanie samo za sebya govorit
void erase_spaces(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

////count letters appereance
//void letter_freq(string &str, map<string, float> &mp)
//{
//	//count 
//	string tmpstr;
//	for (int i = 0; i < str.length(); i++)
//	{
//		if (str.at(i) != 127)
//		{
//			//mp[str.at(i)] ++;
//			tmpstr = str.substr(i, 1);
//			mp[tmpstr] ++;
//			tmpstr.clear();
//
//		}
//	}
//
//}



//count ngramm appereance
void ngramm_freq(string& str, map <string, float> &mp, int n)
{
	//bool contdel;
	string tmpstr;
	for (int i = 0; i < str.length() && i + n != str.length() - 1; i++)
	{
		
			tmpstr = str.substr(i, n);
			mp[tmpstr] ++;
			tmpstr.clear();

	}
}

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

//frequency of letter in per cents
map<string, float> perc_freq(int length, map<string, float> &mp)
{
	map<string, float> map_fr;

	for (map<string, float>::const_iterator it = mp.begin(); it != mp.end(); ++it)
	{
		map_fr.insert({ it->first, (it->second/ length) });
	}

	return map_fr;
}

// cout map
void show_map(map<string, float> &mp)
{
	for (map<string, float>::const_iterator it = mp.begin(); it != mp.end();++it)
	{
		cout << "'" << it->first << "'" << " " << setprecision(5) << it->second << endl;
	}
}

//fout map
void fout_map(ofstream& ofs, map<string, float>& mp)
{
	for (map<string, float>::const_iterator it = mp.begin(); it != mp.end(); ++it)
	{
		ofs << "'" << it->first << "'	" << it->second << endl;
	}
}

//count enthropy
float enthropy_calc(map<string, float>& mp, float n)
{
	float H = 0;
	for (map<string, float>::const_iterator it = mp.begin(); it != mp.end(); ++it)
	{
		H -= it->second * log2(it->second);
	}
//	cout << H << "		";
	H = H / n;
//	cout << H << endl;

	return H;
}
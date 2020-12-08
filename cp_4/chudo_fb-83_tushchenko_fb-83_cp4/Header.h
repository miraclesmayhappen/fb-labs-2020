#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <Windows.h> //for 1251
#include <iomanip> // for setpresicion
#include <algorithm> // for remove replace
#include <cmath>
#include <utility> //pair
#include <tuple>

#include <boost/random.hpp> //rand
#include <boost/random/independent_bits.hpp>
#include <boost/multiprecision/cpp_int.hpp> // cpp_int

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;

ifstream fin;
ofstream fout;

vector<int> dividers = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59 };



	// Declare our random number generator type, the underlying generator
   // is the Mersenne twister mt19937 engine, and we'll generate 256 bit
   // random values, independent_bits_engine will make multiple calls
   // to the underlying engine until we have the requested number of bits:
// obtain a seed from the timer

typedef independent_bits_engine<mt19937, 256, cpp_int> generator_type;
generator_type gen (static_cast<unsigned int>(std::time(0)));







class Pers
{
public:

	Pers(); //constructor
	Pers(pair<cpp_int, cpp_int> publ); //constructor

	pair<cpp_int, cpp_int> getpublickey();
	void printpublickey();

	void printprivatekey();

	pair< cpp_int, cpp_int> sign_message(cpp_int& M/*, tuple<cpp_int, cpp_int, cpp_int>& privatekey*/);
	bool check_signature(pair< cpp_int, cpp_int> sign_mes, pair< cpp_int, cpp_int> publickey);
	
	cpp_int encrypt(cpp_int M, pair<cpp_int, cpp_int>& publkey);
	cpp_int decrypt(cpp_int C/*, tuple<cpp_int, cpp_int, cpp_int>& privatekey*/);

	void setkey();

	pair< cpp_int, cpp_int> RSA_sender(Pers &B, cpp_int k);
	cpp_int RSA_reciever(Pers& A, pair<cpp_int, cpp_int> mes);

private:


	pair<cpp_int, cpp_int> publickey; //pbk value
	tuple<cpp_int, cpp_int, cpp_int> privatekey; //pvk value


	pair<cpp_int, cpp_int> gen_publickey(cpp_int& p, cpp_int& q, cpp_int& phi_n); // generate pbk
	pair< tuple<cpp_int, cpp_int, cpp_int>, pair<cpp_int, cpp_int>> gen_keyset(); // generate pbk and prk



};








#endif
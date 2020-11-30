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
#include <boost/multiprecision/cpp_int.hpp> // uint256_t

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
typedef independent_bits_engine<mt19937, 256, uint256_t> generator_type;
generator_type gen;






class Pers
{
public:

	Pers(); //constructor

	pair<uint512_t, uint256_t> getpublickey();
	void printpublickey();

	pair< uint512_t, uint512_t> sign_message(uint512_t& M/*, tuple<uint256_t, uint256_t, uint256_t>& privatekey*/);
	bool check_signature(pair< uint512_t, uint512_t>& sign_mes, pair< uint512_t, uint256_t>& publickey);
	
	uint512_t encrypt(uint512_t M, pair<uint512_t, uint256_t>& publkey);
	uint512_t decrypt(uint512_t C/*, tuple<uint256_t, uint256_t, uint256_t>& privatekey*/);

	void setkey();



private:


	pair<uint512_t, uint256_t> publickey; //pbk value
	tuple<uint256_t, uint256_t, uint256_t> privatekey; //pvk value


	pair<uint512_t, uint256_t> gen_publickey(uint256_t& p, uint256_t& q, uint256_t& phi_n); // generate pbk
	pair< tuple<uint256_t, uint256_t, uint256_t>, pair<uint512_t, uint256_t>> gen_keyset(); // generate pbk and prk


	pair< uint512_t, uint512_t> RSA_sender(Pers &B, uint512_t k);
	uint512_t RSA_reciever(Pers& A, pair<uint512_t, uint512_t> mes);
		



};








#endif
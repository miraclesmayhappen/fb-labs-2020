#include "sidefunc.h"

pair <uint256_t, uint256_t> Pers::gen_publickey(uint256_t &p, uint256_t &q, uint256_t &phi_n)
{
	uint256_t e;
	bool flag = false;
	
	while (!flag)
	{
		e = 2 + gen() % (phi_n - 3);
		flag = (gcd(e, phi_n) == 1);
	}

	//(n, e)
	return make_pair(p * q, e);

}

pair< tuple<uint256_t, uint256_t, uint256_t>, pair<uint256_t, uint256_t>> Pers::gen_keyset()
{
	uint256_t p = gen_prime();
	uint256_t q = gen_prime();

	uint256_t phi_n = prime_euler(p, q);

	pair<uint256_t, uint256_t> publickey = gen_publickey(p, q, phi_n);

	uint256_t d = inverse_mod(publickey.second, phi_n);

	tuple<uint256_t, uint256_t, uint256_t> privatekey = make_tuple(d, p, q);

	pair< tuple<uint256_t, uint256_t, uint256_t>, pair<uint256_t, uint256_t>> keyset = make_pair(privatekey, publickey);

	return keyset;
}

Pers::Pers()
{
	pair< tuple<uint256_t, uint256_t, uint256_t>, pair<uint256_t, uint256_t>> keyset = gen_keyset();
	this->publickey = keyset.second;
	this->privatekey = keyset.first;
}


void Pers::setkey()
{
	pair< tuple<uint256_t, uint256_t, uint256_t>, pair<uint256_t, uint256_t>> keyset = gen_keyset();
	this->publickey = keyset.second;
	this->privatekey = keyset.first;
}

pair<uint256_t, uint256_t> Pers::getpublickey()
{
	return this->publickey;
}

uint256_t Pers::encrypt(uint256_t &M/*, pair<uint256_t, uint256_t> & publickey*/)
{	
	//n = publickey.first;
	//e = publickey.second;
	// 0 <= M <= n-1

	if (M > this->publickey.first - 1 || M < 0)
	{
		return 0;
	}

	// C = M^e mod n

	return mod(pow(M, this->publickey.second), this->publickey.first);
}

uint256_t Pers::decrypt(uint256_t& C/*, tuple<uint256_t, uint256_t, uint256_t> &privatekey*/)
{
	// d = privatekey<0>
	// n = privatekey<1> * privatekey<2>
	// M = C^d mod n
	uint256_t d;
	tie(d, ignore, ignore) = this->privatekey;

	return mod(pow(C, d), this->publickey.first);
}

pair< uint256_t, uint256_t> Pers::sign_message(uint256_t& M/*, tuple<uint256_t, uint256_t, uint256_t>& privatekey*/)
{
	// d = privatekey<0>
	// n = privatekey<1> * privatekey<2> // n = publickey.first
	// S = M^d mod n

	uint256_t d;
	tie(d, ignore, ignore) = this->privatekey;

	uint256_t S = mod(pow(M, d), this->publickey.first);

	return make_pair(M, S);

}

bool Pers::check_signature(pair< uint256_t, uint256_t>& sign_mes, pair< uint256_t, uint256_t>& publickey)
{
	// M = sign_mes.first
	// S = sign_mes.second
	// n = publickey.first
	// e = publickey.second

	// M = S^e mod n


	if ( mod(pow(sign_mes.second, publickey.second), publickey.first) == sign_mes.first)
	{
		return true;
	}

	else
	{
		return false;
	}

}

pair< uint256_t, uint256_t> Pers::RSA_sender(Pers &B, uint256_t k)
{

	//pair<uint256_t, uint256_t> Apublic = this->publickey;
	pair<uint256_t, uint256_t> Bpublic = B.getpublickey();

	// public key: (n,e)

	// An = Apublic.first
	// Ae = Apublic.second
	// Bn = Bpublic.first
	// Be = Bpublic.second

	// private key: (d, p, q)
	// Apriv = this->privatekey
	// A_d = get<0>this->privatekey


	if (this->publickey.first > Bpublic.first)
	{
		this->setkey();
		RSA_sender(B, k);
	}

	// S = k^A_d mod An

	uint256_t S = mod(pow(k, get<0>(this->privatekey)), this->publickey.first);

	// S1 = S^Be mod Bn

	S = mod(pow(S, Bpublic.second), Bpublic.first);

	// k1 = k^Be mod Bn

	k = mod(pow(k, Bpublic.second), Bpublic.first);

	//(k1, S1)
	return make_pair(k, S);

}

uint256_t Pers::RSA_reciever(Pers& A, pair<uint256_t, uint256_t> &mes)
{
	pair<uint256_t, uint256_t> Apublic = A.getpublickey();

	// mes = (k1, S1)
	// k = k1 ^ Bd mod Bn
	// S = S1 ^ Bd mod Bn

	// An = Apublic.first
	// Ae = Apublic.second

	// B_d = get<0>this->privatekey
	// B_n = this->publickey.first

	uint256_t k = mes.first;
	uint256_t S = mes.second;

	// k = k1 ^ B_d mod B_n 
	k = mod(pow(k, get<0>(this->privatekey)), this->publickey.first);

	// S = S1 ^ B_d mod B_n

	S = mod(pow(S, get<0>(this->privatekey)), this->publickey.first);

	// k == S^ A_e mod A_n

	if (k == mod(pow(S, Apublic.second), Apublic.first))
	{
		cout << "Message recieved" << endl;
		return k;
	}

	else
	{
		cout << "Authentication failed" << endl;
		return 0;
	}

}

void Pers::printpublickey()
{
	cout << "Modulus:" << endl;
	cout << hex << this->publickey.first << endl;
	cout << "Public exponent: " << endl;
	cout << hex << this->publickey.second << endl;
}


#include "sidefunc.h"

pair <cpp_int, cpp_int> Pers::gen_publickey(cpp_int &p, cpp_int &q, cpp_int &phi_n)
{
	cpp_int e;
	bool flag = false;
	
	while (!flag)
	{
		e = 2 + gen() % (phi_n - 3);
		flag = (gcd(e, phi_n) == 1);
	}

	//(n, e)
	return make_pair(p * q, e);

}

pair< tuple<cpp_int, cpp_int, cpp_int>, pair<cpp_int, cpp_int>> Pers::gen_keyset()
{
	cpp_int p = gen_prime();
	cpp_int q = gen_prime();

	cpp_int phi_n = prime_euler(p, q);

	pair<cpp_int, cpp_int> publickey = gen_publickey(p, q, phi_n);

	cpp_int d = inverse_mod(publickey.second, phi_n);

	tuple<cpp_int, cpp_int, cpp_int> privatekey = make_tuple(d, p, q);

	pair< tuple<cpp_int, cpp_int, cpp_int>, pair<cpp_int, cpp_int>> keyset = make_pair(privatekey, publickey);

	return keyset;
}

Pers::Pers()
{
	pair< tuple<cpp_int, cpp_int, cpp_int>, pair<cpp_int, cpp_int>> keyset = gen_keyset();
	this->publickey = keyset.second;
	this->privatekey = keyset.first;
}

Pers::Pers(pair<cpp_int, cpp_int> publ)
{
	this->publickey = publ;
}


void Pers::setkey()
{
	pair< tuple<cpp_int, cpp_int, cpp_int>, pair<cpp_int, cpp_int>> keyset = gen_keyset();
	this->publickey = keyset.second;
	this->privatekey = keyset.first;
}

pair<cpp_int, cpp_int> Pers::getpublickey()
{
	return this->publickey;
}

cpp_int Pers::encrypt(cpp_int M, pair<cpp_int, cpp_int> & publkey)
{	
	//n = publickey.first;
	//e = publickey.second;
	// 0 <= M <= n-1

	if (M > publkey.first - 1 || M < 0)
	{
		return 0;
	}

	// C = M^e mod n

	return horner_pow(M, publkey.second, publkey.first);
}

cpp_int Pers::decrypt(cpp_int C)
{
	// d = privatekey<0>
	// n = privatekey<1> * privatekey<2>
	// M = C^d mod n
	cpp_int d;
	tie(d, ignore, ignore) = this->privatekey;

	return /*mod(pow(C, d), this->publickey.first)*/ horner_pow(C, d, this->publickey.first);
}

pair< cpp_int, cpp_int> Pers::sign_message(cpp_int& M)
{
	// d = privatekey<0>
	// n = privatekey<1> * privatekey<2> // n = publickey.first
	// S = M^d mod n

	cpp_int d;
	tie(d, ignore, ignore) = this->privatekey;

	cpp_int S = horner_pow(M, d, this->publickey.first);

	return make_pair(M, S);

}

bool Pers::check_signature(pair< cpp_int, cpp_int> sign_mes, pair< cpp_int, cpp_int> publickey)
{
	// M = sign_mes.first
	// S = sign_mes.second
	// n = publickey.first
	// e = publickey.second

	// M = S^e mod n


	if (horner_pow(sign_mes.second, publickey.second, publickey.first) == sign_mes.first)
	{
		return true;
	}

	else
	{
		return false;
	}

}

pair< cpp_int, cpp_int> Pers::RSA_sender(Pers &B, cpp_int k)
{

	{////pair<cpp_int, cpp_int> Apublic = this->publickey;
	

	//// public key: (n,e)

	//// An = Apublic.first
	//// Ae = Apublic.second
	//// Bn = Bpublic.first
	//// Be = Bpublic.second

	//// private key: (d, p, q)
	//// Apriv = this->privatekey
	//// A_d = get<0>this->privatekey
	}

	pair<cpp_int, cpp_int> Bpublic = B.getpublickey();
	if (this->publickey.first > Bpublic.first)
	{
		this->setkey();
		RSA_sender(B, k);
	}

	cpp_int S = sign_message(k).second;
	S = encrypt(S, Bpublic);

	k = encrypt(k, Bpublic);

	return make_pair(k, S);



	{//// S = k^A_d mod An

	//cpp_int S = /*mod(pow(k, get<0>(this->privatekey)), this->publickey.first)*/ power(k, get<0>(this->privatekey), this->publickey.first);

	//// S1 = S^Be mod Bn

	//S = /*mod(pow(S, Bpublic.second), Bpublic.first)*/ power (S, Bpublic.second, Bpublic.first);

	//// k1 = k^Be mod Bn

	//k = /*mod(pow(k, Bpublic.second), Bpublic.first)*/power(k, Bpublic.second, Bpublic.first);

	////(k1, S1)
	//return make_pair(k, S);
	}
}

cpp_int Pers::RSA_reciever(Pers& A, pair<cpp_int, cpp_int> mes)
{
	pair<cpp_int, cpp_int> Apublic = A.getpublickey();

	// mes = (k1, S1)
	// k = k1 ^ Bd mod Bn
	// S = S1 ^ Bd mod Bn

	// An = Apublic.first
	// Ae = Apublic.second

	// B_d = get<0>this->privatekey
	// B_n = this->publickey.first

	cpp_int k = mes.first;
	cpp_int S = mes.second;

	k = decrypt(k);
	S = decrypt(S);


	//cpp_int d;
	//tie(d, ignore, ignore) = privatekey;

	//// k = k1 ^ B_d mod B_n 
	//k = /*mod(pow(k, get<0>(this->privatekey)), this->publickey.first)*/power(k, d, publickey.first);

	//// S = S1 ^ B_d mod B_n

	//S = /*mod(pow(S, get<0>(this->privatekey)), this->publickey.first)*/power(S, d, publickey.first);

	//// k == S^ A_e mod A_n
	pair<cpp_int, cpp_int> sign = make_pair(k, S);
	if (check_signature(sign, Apublic))
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

void Pers::printprivatekey()
{
	// d p q
	cout << "d:" << hex << get<0>(this->privatekey) << endl;
}


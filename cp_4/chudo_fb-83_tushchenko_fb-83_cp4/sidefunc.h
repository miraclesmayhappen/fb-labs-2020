#include "Header.h"

////get x^n
//uint256_t pow(uint256_t x, uint256_t n)
//{
//	if (n == 0)
//		return 1;
//	else if (n == 1)
//		return x;
//	else if (n % 2 == 0)
//		return pow(x * x, n / 2);
//	else
//		return pow(x * x, n / 2) * x;
//}
//
//modulus count
uint256_t mod(uint256_t a, uint256_t b)
{
	return (a % b + b) % b;
}

// x*y mod p
uint512_t multiplymod(uint512_t x, uint512_t y, uint512_t p)
{
	uint512_t res = 0;
	uint512_t b = x % p;

	while (y > 0)
	{
		if (y % 2 == 1)
		{
			res = (res + b) % p;
		}

		b = (2 * b) % p;
		y /= 2;
	}

	return res % p;
}

// x^y mod p
/* based on Applied Cryptography by Bruce Schneier*/
uint512_t power(uint512_t x, uint512_t y, uint512_t p)

{
	uint512_t res = 1;

	x = x % p; 

	if (x == 0) return 0; 

	while (y > 0)
	{
		// If y is odd, multiply x with result  
		if (y % 2 == 1)
		{
			res = (res * x) % p;
		}

		// y must be even now  
		x = (x * x) % p;
		y = y/2;  

	}
	return res % p;
}

//eea
pair<uint256_t, uint256_t> eea(uint256_t a, uint256_t b)
{
	pair<uint256_t, uint256_t> res; //gcd, inv

	vector<uint256_t> Rvalues;
	Rvalues.push_back(a);
	Rvalues.push_back(b);

	vector<uint256_t> Uvalues;
	Uvalues.push_back(1);
	Uvalues.push_back(0);

	vector<uint256_t> Vvalues;
	Vvalues.push_back(0);
	Vvalues.push_back(1);

	bool flag = false;

	uint256_t r, q, u, v;

	for (int i = 2; !flag; i++)
	{

		r = Rvalues.at(i - 2) % Rvalues.at(i - 1);

		if (r == 0)
		{
			flag = true;
			break;
		}

		q = Rvalues.at(i - 2) / Rvalues.at(i - 1);

		u = Uvalues.at(i - 2) - q * Uvalues.at(i - 1);

		v = Vvalues.at(i - 2) - q * Vvalues.at(i - 1);

		Uvalues.push_back(u);
		Vvalues.push_back(v);
		Rvalues.push_back(r);

	}

	r = Rvalues.back();
	u = Uvalues.back();

	res = make_pair(r, u);

	return res;
}

//gcd 
uint256_t gcd(uint256_t a, uint256_t m)
{
	pair<uint256_t, uint256_t> ee = eea(a, m);
	return ee.first;
}

//Inverse Modulo
uint256_t inverse_mod(uint256_t a, uint256_t m)
{
	pair <uint256_t, uint256_t> ee; //gcd, inv
	ee = eea(a, m);

	if (ee.first != 1)
	{
		cout << a << "^-1  (mod " << m << ")  doesn`t exist" << endl;
		return 0;
	}

	else
	{
		return mod(ee.second, m);
	}

}

////////////////////////////////////////////////////////////

bool trial_division(uint256_t num)
{

	for (int i=0; i<dividers.size(); i++)
	{
		if (num % dividers.at(i) == 0)
		{
			//cout << "divisible to " << dividers.at(i) << endl;
			return false;
		}
	}

	return true;
}

bool miller_rabin(uint256_t p)
{
	uint256_t k = 1000;//1000 + rand() % 9000;
	vector<uint256_t> used_x;
	uint256_t x = 0;
	uint256_t d, s;
	int	counter = 0;
	s = 0;
	d = p - 1;


	//find d and s values
	// p-1 = d * 2^s
	while (d % 2 == 0)
	{
		d /= 2;
		s++;
	}

	for (counter; counter < k; counter++)
	{
		bool flag = false;
		//generate x
		while (!flag)
		{
			//generate x
			 x = 2 + gen() % (p - 4); // 1<x<p
			//check if this x value was already chosen
			vector<uint256_t>::iterator it = find(used_x.begin(), used_x.end(), x);
			if (it == used_x.end())
			{ //if not in used_x go next step
				flag = true;
				used_x.push_back(x);
			}
		}

		// check if p is pseudo prime for x
		if (gcd(x, p) > 1)
		{
			return false;
		}

		else
		{

			// p is strongly pseudo prime for x
			if (abs(/*mod(pow(x, d), p))*/ power(x, d, p) )== 1)
			{
				continue;
			}
			
			else
				//x_r = x^(d*2^r)
			{
				// xrc = x^d mod p
				uint512_t xrc = x;/*= /*mod(pow(x, d), p) power(x, /*d2, p)*/
								
				for (int r = 1; r <= s-1; r++)
				{
					//x_r = x_r-1 ^2
					xrc = /*mod(pow(xrc, 2), p)*/power(xrc, d, p);

					// p is strongly pseudo prime for x
					if (xrc == p-1) 
					{
						break;
					}
					else 
						 // p is not strongly pseudo prime for x
						if (xrc == 1)
						{
							return false;
						}

				}

			}

		}
	}
	return true;
}

bool try_prime(uint256_t num)
{
	if (!trial_division(num))
	{
		//cout << "failed trial division" << endl;
		return false;
	}
	else if (!miller_rabin(num))
	{
		//cout << "failed miller rabin" << endl;
		return false;
	}
	else return true;
}

uint256_t gen_prime()
{
	bool flag = false;
	uint256_t p;
	while (!flag)
	{

		p = gen();
	//	cout << p << endl;
		flag = try_prime(p);

	}
	return p;
}

uint256_t prime_euler(uint256_t &num1, uint256_t &num2)
{
	return (num1 - 1) * (num2 - 1);
}
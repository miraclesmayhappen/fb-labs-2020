#include "Header.h"

////get x^n
//cpp_int pow(cpp_int x, cpp_int n)
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
cpp_int mod(cpp_int a, cpp_int b)
{
	return (a % b + b) % b;
}

//// x*y mod p
//cpp_int multiplymod(cpp_int x, cpp_int y, cpp_int p)
//{
//	cpp_int res = 0;
//	cpp_int b = x % p;
//
//	while (y > 0)
//	{
//		if (y % 2 == 1)
//		{
//			res = (res + b) % p;
//		}
//
//		b = (2 * b) % p;
//		y /= 2;
//	}
//
//	return res % p;
//}

// x^y mod p
/* based on Applied Cryptography by Bruce Schneier*/
//cpp_int power(cpp_int x, cpp_int y, cpp_int p)
//
//{
//	cpp_int res = 1;
//
//	x = x % p; 
//
//	if (x == 0) return 0; 
//
//	while (y > 0)
//	{
//		// If y is odd, multiply x with result  
//		if (y % 2 == 1)
//		{
//			res = (res * x) % p;
//		}
//
//		// y must be even now  
//		x = (x * x) % p;
//		y = y/2;  
//
//	}
//	return res % p;
//}

cpp_int horner_pow(cpp_int x, cpp_int m, cpp_int p)
{
	x = x % p;
	cpp_int y = 1;
	vector<cpp_int> e_s;
	// m = e0 + e1*2+e2*2^2 +...
	while (m != 0)
	{
		e_s.push_back(m % 2);
			m /= 2;
	}
	//e_s basicly stores reversed binary of m
	//cout << "binary:" << endl;
	//for (int i = e_s.size() - 1; i >= 0; i--)
	//{
	//	cout << e_s.at(i);
	//}
	//cout << endl;

	for (int i = e_s.size() - 1; i >=0 ; i--)
	{
		// y = y * x^ei
		// y = y * y
		//cout << "step" << i << "	y=" << y << "	e=" << e_s.at(i) <<endl;
		if (e_s.at(i) == 1)
		{
			y = (y * x) % p;
		//	cout << "y = (y * x) % p = " << y<< endl;
		}

		if (i == 0)
		{
			break;
		}

		y = (y * y) % p;
		//cout << "y = (y * y) % p = " << y << endl;
	}


	return y;
}

//eea
pair<cpp_int, cpp_int> eea(cpp_int a, cpp_int b)
{
	pair<cpp_int, cpp_int> res; //gcd, inv

	vector<cpp_int> Rvalues;
	Rvalues.push_back(a);
	Rvalues.push_back(b);

	vector<cpp_int> Uvalues;
	Uvalues.push_back(1);
	Uvalues.push_back(0);

	vector<cpp_int> Vvalues;
	Vvalues.push_back(0);
	Vvalues.push_back(1);

	bool flag = false;

	cpp_int r, q, u, v;

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
cpp_int gcd(cpp_int a, cpp_int m)
{
	pair<cpp_int, cpp_int> ee = eea(a, m);
	return ee.first;
}

//Inverse Modulo
cpp_int inverse_mod(cpp_int a, cpp_int m)
{
	pair <cpp_int, cpp_int> ee; //gcd, inv
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

bool trial_division(cpp_int num)
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

bool miller_rabin(cpp_int p)
{
	cpp_int k = 1000;//1000 + rand() % 9000;
	vector<cpp_int> used_x;
	cpp_int x = 0;
	cpp_int d, s;
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
			vector<cpp_int>::iterator it = find(used_x.begin(), used_x.end(), x);
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
			if (horner_pow(x, d, p)== 1 || horner_pow(x, d, p) == p-1)
			{
				continue;
			}
			
			else
				//x_r = x^(d*2^r)
			{
				// xrc = x^d mod p
				cpp_int xrc = x;/*= /*mod(pow(x, d), p) power(x, /*d2, p)*/
								
				for (int r = 1; r <= s-1; r++)
				{
					//x_r = x_r-1 ^2
					xrc = /*mod(pow(xrc, 2), p)*/horner_pow(xrc, d, p);

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

bool try_prime(cpp_int num)
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

cpp_int gen_prime()
{
	bool flag = false;
	cpp_int p;
	while (!flag)
	{

		p = gen();
	//	cout << p << endl;
		flag = try_prime(p);

	}
	return p;
}

cpp_int prime_euler(cpp_int &num1, cpp_int &num2)
{
	return (num1 - 1) * (num2 - 1);
}
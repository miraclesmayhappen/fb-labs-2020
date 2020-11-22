#include "func.h"

int main()
{
	Pers A;

	A.printpublickey();

	uint256_t Message = gen();

	pair< uint256_t, uint256_t> sign = A.sign_message(Message);

	cout << hex << sign.first << endl;
	cout << hex << sign.second << endl;


	return 0;
}
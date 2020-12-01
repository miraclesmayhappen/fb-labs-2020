#include "func.h"

int main()
{

	/*cout << "prostye" << endl;
	cout << try_prime(2467) << endl;
	cout << try_prime(2843) << endl;
	cout << try_prime(2099) << endl;
	cout << try_prime(3229) << endl;
	cout << try_prime(3313) << endl;
	cout << try_prime(2011) << endl;
	cout << try_prime(3571) << endl;

	cout << "sostavnye" << endl;
	cout << try_prime(2620) << endl;
	cout << try_prime(5020) << endl;
	cout << try_prime(87633) << endl;
	cout << try_prime(88730) << endl;
	cout << try_prime(69615) << endl;
	cout << try_prime(98747) << endl;
	cout << try_prime(4625747) << endl;*/

	Pers Chris, Den;
	//uint1024_t *serv_key_n = 0xDE5CCC03C4499D5E75AEBE8C3D7FEFC39FCC70C0921C49760467AFBF0CCBAE6F;
pair <uint512_t, uint256_t> server_key = make_pair(0xD6986EC43B8DF7A6732BA2FE7C98F911, 0x10001);
	Pers Server(server_key);

	pair <uint512_t, uint256_t> chris_key = Chris.getpublickey();

	cout << hex << chris_key.first << endl <<  chris_key.second << endl;

	cout << sizeof(chris_key.first) << endl;


	return 0;
}
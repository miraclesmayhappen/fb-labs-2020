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
////	cpp_int serv_key_n;
////	cout << "enter serv n " << endl;
////	cin >> serv_key_n;
////pair <cpp_int, cpp_int> server_key = make_pair(serv_key_n, 0x10001);
////	Pers Server(server_key);
//
	pair <cpp_int, cpp_int> chris_key = Chris.getpublickey();

	Chris.printpublickey();
	Chris.printprivatekey();

	cpp_int encr = Chris.encrypt(7, chris_key);
	cout << "encrypted:" << endl << hex << encr << endl;

	cpp_int decr = Chris.decrypt(encr);

	cout << "decrypted:" << decr << endl;


	//cpp_int mess = 7;

	//pair< cpp_int, cpp_int> signat = Chris.sign_message(mess);

	//// M S
	//cout << "Message: " << signat.first << endl;
	//cout << "Signature: " << signat.second << endl;

	////pair<cpp_int, cpp_int> signat = make_pair(mess, sign);
	//

	//cout << "Verification: " << Den.check_signature(signat, chris_key) << endl;


	/*pair <cpp_int, cpp_int> s = Chris.sign_message(mess);

	cout << "signature" << endl << hex << s.second << endl;*/


	//cout << horner_pow(785, 679, 851) << endl;



	return 0;
}
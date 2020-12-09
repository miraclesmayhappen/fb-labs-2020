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

	//Pers Chris, Den;
	//Pers Chris;
//	cpp_int serv_key_n;
//	cout << "enter serv n " << endl;
//	cin >> serv_key_n;
//pair <cpp_int, cpp_int> server_key = make_pair(serv_key_n, 0x10001);
//	Pers Server(server_key);
//
	//pair <cpp_int, cpp_int> chris_key = Chris.getpublickey();


	//Chris.printpublickey();


	////cpp_int mess = 0b1001000011011111010101011010001110001;

	////pair< cpp_int, cpp_int> signat = Chris.sign_message(mess);

	////// M S
	////cout << "Message: " << signat.first << endl;
	////cout << "Signature: " << signat.second << endl;



	//pair< cpp_int, cpp_int> sentkey = Chris.RSA_sender(Den, 777777777777);

	//cout << "sentkey k: " << sentkey.first << endl << "sentkey s: " << sentkey.second << endl;

	//cpp_int received_key = Den.RSA_reciever(Chris, sentkey);

	//cout << "receivedkey: " << received_key << endl;

	//Den.check_signature(signat, chris_key);




	Pers Server = Server.cr_s("serv_k.txt");
	Server.printpublickey();

	Pers Chris;
	Chris.printpublickey();

	pair<cpp_int, cpp_int> servk = Server.getpublickey();
	
	cpp_int M=1, S=1;
	cout << "enter message" << endl;
	//cin >> M;
	M = 111;
	cout << "enter signature" << endl;
	cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> S;
	

	pair<cpp_int, cpp_int> mes = make_pair(M, S);

	Chris.check_signature(mes, servk);






	return 0;
}
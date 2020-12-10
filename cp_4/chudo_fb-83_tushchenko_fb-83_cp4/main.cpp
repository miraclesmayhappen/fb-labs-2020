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
	cout << "Server" << endl;
	Server.printpublickey();

	Pers Chris("chris_k.txt");
	cout << endl << "Chris" << endl;
	Chris.printpublickey();
	//Chris.printprivatekey();
	cout << endl;

	pair<cpp_int, cpp_int> servk = Server.getpublickey();
	pair<cpp_int, cpp_int> chrisk = Chris.getpublickey();
	
			//decrypt
	cout << endl << "Encryption" << endl;
	cpp_int mes = 0x12345;
	cout << "Message: " << mes << endl;
	cpp_int encr = Server.encrypt(mes, chrisk);
	cout <<"Encrypted by Server: " << encr << endl;
	cout << "Decryption by Chris" << endl;
	cpp_int decr = Chris.decrypt(encr);
	cout << "Message: " << decr << endl;
	

			//encrypt
	cout << endl << "Encryption for Server" << endl;
	cout << "Message: " << mes << endl;
	cpp_int serv_encr = Chris.encrypt(mes, servk);
	cout << "Encrypted by Chris: " << hex << serv_encr << endl;

		//server ReceiveKey
	cout << endl << "Sending key for server:" << endl;
	cout << "Original key: " << mes << endl;
	pair< cpp_int, cpp_int> sentkey = Chris.RSA_sender(Server, mes);
	cout << "Sent key:" << sentkey.first << endl;
	cout << "Sent key signature: " << sentkey.second << endl;


		//server SendKey
/*	cout << endl << "Receiving key from Server" << endl;
	cpp_int k, S;
	cout << "Enter key:	";
	cin >> hex >> k;
	cout << endl << "Enter signature:	";
	cin >> hex >> S;
	cpp_int key = Chris.RSA_reciever(Server, k, S);
	cout << endl << "Received key:	" << key << endl;*/

	





	return 0;
}
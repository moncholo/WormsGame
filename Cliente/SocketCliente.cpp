#include "SocketCliente.h"

SocketCliente::SocketCliente () {

}

SocketCliente::SocketCliente (int puertoEnServidor, char* ipServidor) {
	Log log(PATH_LOG);
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(1, 1), &wsadata) != 0) {
		log.escribirLog("WSAStartup failed.");
		return;
	}
	//int error = WSAStartup(0x0202, &wsadata);
	if (WSAStartup(0x0202, &wsadata)) {
		log.escribirLog("Cliente: For some reason we couldn't start Winsock.");
		return;
	}
    if (wsadata.wVersion != 0x0202) {
        WSACleanup ();
		log.escribirLog("Version incorrecta de Winsock.");
        return;
    }

    addr.sin_family = AF_INET;					// address family Internet
    addr.sin_port = htons (puertoEnServidor);		//Port to connect on
    addr.sin_addr.s_addr = inet_addr ((const char*)ipServidor);		//Target IP

	socketC = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (socketC == INVALID_SOCKET)   {
		log.escribirLog("Error al crear el socket del cliente.");
		return;						//Don't continue if we couldn't create a //socket!!
	}
    std::cout << "Intentando conectar con el servidor."<<std::endl;
	int conecto = connect(socketC, (SOCKADDR*)&addr, (int)sizeof(addr));
    if (conecto == SOCKET_ERROR) {
		log.escribirLog("No se pudo conectar con el servidor.");
		return;
    }
}
//el buffer receptor es del tamaño de la info qe espero recibir.
//espero recibir ese tamaño fijo y no otro.
int SocketCliente::recibirInfo(char* buffer_receptor, int CantBytes){

	Log log(PATH_LOG);
	int total = 0, bytesQFaltan = CantBytes, recibi = 0;
	while (total < CantBytes) {
		recibi = recv(socketC, buffer_receptor+total, bytesQFaltan, 0);
		if (recibi == -1) {
			std::cout << "cliente: no se pudo recibir el msj." << std::endl;
			log.escribirLog("cliente: no se pudo recibir el msj.");
			return -1;
		} else {
			total += recibi;
			bytesQFaltan -= recibi;
		}
	}

	return total;
}

int SocketCliente::enviarInfo(char* info, int cantBytes){
	Log log(PATH_LOG);
	int total = 0, bytesQFaltan = cantBytes, mande;
	while (total < cantBytes) {
		mande = send(socketC, info+total, bytesQFaltan, 0);
		if (mande == -1) {
			log.escribirLog("cliente: no se pudo enviar el msj.");
			//return -1;
		}
		total += mande;
		bytesQFaltan -= mande;
	}
	return total;
}

void SocketCliente::terminarConexion(){
	closesocket(socketC);
	WSACleanup();
}
#include "Socket.h"

Socket::Socket () {
}

Socket::Socket (int puerto) {
	Log log(PATH_LOG);
	WSADATA w;
	int error = WSAStartup (0x0202, &w);   // Fill in WSA info
	if (error) {
		log.escribirLog("Servidor: For some reason we couldn't start Winsock.");
		return;
	}
	if (w.wVersion != 0x0202) {
        WSACleanup ();
		log.escribirLog("Version incorrecta de Winsock.");
        return;
    }

    addr.sin_family = AF_INET;			// Address family
    addr.sin_port = htons (puerto);		// Assign port to this socket
    //Accept a connection from any IP using INADDR_ANY
    //You could pass inet_addr("0.0.0.0") instead to accomplish the 
    //same thing. If you want only to watch for a connection from a 
    //specific IP, specify that //instead.
    addr.sin_addr.s_addr = htonl (INADDR_ANY);

    socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);		// Create socket
    if ((int)socket_ == -1)  {
		log.escribirLog("Error al crear el socket del servidor.");
		return;						//Don't continue if we couldn't create a //socket!!
	}

	char optval = 1;
	int reusable = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)); 
//para liberar el puerto utilizado y pueda ser reutilizado en un futuro cercano
	if (reusable == -1) {
		perror("Error SO_REUSEADDR");
		exit(1);
	}

    if (bind(socket_, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR) {
		std::stringstream s; s<<"Error bind del socket puerto "<<puerto<< ".";
		log.escribirLog(s.str());
		return;						
	}
}
//el buffer receptor es del tamaño de la info qe espero recibir.
//espero recibir ese tamaño fijo y no otro.
int Socket::recibirInfo(char* buffer_receptor, int CantBytes){
	Log log(PATH_LOG);
	int total = 0, bytesQFaltan = CantBytes, recibi;
	while (total < CantBytes) {
		recibi = recv(socketC, buffer_receptor+total, bytesQFaltan, 0);
 		if (recibi == -1) {
			//log.escribirLog("Servidor: no se pudo recibir el msj.");
			return -1;
		} else {
			total += recibi;
			bytesQFaltan -= recibi;
		}
	}
	return total;
}

int Socket::enviarInfo(char* info, int cantBytes){
	Log log(PATH_LOG);
	int total = 0, bytesQFaltan = cantBytes, mande;
	while (total < cantBytes) {
		mande = send(socketC, info+total, bytesQFaltan, 0);
		if (mande == -1) {
			log.escribirLog("Servidor: no se pudo enviar el msj.");
			return -1;
		}
		total += mande;
		bytesQFaltan -= mande;
	}
	return total;
}

void Socket::terminarConexion(){
	closesocket(socketC);
}
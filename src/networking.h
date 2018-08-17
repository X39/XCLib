#ifndef XCLIB_NETWORKING_H_
#define XCLIB_NETWORKING_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(_WIN32)
	/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib,"WS2_32")
#else
	/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#define INVALID_SOCKET -1
	typedef int SOCKET;
#endif
	typedef struct sockaddr_in SOCKETADDR;
    /*
    Required to be called at the start of any program start
    before the actual first socket gets created.
    Will initialize the networking systems.
    
    Returns 0 on success.
    */
	int networking_init(void);
    /*
    Required to be called when networking components have been
    used and thus networking_init was callen.
    Uninitializes the networking system and closes
    all sockets.
    
    Returns 0 on success.
    */
	int networking_cleanup(void);
    /*
    Closes provided socket.
    Returns 0 on success.
    
    param 1: the socket to close.
    */
	int networking_close(SOCKET);
    /*
    Creates a new client socket and connects it to provided address.
    The socket is put into the third parameter.
    Returns 0 on success.
    
    param 1: the IP Address to connect to.
    param 2: the port to connect to.
    param 3: out parameter for the socket.
    */
	int networking_create_client(const char*, const char*, SOCKET*);
    /*
    Creates a new server and initializes it.
    Returns 0 on success.
    
    param 1: out parameter for the socket.
    */
	int networking_create_server(SOCKET *);
    /*
    Binds provided socket onto provided port.
    Returns 0 on success.
    
    param 1: socket to work on.
    param 2: the port to bind to.
    */
	int networking_server_bind(SOCKET*, unsigned short);
    /*
    Makes the socket to actively listen for connections.
    Returns 0 on success.
    
    param 1: socket to work on.
    param 2: The maximum pending connections.
    */
	int networking_server_listen(SOCKET*, int);
    /*
    Waits for data to read up to provided timeout (ms).
    Returns 0 if no data is available or timeout passed.
    
    param 1: socket to work on.
    param 2: maximum timeout in ms.
    */
	int networking_poll(SOCKET* s, int timeoutms);
    /*
    Waits for an incomming connection in a blocking way.
    Returns 0 on success.
    
    param 1: socket to work on.
    param 2: out parameter for connected socket.
    param 3: out parameter for connected info.
    */
	int networking_server_accept_block(SOCKET*, SOCKET*, SOCKETADDR*);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !XCLIB_NETWORKING_H_

#pragma once

#include <errno.h>
#include <malloc.h>
#include <sys/socket.h>
#include <netinet/in.h>

/**
 * @brief Reads LENGTH bytes into BUFFER from SOCKET. This function is best used
 * to read 2 or more bytes.
 * @return 0 for success; -1 for errors; if returns a positive number, this
 * number is number of bytes left to read.
*/
int receive(int socket, char *buffer, size_t length);
/**
 * @brief Reads 1 byte from SOCKET. On errors, sets the errno variable to
 * ECONNABORTED.
 * @return Read unsigned char.
*/
uint8_t receive_byte(int socket);
/**
 * @brief Reads 2 bytes from SOCKET. On errors, sets the errno variable to
 * ECONNABORTED.
 * @return Read unsigned short.
*/
uint16_t receive_uint16(int socket);
/**
 * @brief Reads 4 bytes from SOCKET. On errors, sets the errno variable to
 * ECONNABORTED.
 * @return Read unsigned int.
*/
uint32_t receive_uint32(int socket);
/**
 * @brief Reads string from SOCKET. On errors, sets the errno variable to
 * ECONNABORTED. Reading format: int -> string. First, the size of the string
 * is read, and then the string itself.
 * @return Pointer to allocated string.
*/
char *receive_bytes(int socket);

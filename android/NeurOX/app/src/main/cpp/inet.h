//
// Created by Admin on 15.04.2026.
//

#ifndef NEUROX_INET_H
#define NEUROX_INET_H

#include <sys/types.h>
#include <linux/in.h>

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus
    /**
     * Инициализирует подключение к серверу заполняя все соответствующие структуры и дескрипторы
     * по выходу из функции получаем полностью готовое к прослушиванию соединение с сервером
     * в случае успеха возвращает EXIT_FAILURE, в противном - EXIT_FAILURE
     *
     * @param _ServerAddr: const char* - DNS имя сервера
     * @param _ServerPort: uint16_t - Порт подключения к серверу
     * @param _EPollFD: int* - Указатель на дескриптор epoll_fd
     * @param _SocketFD: int* - Указатель на дескриптор соединения
     * @param _ServerInAddr: struct sockaddr_in* - Указатель на структуру адреса Сервера
     *
     * @returns int - EXIT_SUCCESS || EXIT_FAILURE
     * */
    int initConnection(
            const char* _ServerAddr,
            uint16_t _ServerPort,
            int* _EPollFD,
            int _SocketFD,
            struct sockaddr_in* _ServerInAddr
            );

    /**
     * Устанавливает подключение в неблокирующий режим,
     * работает с любыми файловыми дескрипторами UNIX
     *
     * @param _FD: int - Дескриптор файла подключения
     *
     * @returns int - EXIT_SUCCESS || EXIT_FAILURE
     * */
    inline int setnonblock(int _FD);

    /**
     * Закрывает подключение
     *
     * @param _FD: int - файловый дескриптор подключения
     *
     * @returns void
     * */
    inline void closesocket(int _FD);

    /**
     * Инициализирует "sys/epoll" точку подключения,
     * при выходе с функции дескрипторы на которые указывают
     * _EPollFD и _SocketFD полностью готовы, в случае ошибки
     * в них сохраняются значения -1
     *
     * @param _EPollFD: int* - Указатель на дескриптор epoll
     * @param _SocketFD: int* - Указатель не дескриптор подключения
     *
     * @returns int - EXIT_SUCCESS || EXIT_FAILURE
     * */
    int initDescriptors(int* _EPollFD, int* _SocketFD);

    /**
     * */
    int initServerAddres(struct sockaddr_in* _ServerAddres, const char* _ServerName, uint16_t _ServerPort);

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif //NEUROX_INET_H

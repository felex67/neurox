#include <jni.h>
#include <string>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

constexpr char ServerAddres[] = "neurox.su";
constexpr uint16_t ServerPort = 7777;
constexpr int INVALID_SOCKET = -1;

extern "C" {


#pragma pack(push, 1)
    typedef struct PacketHeader { uint16_t size; uint8_t id; } PacketHeader;
#pragma pack(pop)

#pragma pack(push, 1)
    typedef struct Packet_CS_x00 {
        PacketHeader header;
        char Msg[1024];
    } Packet_CS_x00;
#pragma pack(pop)
    Packet_CS_x00 cs_0x00_init = { 0 };

#pragma pack(push, 1)
    typedef struct BoardCell {
        int8_t side: 2;
        int8_t x: 3;
        int8_t y: 3;
    } BoardCell;
#pragma pack(pop)

#pragma pack(push, 1)
    typedef struct GameState {
        BoardCell board[3][3];
        BoardCell log[9];
        BoardCell winners[3];
        unsigned char turn;
    } GameState;
#pragma pack(pop)

    GameState GameInit = {
            .board = {
                    {
                            { .side = 0, .x = 0, .y = 0 },
                            { .side = 0, .x = 1, .y = 0 },
                            { .side = 0, .x = 2, .y = 0 },
                    },
                    {
                            { .side = 0, .x = 0, .y = 1 },
                            { .side = 0, .x = 1, .y = 1 },
                            { .side = 0, .x = 2, .y = 1 },
                    },
                    {
                            { .side = 0, .x = 0, .y = 2 },
                            { .side = 0, .x = 1, .y = 2 },
                            { .side = 0, .x = 2, .y = 2 },
                    },
            },
            .log = {
                    { .side = 1, .x = 0, .y = 0 },
                    { .side = -1, .x = 0, .y = 0 },
                    { .side = 1, .x = 0, .y = 0 },
                    { .side = -1, .x = 0, .y = 0 },
                    { .side = 1, .x = 0, .y = 0 },
                    { .side = -1, .x = 0, .y = 0 },
                    { .side = 1, .x = 0, .y = 0 },
                    { .side = -1, .x = 0, .y = 0 },
                    { .side = 1, .x = 0, .y = 0 },
            },
            .winners = { 0 },
            .turn = 0,
    };

    struct State {
        int online;
    } state = { 0 };

}

/**
 * Основная функция работы с сетевым подключением.
 * Инициализирует подключение принимает пакеты от сервера, проверяет соединение на ошибки.
 * В случае ошибки устанавливает "state.online = 0"
 *
 * @param void
 * @returns void
 * */
void worker() {
    // Информация о сервере
    hostent* host = nullptr;
    // Адрес сервера
    sockaddr_in addr;
    // Структура события
    epoll_event epollEvent;
    // Дескриптор epoll
    int EPFd = INVALID_SOCKET;
    // Дескриптор соединения
    int fd = INVALID_SOCKET;
    /*
     * Не знаю зачем AndroidStudio просит заключать в дополнительные скобки,
     * раз просит - сделано =)
     * в обычном коде следует делать без дополнительных скобок:
     * if (host = gethostbyname(ServerAddres)) {}
     * */
    if ((host = gethostbyname(ServerAddres))) {
        addr.sin_family = AF_INET;
        addr.sin_port = htons(ServerPort);
        addr.sin_addr = *reinterpret_cast<in_addr*>(host->h_addr_list[0]);
    }
    else {
        // TODO: Добавить логирование ошибки разрешения имени сервера
        state.online = 0;
        return;
    }
    if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)));
    else {
        // TODO: Добавить логирование ошибки создания точки подключения
        state.online = 0;
        return;
    }
    if (!connect(fd, (sockaddr*)&addr, sizeof(addr)));
    else {
        // TODO: Добавить логирование ошибки подключения к серверу
        state.online = 0;
        return;
    }
    if ((EPFd = epoll_create1(0))) {
        // Делаем сокет неблокирующим
        int flags = fcntl(fd, F_GETFL);     // Читаем флаги
        if (flags != INVALID_SOCKET);
        else flags = 0;                         // Сбрасываем флаги если ошибка
        // Устанавливаем в неблокирующий режим и проверяем на ошибку
        if (INVALID_SOCKET != fcntl(fd, F_SETFL, flags | O_NONBLOCK));
        else {
            // TODO: Добавить логирование ошибки установки в неблокирующий режим
            // Закрываем соединение
            shutdown(fd, SHUT_RDWR);
            close(fd);
            // Закрываем EPFd, освобождаем ресурсы ядра
            close(EPFd);
            state.online = 0;
            return;
        }
        epollEvent.data.fd = fd;
        epollEvent.events = EPOLLIN | EPOLLOUT;
        if (EXIT_SUCCESS == epoll_ctl(EPFd, EPOLL_CTL_ADD, fd, &epollEvent));
        else {
            // TODO: Добавить логирование ошибки установки контроля над подключением
            // Закрываем подключение и EPFd
        }
    }
    else {
        // TODO: Добавить логирование ошибки создания дескриптора "epoll"
        state.online = 0;
        return;
    }
    while (state.online) {

    }
}


extern "C" JNIEXPORT jstring JNICALL
Java_ru_felexdev_neurox_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


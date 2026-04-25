#include "FXAlloc.h"

#include <threads.h>

// В этой переменной настраиваем градации и предположительное количесвто блоков
static const FXGrade grades[] = {
    { 32, 200 }, { 64, 200 }, { 128, 8000 },
    { 256, 4000 }, { 512, 2000 }, { 1024, 1200 },
    { 4096, 200 }, { 0x10000, 4 },
    { 0 }   // Ноль-терминант
};



#ifdef _WIN32
    // Windows-версия
__declspec(thread) extern void* (*fxalloc)(size_t _NBytes);
__declspec(thread) extern void (*fxfree)(void* _Ptr);
#else
    // POSIX-версия
    extern static pthread_key_t thread_key;
    
    extern void* (*fxalloc)(size_t _NBytes);
    extern void (*fxfree)(void* _Ptr);
#endif


extern static pthread_key_t thread_key;

void* fastalloc();

void init_tls() {
    pthread_setspecific(thread_key, (void*)fxalloc);
    fxalloc = fastalloc;
    // или более сложный вариант с хранением структуры
}
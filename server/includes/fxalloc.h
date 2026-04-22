#pragma once

#ifndef _WIN32
    #include <sys/types.h>
#endif //_WIN32

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    void* fxalloc(size_t _NBytes);

#ifdef __cplusplus
}
#endif // __cplusplus

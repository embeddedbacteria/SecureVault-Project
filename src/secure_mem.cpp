#include "../include/secure_mem.hpp"

namespace SecureVault {
    void secure_wipe(void* ptr, size_t len) {
        if (ptr == nullptr) return;
        // volatile: Derleyicinin bu silme işlemini optimize etmesini engeller.
        volatile unsigned char* p = (volatile unsigned char*)ptr;
        while (len--) {
            *p++ = 0;
        }
    }
}
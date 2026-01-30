#ifndef SECURE_MEM_HPP
#define SECURE_MEM_HPP

#include <iostream>

namespace SecureVault {
    // RAM'deki veriyi kalıcı olarak sıfırlar
    void secure_wipe(void* ptr, size_t len);
}

#endif
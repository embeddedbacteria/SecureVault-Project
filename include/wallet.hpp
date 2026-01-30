#ifndef WALLET_HPP
#define WALLET_HPP

#include <string>

namespace SecureVault {
    class Wallet {
    private:
        std::string master_seed;
        bool is_locked;
        const std::string pin = "1234";
        
        int failed_attempts = 0;       // Hatalı deneme sayısı
        const int max_attempts = 3;    // Maksimum hak
        bool is_permanently_locked = false; // Cihaz kendini imha etti mi?

    public:
        Wallet() : is_locked(true) {}
        ~Wallet(); 
        
        void generate_mnemonic();
        bool unlock_wallet(const std::string& input_pin);
        void show_seed();
    };
}

#endif
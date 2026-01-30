#include "../include/wallet.hpp"
#include "../include/secure_mem.hpp"
#include <iostream>
#include <string>
#include <conio.h>

// Yıldızlı PIN giriş fonksiyonu
std::string getMaskedInput() {
    std::string password = "";
    char ch;
    while (true) {
        ch = _getch(); // Tuşa basılmasını bekle (ekrana yazmaz)
        
        if (ch == 13) { // 13 = Enter tuşu
            std::cout << std::endl;
            break;
        } else if (ch == 8) { // 8 = Backspace (Geri silme)
            if (password.length() > 0) {
                password.pop_back();
                std::cout << "\b \b"; // Ekrandan bir karakter siler
            }
        } else if (ch >= 32 && ch <= 126) { // Yazdırılabilir karakterler
            password += ch;
            std::cout << '*';
        }
    }
    return password;
}

int main() {
    SecureVault::Wallet myWallet;

    std::cout << "--- SecureVault C++ HW Simulator ---" << std::endl;
    myWallet.generate_mnemonic();
    
    bool authenticated = false;

    while (!authenticated) {
        std::cout << "\nEnter PIN: ";
        // Eskiden: std::cin >> userPin; 
        // Şimdi:
        std::string userPin = getMaskedInput();

        if (myWallet.unlock_wallet(userPin)) {
            authenticated = true;
            myWallet.show_seed();
        } else {
            // Cüzdan kalıcı kilitlendiyse döngüden çık
            // (Buraya is_permanently_locked kontrolü eklenebilir ama 
            // şimdilik basit tutalım)
        }
    }

    std::cout << "\nClosing SecureVault..." << std::endl;
    return 0;
}
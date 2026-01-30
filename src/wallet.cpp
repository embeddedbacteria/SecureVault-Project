#include "../include/wallet.hpp"
#include "../include/secure_mem.hpp"
#include "logger.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace SecureVault {
    Wallet::~Wallet() {
        if (!master_seed.empty()) {
            secure_wipe(&master_seed[0], master_seed.capacity());
            std::cout << "\n[SECURITY] Sensitive data wiped from RAM." << std::endl;
        }
    }

    void Wallet::generate_mnemonic() {
        master_seed = "apple banana cherry dragon eagle forest ghost hunter ice jungle knight lemon";
        std::cout << "[SUCCESS] Mnemonic generated." << std::endl;
    }

    bool Wallet::unlock_wallet(const std::string& input_pin) {
    if (is_permanently_locked) {
        std::cout << "[FATAL] Device is wiped due to too many failed attempts!" << std::endl;
        Logger::log("ACCESS DENIED: Permanent lock active.");
        return false;
    }

    if (input_pin == pin) {
        is_locked = false;
        failed_attempts = 0; // Başarılı girişte sayacı sıfırla
        Logger::log("SUCCESS: Wallet unlocked successfully.");
        std::cout << "[ACCESS] Wallet Unlocked." << std::endl;
        return true;
    } else {
        failed_attempts++;
        std::cout << "[WARNING] Wrong PIN! Attempt: " << failed_attempts << "/" << max_attempts << std::endl;
        Logger::log("WARNING: Failed PIN attempt (" + std::to_string(failed_attempts) + ")");
        if (failed_attempts < max_attempts) {
            std::cout << "[PENALTY] Security delay active. Please wait: " << std::endl;
            
            for (int i = 10; i > 0; --i) {
                std::cout << i << "... " << std::endl; // Yan yana yazması için flush kullanıyoruz
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            std::cout << "\n[READY] You can try again now." << std::endl;
        }
        
        if (failed_attempts >= max_attempts) {
            is_permanently_locked = true;
            // KENDİNİ İMHA ET: Bellekteki seed'i hemen sil!
            secure_wipe(&master_seed[0], master_seed.capacity());
            master_seed = ""; 
            std::cout << "[SECURITY] Maximum attempts reached. Master seed WIPE triggered!" << std::endl;
            Logger::log("CRITICAL: Self-destruct triggered! Master seed wiped.");
        }
        return false;
    }
    }   

    void Wallet::show_seed() {
        if (is_locked) {
            std::cout << "[LOCKED] Unlock first to see seed!" << std::endl;
        } else {
            std::cout << "Your Seed: " << master_seed << std::endl;
        }
    }
}
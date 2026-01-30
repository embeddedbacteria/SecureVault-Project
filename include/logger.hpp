#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <ctime>
#include <windows.h> 
#include <lmcons.h>  

namespace SecureVault {
    class Logger {
    public:
        // Kullanıcı Adını Alır
        static std::string getUserName() {
            char username[UNLEN + 1];
            DWORD username_len = UNLEN + 1;
            if (GetUserNameA(username, &username_len)) {
                return std::string(username);
            }
            return "UnknownUser";
        }

        // Bilgisayar Adını (Cihaz Kimliği) Alır
        static std::string getComputerName() {
            char computerName[MAX_COMPUTERNAME_LENGTH + 1];
            DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
            if (GetComputerNameA(computerName, &size)) {
                return std::string(computerName);
            }
            return "UnknownHost";
        }

        static void log(const std::string& message) {
            std::ofstream logFile("vault_activity.log", std::ios::app);
            if (logFile.is_open()) {
                std::time_t now = std::time(nullptr);
                char timestamp[20];
                std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
                
                // Format: [ZAMAN] [PC_ADI\KULLANICI] MESAJ
                logFile << "[" << timestamp << "] "
                        << "[" << getComputerName() << "\\" << getUserName() << "] "
                        << message << std::endl;
                logFile.close();
            }
        }
    };
}

#endif
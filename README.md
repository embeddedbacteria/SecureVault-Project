# SecureVault: C++ Hardware Wallet Simulator

A high-security Hardware Wallet simulation written in C++. This project demonstrates low-level security concepts, memory safety, and anti-tamper mechanisms used in modern cryptographic devices.

## 🛡️ Security Features

- **Memory Protection:** Utilizes `secure_wipe` (zero-fill) to clear sensitive mnemonic data from RAM immediately after use, preventing memory dump attacks.
- **Anti-Brute Force:** Implements a strict "3-strikes" policy. The device triggers a self-destruct (memory wipe) after 3 failed PIN attempts.
- **Rate Limiting:** Enforces a 10-second security delay between failed attempts to mitigate automated brute-force scripts.
- **Masked Input:** PIN entry is masked with `*` characters to prevent "shoulder surfing" in terminal environments.
- **Security Auditing:** Maintains a time-stamped log file (`vault_activity.log`) that records access attempts, including the system username and device hostname for forensic tracking.
- **XOR Encryption:** The master seed is never stored in plain text; it is obfuscated using a bitwise XOR operation.

## 🛠️ Technical Stack

- **Language:** C++17
- **Platform:** Windows (utilizes Win32 API for identity tracking and masked input)
- **Compiler:** GCC/G++

## 🚀 How to Run

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/your-username/SecureVault-Project.git](https://github.com/your-username/SecureVault-Project.git)
   cd SecureVault-Project

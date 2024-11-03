#include "Header.h"

int main() {
    int option;

    while (true)
    {
        std::cout << "Choose action: encrypt and decrypt message(enter '1')/exit(enter '0'): ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option)
        {
        case 1: {
            secret();
            std::pair<int, int> qr = generateQandR(sum + 1, 2 * sum);
            q = qr.first; // Значение q
            r = qr.second; // Значение r
            multy_number(r, q);
            open(q, r);
            string message = "";
            std::cout << "Enter message: ";
            std::getline(std::cin, message);
            string bin = StringToBinary(message);
            vector <int> enc = encrypt(bin);
            cout << "Encrypted text: ";
            for (int i = 0; i < enc.size(); i++) {
                cout << enc[i] << " ";
            }
            string dec = binaryToText(decrypt(enc));
            cout << endl << "Decrypted text: " << dec << endl;
            clearData();
            break;
        }
        case 0: {
            return 0;
        }
        default:
            std::cout << "Wrong input" << std::endl;
            continue;
            break;
        }
    }
    return 0;
}
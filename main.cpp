#include <iostream>
#include <string>
bool checkChar (char symbol, int part)
{
    bool result;
    if (part == 0)
    {
        result = (symbol == '!' || (symbol >= '"' && symbol <= '\'') ||
                  symbol == '*' || (symbol >= '+' && symbol <= '9') ||
                  symbol == '=' || (symbol >= '?' && symbol <= 'Z') ||
                  (symbol >= '^' && symbol <= '~'));
    }
    else
    {
        result = (symbol == '-' || symbol == '.' ||
                  (symbol >= '0' && symbol <= '9') ||
                  (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z'));
    }

    return result;
}

void checkEmail (std::string &address)
{
    bool correctAddress {true};
    int shiftSymbolCounter {0};
    int firstPartCounter {0}, secondPartCounter {0};
    int part = 0;
    if (address[0] == '.' || address[address.length() - 1] == '.' || address[address.length() - 1] == '@' )
         // я думаю,что теперь в цикле не будет проверки когда '@' завершает строку
    {
        correctAddress = false;
    }

    for (int i = 0; i < address.length() && correctAddress; i++)
    {

        if (checkChar(address[i], part))
        {

            if ((address[i] == '.' && address[i+1] == '.') || (address[i] == '.' && address[i+1] == '@')
                || (address[i] == '@' && address[i+1] == '.'))
            {
                correctAddress = false;
            }

            if (address[i] == '@')
            {
                shiftSymbolCounter++;
                part = 1;
            } else if (shiftSymbolCounter > 0)
            {
                secondPartCounter++;
            } else if (shiftSymbolCounter == 0)
            {
                firstPartCounter++;
            }

            if (shiftSymbolCounter > 1 || firstPartCounter > 64 || secondPartCounter > 63
                || (firstPartCounter == 0 && shiftSymbolCounter > 0)
                || (secondPartCounter == 0 && shiftSymbolCounter > 0 && i == address.length() - 1))
            {
                correctAddress = false;
            }

        }
        else
        {
            correctAddress = false;
        }

    }
    std::cout << (correctAddress && shiftSymbolCounter == 1 ? "Yes" : "No") << std::endl;
}

int main()
{
    std::string email;
    std::cout << "Input email: ";
    getline(std::cin, email);
    checkEmail(email);
}

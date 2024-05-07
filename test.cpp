#include <iostream>
#include <cstring>

using namespace std;

class String {
private:
    char* str;
    int length;

public:
    String() : str(nullptr), length(0) {}

    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        strcpy_s(str, length + 1, s);
    }

    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        strcpy_s(str, length + 1, other.str);
    }

    ~String() {
        delete[] str;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy_s(str, length + 1, other.str);
        }
        return *this;
    }

    int GetLength() const {
        return length;
    }

    const char* GetString() const {
        return str;
    }

    void Clear() {
        delete[] str;
        str = nullptr;
        length = 0;
    }

    String operator+(const String& other) const {
        String result;
        result.length = length + other.length;
        result.str = new char[result.length + 1];
        strcpy_s(result.str, result.length + 1, str);
        strcat_s(result.str, result.length + 1, other.str);
        return result;
    }

    String& operator+=(const String& other) {
        char* temp = new char[length + other.length + 1];
        strcpy_s(temp, length + other.length + 1, str);
        strcat_s(temp, length + other.length + 1, other.str);
        delete[] str;
        str = temp;
        length += other.length;
        return *this;
    }

    bool operator==(const String& other) const {
        int result;
        return strncmp(str, other.str, length + 1 &result) == 0 && result == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    char operator[](int index) const {
        if (index >= 0 && index < length) {
            return str[index];
        }
        else {
            return '\0'; // Возвращаем нулевой символ для некорректного индекса
        }
    }
};

class BitString : public String {
public:
    BitString() : String() {}

    BitString(const char* s) : String(s) {
        // Проверка на наличие символов отличных от '0' и '1'
        for (int i = 0; i < GetLength(); ++i) {
            if ((*this)[i] != '0' && (*this)[i] != '1') {
                // Если находим символ отличный от '0' и '1', делаем строку пустой
                Clear();
                break;
            }
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other) {
        if (this != &other) {
            String::operator=(other);
        }
        return *this;
    }

    ~BitString() {}

    void ChangeSign() {
        // Добавьте здесь логику для изменения знака числа
    }

    BitString operator+(const BitString& other) const {
        return BitString((String::operator+(other)).GetString());
    }

    bool operator==(const BitString& other) const {
        return String::operator==(other);
    }

    bool operator!=(const BitString& other) const {
        return String::operator!=(other);
    }
};

int main() {
    // Пример использования класса BitString
    BitString bitStr1("101010");
    cout << "BitString 1: " << bitStr1.GetString() << endl;

    BitString bitStr2("1111100");
    cout << "BitString 2: " << bitStr2.GetString() << endl;

    BitString bitStr3("120102"); // Некорректный битовый рядок
    cout << "BitString 3: " << bitStr3.GetString() << endl;

    return 0;
}
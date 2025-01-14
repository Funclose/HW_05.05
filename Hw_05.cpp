#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)
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
        strcpy(str, s);
    }

    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    ~String() {
        delete[] str;
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy(str, other.str);
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
        strcpy(result.str, str);
        strcat(result.str, other.str);
        return result;
    }

    String& operator+=(const String& other) {
        char* temp = new char[length + other.length + 1];
        strcpy(temp, str);
        strcat(temp, other.str);
        delete[] str;
        str = temp;
        length += other.length;
        return *this;
    }

    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    char operator[](int index) const {
        if (index >= 0 && index < length) {
            return str[index];
        }
        else {
            return '\0'; // ��������� ������� ������ ��� ������������� �������
        }
    }
};

class BitString : public String {
public:
    BitString() : String() {}

    BitString(const char* s) : String(s) {
        // �������� �� ������ ������� ����� 0 � 1
        for (int i = 0; i < GetLength(); ++i) {
            if ((*this)[i] != '0' && (*this)[i] != '1') {
                // ���� ���� ������ �� ��������� 0 ��� 1 ������ ������ ������
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
    
    BitString bitStr1("101010");
    cout << "BitString 1: " << bitStr1.GetString() << endl;

    BitString bitStr2("1111100");
    cout << "BitString 2: " << bitStr2.GetString() << endl;

    BitString bitStr3("120102"); // ������������ ������� �����
    cout << "BitString 3: " << bitStr3.GetString() << endl;

    return 0;
}
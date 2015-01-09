#include <iostream>



class CLogin
{
public:
    CLogin() : Us() { };
    ~CLogin();

    CLogin(wchar_t UsNa, wchar_t UsPw);
    CLogin(wchar_t UsNa);

    wchar_t SendData(wchar_t UsNa[256], wchar_t UsPw[256]);       // Send data to server. 
    wchar_t GetUsNa(wchar_t UsNa[256]);         // Return only User Name
    wchar_t GetUsPw(wchar_t UsPw[256]);         // Return only User Passwort
    void GetData(wchar_t UsNa[256], wchar_t UsPw[256]);         // return User Name and User Passwort
    void ReadData(int data, int accid); // Read Data from Server	


private:
    wchar_t UsNa;
    wchar_t UsPw;
    wchar_t Us;



};

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <cmath>
#include <comdef.h>
// #include <vcclr.h>
#include <stdio.h>
#include <stdlib.h>
#include "CLogin.h"
#include "File/CFile.h"



CLogin::~CLogin()
{

}



wchar_t CLogin::GetUsNa(wchar_t UsNa[256])
{



    return *UsNa;

}

wchar_t CLogin::GetUsPw(wchar_t UsPw[256])
{

    return *UsPw;

}

void CLogin::GetData(wchar_t UsNa[256], wchar_t UsPw[256])
{
    CLogin log;
    CFile cfile;

    log.SendData(&UsNa[256], &UsPw[256]);
}

wchar_t CLogin::SendData(wchar_t UsNa[256], wchar_t UsPw[256])
{


  //  ser.ReadData(Data);
    return *UsNa; // Need to send data to server to check server side the account data.
    return *UsPw;

}

void CLogin::ReadData(int data, int accid) // temp int as responde code. Correct = 542 Incorrect = 1043, later the correct response code from server.
{
    CLogin log;
    if (data == 542)
    {

    }
    else if (data == 1043)
    {

    }


}
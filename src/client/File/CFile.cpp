#define _CRT_SECURE_NO_DEPRECATE
#include <wchar.h>
#include "CFile.h"

/* Define File Flags
*	1 - Music
*	2 - Graphic
*	3 - FullScr
*/

// Konstruktor: No spezific function actually
CFile::CFile()
{}

// Dekonstruktor: Close and End the file
CFile::~CFile()
{
	Textout("End of Options");
	fclose(m_File);
}

inline bool CFile::CSettingsExist(const char *FileName)
{
	if (FILE *file = fopen(FileName, "r"))
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

// CCreateSetting: If setting file not exist, create a setting file
void CFile::CCreateSetting(const char *FileName)
{

	if (CSettingsExist(FileName) == false)
	{

		// if new setting file, so clear this and write the head
		m_File = fopen(FileName, "w");
		Textout("------- Settings ----------");
		Textout("\r\n");

		// actually build konfiguration write
#ifdef _DEBUG
		Textout("BUILD: DEBUG\r\n");
#else
		Textout("BUILD: RELEASE\r\n");
#endif
		// Settings closed and reopen with append
		fclose(m_File);
		m_File = fopen(FileName, "a");
		CCreateBasic(FileName);
	}
	else
		COpenFile(FileName);
}

void CFile::CCreateFile(const char* FileName)
{
    if (CSettingsExist(FileName) == false)
    {

        // if new setting file, so clear this and write the head
        m_File = fopen(FileName, "w");
        Textout("------- Settings ----------");
        Textout("\r\n");

        // actually build konfiguration write
#ifdef _DEBUG
        Textout("BUILD: DEBUG\r\n");
#else
        Textout("BUILD: RELEASE\r\n");
#endif
        // Settings closed and reopen with append
        fclose(m_File);
        m_File = fopen(FileName, "a");
    }
    else
        COpenFile(FileName);
}

// CWriteMusic: Write the Music settings to the setting file
void CFile::CWriteMusic(int Music)
{
	if (Music == NULL)
	{
		Music = 50;
		Textout("Music: %i", Music, 1);
	}

	Textout("Music: %i", Music, 1);
}

// CWriteGraphic: Write the Graphic settings to the settings file
void CFile::CWriteGraphic(int x, int y)
{
	Textout("Graphic: %i x %i", x, y, 2);

}

// CWriteFullscr: Window Fullscreen or not, write this to setting file
// Fullscreen has two states, 0 for no full screen and 1 for full screen.
void CFile::CWriteFullScr(int FullScr)
{
	Textout("Fullscreen: %i", FullScr, 3);
}

// Textout functions.

// Simple Textout for only text.

void CFile::Textout(const char *Text)
{
	fprintf(m_File, Text);
	fflush(m_File);
}

void CFile::sTextout(const wchar_t *Text2, ...)
{
    fwprintf_s(m_File, Text2);
    fflush(m_File);
}

void CFile::wTextout(const char *Text, const wchar_t *Text2, ...)
{
    fprintf(m_File, Text);
    fwprintf(m_File, Text2);
    fflush(m_File);
}

void CFile::wTextout(const wchar_t *Text, ...)
{
    fprintf(m_File, "Test: ");
    fwprintf(m_File, Text);
    fflush(m_File);
}     

void CFile::wTextout(const wchar_t *Text[], ...)
{
    fprintf(m_File, "Test2: ");
    for (int i = 0; i < sizeof(Text[i]); i++)
        fwprintf(m_File, Text[i]);
    fflush(m_File);
}


void CFile::Textout(const char *Text, const char *Text2, ...)
{
    fprintf(m_File, Text, Text2);
    fflush(m_File);
}


// Textout with one parameter
void CFile::Textout(const char *Text, int x, ...)
{
	fprintf(m_File, Text, x);
	fflush(m_File);
}

// Textout with one parameter and flag
void CFile::Textout(const char *Text, int x, int flag, ...)
{
	switch (flag)
	{
		default:
			break;
	}

	fprintf(m_File, Text, x);
	fflush(m_File);
}

// Textout with two parameter and flag
void CFile::Textout(const char *Text, int x, int y, int flag, ...)
{
	fprintf(m_File, Text, x, y);
	fflush(m_File);
}

// CCreateBasic: Create a basic file for starting
void CFile::CCreateBasic(const char *FileName)
{
	Textout("Music: 50%\r\n");
	Textout("Graphic: 800 x 600\r\n");
	Textout("Full Screen: 0 (false)\r\n");
}

// COpenFile: Open the file for write and read.
void CFile::COpenFile(const char *FileName)
{
	if (CSettingsExist(FileName) == false)
	{
		CCreateSetting(FileName);
	}
	else
	{
		m_File = fopen(FileName, "a");
	}
}

// Read functions

// CReadMusic: 	Read the actually value of Music to see on window
int CFile::CReadMusic()
{
	int Music = 0;
	fopen("settings.txt", "r");


	return Music;
}

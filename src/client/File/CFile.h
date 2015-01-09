/*			Write and Read data to file for settings or some
*			another think.
*
*			
*/
#ifndef __CFILE
#define __CFILE


#include <iostream>
#include <stdio.h>

#define MAX_BUFFER_SIZE	1024 // 2048

class CFile
{
	public:
		CFile();
		~CFile();
		inline bool CSettingsExist(const char *Name);
		void CCreateSetting(const char *FileName);
		void CWriteMusic(int Music);
		void CWriteGraphic(int x, int y);
		void CWriteFullScr(int FullScr);
		int CReadMusic();
		int CReadGraphic();
		int CReadFullScr();
		void Textout(const char *Text);
        void sTextout(const wchar_t *Text2, ...);
		void Textout(const char *Text, int x, ...);
		void Textout(const char *Text, int x, int flag, ...);
		void Textout(const char *Text, int x, int y, int flag, ...);
        void Textout(const char *Text, const char *Text2, ...);
        void wTextout(const char *Text, const wchar_t *Text2, ...);
        void wTextout(const wchar_t *Text2, ...);
        void wTextout(const wchar_t *Text2[], ...);
		void CCreateBasic(const char *FileName);
		void COpenFile(const char *FileName);
        void CCreateFile(const char *FileName);

	private:
		FILE *m_File;

};



#endif __CFILE
#pragma once

#include <stdlib.h>


#define VTBL( classptr ) (*(DWORD*)classptr)
#define PVFN_( classptr , offset ) (VTBL( classptr ) + offset)
#define VFN_( classptr , offset ) *(DWORD*)PVFN_( classptr , offset )
#define PVFN( classptr , offset ) PVFN_( classptr , ( offset * sizeof(void*) ) )
#define VFN( classptr , offset ) VFN_( classptr , ( offset * sizeof(void*) ) )

#define DETOUR_TYPE_OBS_ADD				11
#define DETOUR_TYPE_OBS_XOR				12
#define DETOUR_TYPE_OBS_STACKADD		13
#define DETOUR_TYPE_OBS_ROR				14
#define DETOUR_TYPE_OBS_ADDNOT			15

#define DetourRandTypeLow				DETOUR_TYPE_OBS_ADD
#define DetourRandTypeHigh				DETOUR_TYPE_OBS_ADDNOT


class CVirtualCallGate 
{
public:

	void Build( void *pOrigFunc, void *pNewFunc, void* pOrgFuncCaller, bool bIsD3D )
	{
		int iTmpRnd = (rand() * 0xFF) + rand();
		DWORD dwNewFunc = (DWORD)pNewFunc;
		DWORD dwOrgFunc = (DWORD)pOrigFunc;

		memset(m_szGate, 0x90, sizeof(m_szGate));

		if(!bIsD3D)
		{
			m_szGate[0] = '\x58';
			m_szGate[1] = '\x51';
			m_szGate[2] = '\x50';
		}

		m_iPatchType = (rand() % (DetourRandTypeHigh - DetourRandTypeLow + 1) + DetourRandTypeLow);

		if(m_iPatchType == DETOUR_TYPE_OBS_ADD)
		{
			m_szGate[3] = '\xB8';
			*(DWORD*)&m_szGate[4] = iTmpRnd;
			m_szGate[8] = '\x05';
			*(int*)&m_szGate[9] = dwNewFunc - iTmpRnd;
			m_szGate[13] = '\xFF';
			m_szGate[14] = '\xE0';

			*(DWORD*)pOrgFuncCaller = (DWORD)&m_szGate[15];
			iTmpRnd = (rand() * 0xFF) + rand();

			if(!bIsD3D)
			{
				m_szGate[15] = '\x58';
				m_szGate[16] = '\x59';
				m_szGate[17] = '\x50';
			}

			m_szGate[18] = '\xB8';
			*(DWORD*)&m_szGate[19] = iTmpRnd;
			m_szGate[23] = '\x05';
			*(int*)&m_szGate[24] = dwOrgFunc - iTmpRnd;
			m_szGate[28] = '\xFF';
			m_szGate[29] = '\xE0';
		}

		else if(m_iPatchType == DETOUR_TYPE_OBS_XOR)
		{
			m_szGate[3] = '\x33';
			m_szGate[4] = '\xC0';
			m_szGate[5] = '\x2D';
			*(int*)&m_szGate[6] = (int)iTmpRnd;
			m_szGate[10] = '\x35';
			*(DWORD*)&m_szGate[11] = dwNewFunc ^ (-iTmpRnd);
			m_szGate[15] = '\xFF';
			m_szGate[16] = '\xE0';

			*(DWORD*)pOrgFuncCaller = (DWORD)&m_szGate[17];
			iTmpRnd = (rand() * 0xFF) + rand();

			if(!bIsD3D)
			{
				m_szGate[17] = '\x58';
				m_szGate[18] = '\x59';
				m_szGate[19] = '\x50';
			}

			m_szGate[20] = '\x33';
			m_szGate[21] = '\xC0';
			m_szGate[22] = '\x2D';
			*(int*)&m_szGate[23] = (int)iTmpRnd;
			m_szGate[27] = '\x35';
			*(DWORD*)&m_szGate[28] = dwOrgFunc ^ (-iTmpRnd);
			m_szGate[32] = '\xFF';
			m_szGate[33] = '\xE0';
		}

		else if(m_iPatchType == DETOUR_TYPE_OBS_STACKADD)
		{
			m_szGate[3] = '\x68';
			*(DWORD*)&m_szGate[4] = (DWORD)iTmpRnd;
			m_szGate[8] = '\x81';
			m_szGate[9] = '\x34';
			m_szGate[10] = '\x24';
			*(DWORD*)&m_szGate[11] = dwNewFunc ^ iTmpRnd;
			m_szGate[15] = '\xC3';

			*(DWORD*)pOrgFuncCaller = (DWORD)&m_szGate[16];
			iTmpRnd = (rand() * 0xFF) + rand();

			if(!bIsD3D)
			{
				m_szGate[16] = '\x58';
				m_szGate[17] = '\x59';
				m_szGate[18] = '\x50';
			}

			m_szGate[19] = '\x68';
			*(DWORD*)&m_szGate[20] = (DWORD)iTmpRnd;
			m_szGate[24] = '\x81';
			m_szGate[25] = '\x34';
			m_szGate[26] = '\x24';
			*(DWORD*)&m_szGate[27] = dwOrgFunc ^ iTmpRnd;
			m_szGate[31] = '\xC3';
		}

		else if(m_iPatchType == DETOUR_TYPE_OBS_ROR)
		{
			BYTE bTmpRnd = 0;

			while (!(bTmpRnd % 32)) bTmpRnd = (BYTE)rand();

			__asm
			{
				pushad;
				mov cl, bTmpRnd;
				mov eax, dwNewFunc;
				rol eax, cl;
				mov dword ptr dwNewFunc, eax;
				popad;
			}

			m_szGate[3] = '\x51';
			m_szGate[4] = '\xB1';
			m_szGate[5] = bTmpRnd;
			m_szGate[6] = '\xB8';
			*(DWORD*)&m_szGate[7] = dwNewFunc;
			m_szGate[11] = '\xD3';
			m_szGate[12] = '\xC8';
			m_szGate[13] = '\x59';
			m_szGate[14] = '\xFF';
			m_szGate[15] = '\xE0';
			*(DWORD*)pOrgFuncCaller = (DWORD)&m_szGate[16];

			if(!bIsD3D)
			{
				m_szGate[16] = '\x58';
				m_szGate[17] = '\x59';
				m_szGate[18] = '\x50';
			}

			while (!(bTmpRnd % 32)) bTmpRnd = (BYTE)rand();

			__asm
			{
				pushad;
				mov cl, bTmpRnd;
				mov eax, dwOrgFunc;
				rol eax, cl;
				mov dword ptr dwOrgFunc, eax;
				popad;
			}

			m_szGate[19] = '\x51';
			m_szGate[20] = '\xB1';
			m_szGate[21] = bTmpRnd;
			m_szGate[22] = '\xB8';
			*(DWORD*)&m_szGate[23] = dwOrgFunc;
			m_szGate[27] = '\xD3';
			m_szGate[28] = '\xC8';
			m_szGate[29] = '\x59';
			m_szGate[30] = '\xFF';
			m_szGate[31] = '\xE0';
		}

		else if(m_iPatchType == DETOUR_TYPE_OBS_ADDNOT)
		{
			m_szGate[3] = '\xB8';
			*(DWORD*)&m_szGate[4] = iTmpRnd;
			m_szGate[8] = '\x05';
			*(int*)&m_szGate[9] = (~dwNewFunc) - iTmpRnd;
			m_szGate[13] = '\xF7';
			m_szGate[14] = '\xD0';
			m_szGate[15] = '\xFF';
			m_szGate[16] = '\xE0';

			*(DWORD*)pOrgFuncCaller = (DWORD)&m_szGate[17];
			iTmpRnd = (rand() * 0xFF) + rand();

			if(!bIsD3D)
			{
				m_szGate[18] = '\x58';
				m_szGate[19] = '\x59';
				m_szGate[20] = '\x50';
			}

			m_szGate[21] = '\xB8';
			*(DWORD*)&m_szGate[22] = iTmpRnd;
			m_szGate[26] = '\x05';
			*(int*)&m_szGate[27] = (~dwOrgFunc) - iTmpRnd;
			m_szGate[31] = '\xF7';
			m_szGate[32] = '\xD0';
			m_szGate[33] = '\xFF';
			m_szGate[34] = '\xE0';
		}
	}

	DWORD Gate( void )
	{
		return (DWORD)&m_szGate[0];
	}

	int Index( const char *fmt, ... )
	{
		va_list	va_alist;
		char buf[32];

		memset(buf, 0, sizeof(buf));

		va_start(va_alist, fmt);
    	vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char *op = (char *)strtoul(buf, NULL, 16);

		while(1)
		{
			if(*op == '\xFF')
			{
				op++;

				if(*op == '\xA0')
				{
					int iIndex = 0;

					op++;
					memcpy(&iIndex, op, (4));
					return (iIndex / 4);
				}

				op++;
				break;
			}

			op++;
		}

		return ((int)*op) / 4;
	}

	void DeProtect( void *pMemory, UINT uiLen )
	{
		VirtualProtect(pMemory, uiLen, PAGE_EXECUTE_READWRITE, &m_dwProt);
	}

	void ReProtect( void *pMemory, UINT uiLen )
	{
		VirtualProtect(pMemory, uiLen, m_dwProt, &m_dwProt);
	}

private:

	char	m_szGate[35];
	DWORD	m_dwProt;
	int		m_iPatchType;
};

#define EXTDEFVFUNC( funcname , returntype , proto ) \
	typedef returntype ( WINAPI * funcname##Func ) proto ; \
	extern funcname##Func funcname; \
	extern CVirtualCallGate funcname##Gate;

#define DEFVFUNC( funcname , returntype , proto ) \
	typedef returntype ( WINAPI * funcname##Func ) proto ; \
	funcname##Func funcname = NULL; \
	CVirtualCallGate funcname##Gate;

#define HOOKD3DVFUNC( class, classptr , classfunc , funcname , newfunc ) \
	funcname##Gate.DeProtect((void*)VTBL( classptr ), ( funcname##Gate.Index("%p", & class :: classfunc) * sizeof(void*)) + 4 ); \
	funcname##Gate.Build((void*)VFN( classptr , funcname##Gate.Index("%p", & class :: classfunc) ), newfunc , & funcname, true ); \
	*(DWORD*)PVFN( classptr , funcname##Gate.Index("%p", & class :: classfunc) ) = funcname##Gate.Gate(); \
	funcname##Gate.ReProtect((void*)VTBL( classptr ), ( funcname##Gate.Index("%p", & class :: classfunc) * sizeof(void*)) + 4 );
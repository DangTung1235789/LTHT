#pragma once
#define NUMLINES ((int) (sizeof sysmetrics / sizeof sysmetrics [0]))
struct
{
	const TCHAR* szLabel;
	const TCHAR* szDesc;
}
sysmetrics[] =
{
	TEXT("SM_CXSCREEN"),TEXT("Screen width in pixels"),
	TEXT("SM_CYSCREEN"),TEXT("Screen height in pixels")
};

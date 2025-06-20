#include "DuckDBCommon.h"


void CpyDuckdbString(char* data, duckdb_string_t& str)
{
	if (duckdb_string_is_inlined(str))
	{
		strcpy(data, str.value.inlined.inlined);
	}
	else
	{
		strcpy(data, str.value.pointer.ptr);
	}
}

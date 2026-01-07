#pragma once
#include "MdbStructs.h"

namespace mdb
{
	struct MdUserLoginSessionEqualForMdUserIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionLessForMdUserIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	
}

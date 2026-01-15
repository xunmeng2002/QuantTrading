#pragma once
#include "MdbStructs.h"

namespace mdb
{
	struct InstrumentEqualForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	struct InstrumentLessForExchangeIDIndex
	{
		bool operator()(const Instrument* const left, const Instrument* const right) const;
	};
	
	struct MdUserLoginSessionEqualForMdUserIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	struct MdUserLoginSessionLessForMdUserIDIndex
	{
		bool operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const;
	};
	
}

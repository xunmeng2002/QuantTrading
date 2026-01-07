#include "MdbIndexComp.h"
#include <string.h>


namespace mdb
{
	bool MdUserLoginSessionEqualForMdUserIDIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		return strcmp(left->MdUserID, right->MdUserID) == 0;
	}
	bool MdUserLoginSessionLessForMdUserIDIndex::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		if (strcmp(left->MdUserID, right->MdUserID) < 0)
			return true;
		else if (strcmp(left->MdUserID, right->MdUserID) > 0)
			return false;
		return false;
	}
	
}

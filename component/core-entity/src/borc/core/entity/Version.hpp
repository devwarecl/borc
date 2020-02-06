
#pragma once 

namespace borc::core::entity {
	struct Version {
		int major;
		int minor;
		int revision;

        bool operator == (const Version &rhs) const;
	};
}
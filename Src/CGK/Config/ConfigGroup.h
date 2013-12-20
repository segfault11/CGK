#ifndef CONFIGGROUP_H
#define CONFIGGROUP_H

#include <string>
#include "ConfigEntry.h"

class CGKConfigGroup 
{
public:
    CGKConfigGroup(const std::string& name);
    virtual ~CGKConfigGroup();

	void AddEntry(const CGKConfigEntry& entry);

	std::string GetName() const;
	const CGKConfigEntry* GetEntryWithName(const std::string& name) const;	

private:
	class RealConfigGroup;
	RealConfigGroup* group;
};

#endif /* end of include guard: CONFIGGROUP_H */

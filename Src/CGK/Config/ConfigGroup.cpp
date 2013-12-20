//-----------------------------------------------------------------------------
#include "ConfigGroup.h"
#include <list>
//-----------------------------------------------------------------------------
class CGKConfigGroup::RealConfigGroup
{
public:
	RealConfigGroup(const std::string& name);
	virtual ~RealConfigGroup();

	void AddEntry(const CGKConfigEntry& entry);

	std::string GetName() const;
	const CGKConfigEntry* GetEntryWithName(const std::string& name) const;	

private:
	std::string name;
	std::list<const CGKConfigEntry*> entries;
};
//-----------------------------------------------------------------------------
CGKConfigGroup::RealConfigGroup::RealConfigGroup(const std::string& name)
: name(name)
{
	
}
//-----------------------------------------------------------------------------
CGKConfigGroup::RealConfigGroup::~RealConfigGroup()
{

}
//-----------------------------------------------------------------------------
void CGKConfigGroup::RealConfigGroup::AddEntry(const CGKConfigEntry& entry)
{
	this->entries.push_back(&entry);
}
//-----------------------------------------------------------------------------
std::string CGKConfigGroup::RealConfigGroup::GetName() const
{
	return this->name;
}
//-----------------------------------------------------------------------------
const CGKConfigEntry* CGKConfigGroup::RealConfigGroup::GetEntryWithName(
	const std::string& name
) const
{
	for (const CGKConfigEntry* entry : this->entries)
	{
		if (!entry->GetName().compare(name))
		{
			return entry;
		}	
	}

	return NULL;
}
//-----------------------------------------------------------------------------
// ConfigGroups's definition
//-----------------------------------------------------------------------------
CGKConfigGroup::CGKConfigGroup(const std::string& name)
{
	this->group = new RealConfigGroup(name);
}
//-----------------------------------------------------------------------------
CGKConfigGroup::~CGKConfigGroup()
{

}
//-----------------------------------------------------------------------------
void CGKConfigGroup::AddEntry(const CGKConfigEntry& entry)
{
	this->group->AddEntry(entry);
}
//-----------------------------------------------------------------------------
std::string CGKConfigGroup::GetName() const
{
	return this->group->GetName();
}
//-----------------------------------------------------------------------------
const CGKConfigEntry* CGKConfigGroup::GetEntryWithName(
	const std::string& name
) const
{
	return this->group->GetEntryWithName(name);
}
//-----------------------------------------------------------------------------

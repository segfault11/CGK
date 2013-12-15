//-----------------------------------------------------------------------------
#include <map>
#include <iostream>
#include "ConfigEntry.h"
//-----------------------------------------------------------------------------
class CGKConfigEntry::RealConfigEntry
{
public:
    RealConfigEntry(const std::string& name);
    ~RealConfigEntry();

    std::string GetName() const;
    std::string GetValueForKey(const std::string& key) const;
    
    void SetValueForKey(
        const std::string& key, 
        const std::string& value
    );

private:
    std::string name;
    std::map<std::string, std::string> map;
};
//-----------------------------------------------------------------------------
CGKConfigEntry::RealConfigEntry::RealConfigEntry(const std::string& name)
: name(name)
{

}
//-----------------------------------------------------------------------------
CGKConfigEntry::RealConfigEntry::~RealConfigEntry()
{

}
//-----------------------------------------------------------------------------
std::string CGKConfigEntry::RealConfigEntry::GetName() const
{
    return name;
}
//-----------------------------------------------------------------------------
std::string CGKConfigEntry::RealConfigEntry::GetValueForKey(
    const std::string& key
) const
{
    auto it = this->map.find(key);   

    if (it != this->map.end())
    {
        return it->second;
    }

    return std::string("");
}
//-----------------------------------------------------------------------------
void CGKConfigEntry::RealConfigEntry::SetValueForKey(
    const std::string& key, 
    const std::string& value
)
{
    this->map[key] = value;
}
//-----------------------------------------------------------------------------
//  Definition of CGKConfigEntry's public interfaceke
//-----------------------------------------------------------------------------
CGKConfigEntry::CGKConfigEntry(const std::string& name)
{
    this->entry = new RealConfigEntry(name);
}
//-----------------------------------------------------------------------------
CGKConfigEntry::~CGKConfigEntry()
{
    delete this->entry;
}
//-----------------------------------------------------------------------------
std::string CGKConfigEntry::GetName() const
{
    return this->entry->GetName();
}
//-----------------------------------------------------------------------------
std::string CGKConfigEntry::GetValueForKey(const std::string& key) const
{
    return this->entry->GetValueForKey(key);
}
//-----------------------------------------------------------------------------
void CGKConfigEntry::SetValueForKey(
    const std::string& key, 
    const std::string& value
)
{
    this->entry->SetValueForKey(key, value);
}
//-----------------------------------------------------------------------------


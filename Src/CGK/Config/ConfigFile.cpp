//-----------------------------------------------------------------------------
#include "ConfigFile.h"
#include <list>
#include <cstdio>
#include <fstream>
#include <iostream>
//-----------------------------------------------------------------------------
class CGKConfigFile::RealConfigFile
{
public:
    RealConfigFile(const std::string& filename);
    virtual ~RealConfigFile();

    unsigned int GetNumEntries() const;
	const CGKConfigGroup* GetGroupWithName(const std::string& name) const;
    const CGKConfigEntry* GetEntryWithName(const std::string& name) const;
    const CGKConfigEntry* GetEntryAtIndex(unsigned int index) const;

private:
    void processLine(const std::string& line);

    std::string name;
    std::list<CGKConfigEntry*> entries;        	
	std::list<CGKConfigGroup*> groups;
};
//-----------------------------------------------------------------------------
CGKConfigFile::RealConfigFile::RealConfigFile(const std::string& filename)
{    
    this->entries.push_back(new CGKConfigEntry(""));
   
    std::ifstream file;
    file.open(filename); 
    std::string line;
    
    while(std::getline(file, line))
    {
        this->processLine(line);
    }
    
    file.close();
}
//-----------------------------------------------------------------------------
CGKConfigFile::RealConfigFile::~RealConfigFile()
{
    for (CGKConfigEntry* entry : this->entries)
    {
        delete entry;
    }
	
	for (CGKConfigGroup* group : this->groups)
	{
		delete group;
	}
}
//-----------------------------------------------------------------------------
void CGKConfigFile::RealConfigFile::processLine(const std::string& line)
{
    char name[1024];
    char key[1024];
    char value[1024];

    switch(line.c_str()[0])
    {
	case '^':
        if (std::sscanf(line.c_str(), "^ %s", name) == 1)        
		{
			this->groups.push_back(new CGKConfigGroup(std::string(name)));
		}
    case '@':
        if (std::sscanf(line.c_str(), "@ %s", name) == 1)        
        {
			CGKConfigEntry* entry = new CGKConfigEntry(std::string(name));

            this->entries.push_back(entry);
			
			if (this->groups.size() > 0)
			{
				auto it = this->groups.back();
				it->AddEntry(*entry);
			}
        }
    break;   

    case '*':
        if (2 == std::sscanf(line.c_str(), "* %s %s", key, value)) 
        {
            auto it = this->entries.back();  
            it->SetValueForKey(std::string(key), std::string(value));
        }

    break;
    };
}
//-----------------------------------------------------------------------------
const CGKConfigEntry* CGKConfigFile::RealConfigFile::GetEntryWithName(
    const std::string& name
) const
{
    for (CGKConfigEntry* entry : this->entries)
    {
        if (!entry->GetName().compare(name))
        {
            return entry;
        }
    }    

    return NULL;
}
//-----------------------------------------------------------------------------
const CGKConfigGroup* CGKConfigFile::RealConfigFile::GetGroupWithName(
	const std::string& name
) const
{
	for (CGKConfigGroup* group : this->groups)
	{
        if (!group->GetName().compare(name))
        {
            return group;
        }
	}	
	
	return NULL;
}
//-----------------------------------------------------------------------------
// CGKConfigurationFile's public definition
//-----------------------------------------------------------------------------
CGKConfigFile::CGKConfigFile(const std::string& filename)
{
    this->configFile = new RealConfigFile(filename);
}
//-----------------------------------------------------------------------------
CGKConfigFile::~CGKConfigFile()
{
    delete this->configFile;
}
//-----------------------------------------------------------------------------
const CGKConfigEntry* CGKConfigFile::GetEntryWithName(
    const std::string& name
) const
{
    return this->configFile->GetEntryWithName(name);
}
//-----------------------------------------------------------------------------

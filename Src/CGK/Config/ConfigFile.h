#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <string>
#include "ConfigEntry.h"
#include "ConfigGroup.h"

class CGKConfigFile 
{
public:
    CGKConfigFile(const std::string& filename);
    virtual ~CGKConfigFile();

    unsigned int GetNumEntries() const;

	/// Gets the first ConfigGroup with the name [name]. Returns NULL if there
	/// are no entries that have name [name].
	const CGKConfigGroup* GetGroupWithName(const std::string& name) const;	

    /// Gets the first ConfigEntry with name [name]. Returns NULL if there
    /// are no entries that have name [name].
    const CGKConfigEntry* GetEntryWithName(const std::string& name) const;
    
    // Gets the entry at [index] position or NULL if [index] is greater or
    // equal to the total number or entries.    
    const CGKConfigEntry* GetEntryAtIndex(unsigned int index) const;
private:
    CGKConfigFile(const CGKConfigFile& orig); 
    CGKConfigFile& operator=(const CGKConfigFile& orig);

    class RealConfigFile;
    RealConfigFile* configFile;
};

#endif /* end of include guard: CONFIGFILE_H */

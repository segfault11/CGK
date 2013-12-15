#ifndef CONFIGENTRY_H
#define CONFIGENTRY_H

#include <string>

class CGKConfigEntry 
{
public:
    CGKConfigEntry(const std::string& name);
    virtual ~CGKConfigEntry();

    std::string GetName() const;
    std::string GetValueForKey(const std::string& key) const;
    
    void SetValueForKey(
        const std::string& key, 
        const std::string& value
    );

private:
    class RealConfigEntry;
    RealConfigEntry* entry;
};

#endif /* end of include guard: CONFIGENTRY_H */

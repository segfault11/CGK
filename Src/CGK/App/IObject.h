#ifndef IOBJECT_H__
#define IOBJECT_H__
 

    class CGKAppIObject
    {
    public:
        CGKAppIObject() {};
        ~CGKAppIObject() {};
    
        /// This function is called by the application before the main loop.
        virtual void Start();

        /// This function is called by the application when the main loop exits
        virtual void End();

        /// This function is called by the application at every iteration of 
        /// the main loop.
        virtual void Update();
    };
 
#endif /* end of include guard: IOBJECT_H__ */
#ifndef ERROR_H__
#define ERROR_H__

#define CGK_REPORT(x, y) CGKErrorReport(__FILE__, __LINE__, x, y);
#define CGK_ASSERT(x) if (x) {} else {CGKErrorAssert(#x, __FILE__, __LINE__);}

// Error Codes
enum
{
    CGK_NO_ERROR = 0,
    CGK_GL_ERROR,
    CGK_FILE_NOT_FOUND,
    CGK_INVALID_FILE,
    CGK_INVALID_TEXTURE,
    CGK_INVALID_ARGUMENTS,
    CGK_NOT_ENOUGH_MEMORY,
    CGK_UNKNOWN_ERROR
};

void CGKErrorReport(const char* filename, int line, const char* message, int code);
void CGKErrorAssert(const char* expr, const char* filename, int line);

#endif /* end of include guard: ERROR_H__ */

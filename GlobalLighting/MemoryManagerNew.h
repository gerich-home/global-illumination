#pragma once

#if USE_MEMORY_MANAGER
extern const char* __file__;
extern size_t __line__;
#define new (__file__=__FILE__,__line__=__LINE__) && 0 ? NULL : new
#endif
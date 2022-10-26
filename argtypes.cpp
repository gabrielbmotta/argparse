#include "argtypes.h"
#ifdef __cplusplus
arg::arg(arg_type in_t, void* in_value, const char * in_argument, const char * in_short_argument, const char * in_description)
: t(in_t)
, value(in_value)
, argument(in_argument)
, short_argument(in_short_argument)
, description(in_description)  
{
}
#endif
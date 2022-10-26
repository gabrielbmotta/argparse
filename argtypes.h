#ifndef ARG_PARSE_LIB_ARGTYPES
#define ARG_PARSE_LIB_ARGTYPES

typedef enum arg_type{
    int_arg,
    float_arg,
    string_arg,
    bool_arg
} arg_type;

typedef struct arg{
    arg_type t;
    void* value;
    const char * argument;
    const char * short_argument;
    const char * description;

#ifdef __cplusplus
    arg(arg_type in_t = string_arg,
        void* in_value = nullptr,
        const char * in_argument = "",
        const char * in_short_argument = "",
        const char * in_description = "");
#endif
} arg;

#endif
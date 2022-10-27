#ifndef ARG_PARSE_LIB_ARGPARSE
#define ARG_PARSE_LIB_ARGPARSE

typedef enum arg_type{
    int_arg,
    float_arg,
    string_arg,
    bool_arg
} arg_type;

typedef enum arg_parse_status{
    success,
    help,
    error
} arg_parse_status;

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

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

typedef void* arg_parser_t;

EXTERNC arg_parser_t create_arg_parser(char* name, char* version);
EXTERNC arg_parser_t create_nameless_arg_parser();
EXTERNC void add_argument(arg_parser_t parser, arg* input_arg);
EXTERNC arg_parse_status parse_args(arg_parser_t parser, int argc, char* argv[]);
EXTERNC void print_errors(arg_parser_t parser);
EXTERNC void delete_parser(arg_parser_t parser);

#undef EXTERNC

#ifdef __cplusplus

#include <vector>
#include <string>

class ArgParser{
public:
    ArgParser(const char* = "", const char* app_version = "");
    void addArgument(const arg& input_arg);
    arg_parse_status parseArguments(int in_argc, char* in_argv[]);
    bool helpMode();

    void printErrors();
private:
    void printHelpText();
    void parseLongArg(int index);
    void parseShortArg(int index);
    void parseDefaultArg(int index);

    void setArgValue(arg& argument, int index);

    int argc;
    char** argv;

    bool next_read;

    const char* name;
    const char* version;

    bool help;

    std::vector<arg> args;
    std::vector<std::string> error_status;
};

#endif // __cplusplus
#endif // ARG_PARSE_LIB_ARGPARSE
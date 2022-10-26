#ifndef ARG_PARSE_LIB_ARGPARSE
#define ARG_PARSE_LIB_ARGPARSE

#include "argtypes.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

typedef void* arg_parser_t;

EXTERNC arg_parser_t create_arg_parser(char* name, char* version);
EXTERNC arg_parser_t create_nameless_arg_parser();
EXTERNC void add_argument(arg_parser_t parser, arg* input_arg);
EXTERNC void parse_args(arg_parser_t parser, int argc, char* argv[]);
EXTERNC void delete_parser(arg_parser_t parser);

#undef EXTERNC

#ifdef __cplusplus

#include <vector>
#include <string>

class ArgParser{
public:
    ArgParser(const char* = "", const char* app_version = "");
    void addArgument(const arg& input_arg);
    bool parseArguments(int in_argc, char* in_argv[]);
    bool helpMode();

    void printErrors();
private:
    void printHelpText();
    void parseLongArg(int index);
    void parseShortArg(int index);

    void setArgValue(arg& argument, int index);

    int argc;
    char** argv;

    const char* name;
    const char* version;

    bool help;

    std::vector<arg> args;
    std::vector<std::string> error_status;
};

#endif // __cplusplus
#endif // ARG_PARSE_LIB_ARGPARSE
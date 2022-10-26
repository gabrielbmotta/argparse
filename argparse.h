#ifndef ARG_PARSE_LIB_ARGPARSE
#define ARG_PARSE_LIB_ARGPARSE

#include "argtypes.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

typedef void* arg_parser_t;

EXTERNC arg_parser_t create_arg_parser();
EXTERNC void add_argument(arg_parser_t parser, arg* input_arg);
EXTERNC void parse_args(arg_parser_t parser, int argc, char* argv[]);
EXTERNC void delete_parser(arg_parser_t parser);

#undef EXTERNC

#ifdef __cplusplus

#include <vector>
#include <string>

class ArgParser{
public:
    ArgParser();
    ArgParser(std::string app_name, std::string app_version = "");
    void addArgument(const arg& input_arg);
    bool parseArguments(int in_argc, char* in_argv[]);

    void printErrors();
private:
    void parseLongArg(int index);
    void parseShortArg(int index);

    void setArgValue(arg& argument, int index);

    int argc;
    char** argv;

    std::vector<arg> args;
    std::vector<std::string> error_status;
};

#endif // __cplusplus
#endif // ARG_PARSE_LIB_ARGPARSE
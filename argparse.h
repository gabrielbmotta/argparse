/**
MIT License

Copyright (c) 2022 Gabriel Motta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

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

typedef struct cmdl_arg{
    arg_type t;
    void* value;
    const char * argument;
    const char * short_argument;
    const char * description;

#ifdef __cplusplus
    cmdl_arg(arg_type in_t = string_arg,
        void* in_value = nullptr,
        const char * in_argument = "",
        const char * in_short_argument = "",
        const char * in_description = "");
#endif
} cmdl_arg;

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

typedef void* arg_parser_t;

EXTERNC arg_parser_t create_arg_parser(char* name, char* version);
EXTERNC arg_parser_t create_nameless_arg_parser();
EXTERNC void delete_parser(arg_parser_t parser);

EXTERNC void add_argument(arg_parser_t parser, cmdl_arg* input_arg);
EXTERNC arg_parse_status parse_args(arg_parser_t parser, int argc, char* argv[]);

EXTERNC void print_errors(arg_parser_t parser);
EXTERNC void print_help(arg_parser_t parser);

#undef EXTERNC

#ifdef __cplusplus

#include <vector>
#include <string>

class ArgParser{
public:
    ArgParser(const char* = "", const char* app_version = "");

    void addArgument(const cmdl_arg& input_arg);
    arg_parse_status parseArguments(int in_argc, char* in_argv[]);

    void printErrors();
    void printHelpText();
private:
    void parseLongArg(int index);
    void parseShortArg(int index);
    void parseDefaultArg(int index);

    void setArgValue(cmdl_arg& argument, int index);

    int _argc;
    char** _argv;

    bool _next_read;
    bool _help;

    const char* _name;
    const char* _version;

    std::vector<cmdl_arg> _registered_args;
    std::vector<std::string> _error_msgs;
};

#endif // __cplusplus
#endif // ARG_PARSE_LIB_ARGPARSE
#ifndef __cplusplus
    #error C++ compiler required.
#endif

#include "argparse.h"
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

void composeString(std::string& str){
    
}

template<typename T, typename... Types>
void composeString(std::string& str, T var1, Types... var2){
    str += var1;

    composeString(str, var2...);
} 

template<typename... Types>
void addToStringList(std::vector<std::string>& vec, Types... var){
    std::string s;
    composeString(s, var...);

    vec.push_back(s);
}


cmdl_arg::cmdl_arg(arg_type in_t, void* in_value, const char * in_argument, const char * in_short_argument, const char * in_description)
: t(in_t)
, value(in_value)
, argument(in_argument)
, short_argument(in_short_argument)
, description(in_description)  
{
}

ArgParser::ArgParser(const char* app_name, const char* app_version)
: _name(app_name)
, _version(app_version)
, _next_read(false)
, _help(false)
{

}

void ArgParser::addArgument(const cmdl_arg& input_arg)
{
    _registered_args.push_back(input_arg);
}

arg_parse_status ArgParser::parseArguments(int in_argc, char* in_argv[])
{
    this->_argc = in_argc;
    this->_argv = in_argv;
    
    for(int i = 1; i < _argc; ++i){
        _next_read = false;
        if(!std::strcmp("--help", _argv[i])){
            printHelpText();
            _help = true;
            continue;
        }
        auto len = std::strlen(_argv[i]);
        if(len > 1 && _argv[i][0] == '-'){
            if(len > 2 && _argv[i][1] == '-'){
                parseLongArg(i);
            }
            else {
                parseShortArg(i);
            }
        } else {
            parseDefaultArg(i);
        }
        if(_next_read){
            ++i;
        }
    }

    if(_help){
        return arg_parse_status::help;
    } else if (_error_msgs.empty()){
        return arg_parse_status::success;
    } else {
        return arg_parse_status::error;
    }

}

void ArgParser::printErrors()
{
    for (auto& str : _error_msgs){
        std::cout << str << "\n";
    }
}

void ArgParser::printHelpText()
{
    std::cout << _name << " " << _version << "\n";
    for (auto& argument : _registered_args){
        std::cout << argument.argument << ", " << argument.short_argument << "\t\t" << argument.description << "\n";
    }
    std::cout << "\n--help \t\tShow this help text.";
}

void ArgParser::parseLongArg(int index)
{
    for(auto& argument : _registered_args){
        if(!std::strcmp(argument.argument, _argv[index])){
            setArgValue(argument, index);
            return;
        }
    }
    addToStringList(_error_msgs, "Argument not recognized [ ", _argv[index], " ]");
}

void ArgParser::parseShortArg(int index)
{
    auto len = std::strlen(_argv[index]);
    if(len == 2){
        for(auto& argument : _registered_args){
            if(!std::strcmp(argument.short_argument, _argv[index])){
                setArgValue(argument, index);
                return;
            }
        }
        addToStringList(_error_msgs, "Argument not recognized [ ", _argv[index], " ]");
    } else if(len > 2){
        for(auto i = 1; i < len; ++i){
            bool found = false;
            char c = _argv[index][i];
            for(auto& argument : _registered_args){
                if(argument.short_argument[1] == c){
                    setArgValue(argument, index);
                    found = true;
                    break;
                }
            }
            if(!found){
                addToStringList(_error_msgs, "Argument not recognized [ ", _argv[index], " ] in [ ", _argv[index], " ]");
            }
        }
    }
}

void ArgParser::parseDefaultArg(int index)
{
    for(auto& argument : _registered_args){
        if(!std::strlen(argument.argument) && !std::strlen(argument.short_argument)){
            setArgValue(argument, index);
            return;
        } else {
            addToStringList(_error_msgs, "Not expecting unnamed argument [ ", _argv[index], " ]");
        }
    }
}


void ArgParser::setArgValue(cmdl_arg& argument, int index)
{
    switch (argument.t) {
    case int_arg:{
        if(index + 1 < _argc){
            auto* value = reinterpret_cast<int*>(argument.value);
            char* idx;
            *value = std::strtol(_argv[index + 1], &idx, 10);
            if(_argv[index+1] + std::strlen(_argv[index+1]) != idx ){
                addToStringList(_error_msgs, "Unable to interpet input ", _argv[index + 1], " as int input to ", argument.argument, ", ", argument.short_argument);

            }
            _next_read = true;
        } else {
            addToStringList(_error_msgs, "No argument provided for ", argument.argument,", ",argument.short_argument);
        }
        break;
    }

    case float_arg:{
        if(index + 1 < _argc){
            auto* value = reinterpret_cast<float*>(argument.value);
            char* idx;
            *value = std::strtof(_argv[index + 1], &idx);
            if(*idx != '\0'){
                addToStringList(_error_msgs, "Unable to interpet input ", _argv[index + 1], " as float input to ", argument.argument, ", ", argument.short_argument);
            }
            _next_read = true;
        } else {
            addToStringList(_error_msgs, "No argument provided for ", argument.argument,", ",argument.short_argument);
        }
        break;
    }

    case string_arg:{
        if(index + 1 < _argc){
            auto* value = reinterpret_cast<const char*>(argument.value);
            size_t* idx;
            value = _argv[index + 1];
            _next_read = true;
        } else {
            addToStringList(_error_msgs, "No argument provided for ", argument.argument,", ",argument.short_argument);
        }
        break;
    }
    case bool_arg:{
        auto* value = reinterpret_cast<bool*>(argument.value);
        *value = true;
        break;
    }
    }
}

// C bindings

arg_parser_t create_arg_parser(char* name, char* version)
{
    return new ArgParser(name, version);
}

arg_parser_t create_nameless_arg_parser()
{
    return new ArgParser();
}

void delete_parser(arg_parser_t parser)
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    delete my_parser;
}

void add_argument(arg_parser_t parser, cmdl_arg* input_arg)
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    my_parser->addArgument(*input_arg);
}

arg_parse_status parse_args(arg_parser_t parser, int argc, char* argv[])
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    return my_parser->parseArguments(argc, argv);
}

void print_errors(arg_parser_t parser)
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    my_parser->printErrors();
}

void print_help(arg_parser_t parser)
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    my_parser->printHelpText();
}

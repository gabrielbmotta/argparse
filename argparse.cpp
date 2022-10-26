#ifndef __cplusplus
    #error C++ compiler required.
#endif

#include "argparse.h"
#include "argtypes.h"
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>


ArgParser::ArgParser()
{

}

ArgParser::ArgParser(std::string app_name, std::string app_version)
{

}

void ArgParser::addArgument(const arg& input_arg)
{
    args.push_back(input_arg);
}

bool ArgParser::parseArguments(int in_argc, char* in_argv[])
{
    this->argc = in_argc;
    this->argv = in_argv;
    
    for(int i = 1; i < argc; ++i){
        auto len = std::strlen(argv[i]);
        if(len > 1 && argv[i][0] == '-'){
            if(len > 2 && argv[i][1] == '-'){
                parseLongArg(i);
            }
            else {
                parseShortArg(i);
            }
        }
    }

    return error_status.empty();
}

void ArgParser::printErrors()
{
    for (auto& str : error_status){
        std::cout << str << "\n";
    }
}

void ArgParser::parseLongArg(int index)
{
    for(auto& argument : args){
        if(!std::strcmp(argument.argument, argv[index])){
            setArgValue(argument, index);
        }
    }
}

void ArgParser::parseShortArg(int index)
{
    auto len = std::strlen(argv[index]);
    if(len == 2){
        for(auto& argument : args){
            if(!std::strcmp(argument.short_argument, argv[index])){
                setArgValue(argument, index);
            }
        }
    } else {
        for(auto i = 1; i < len; ++i){
            for(auto& argument : args){
                if(!std::strcmp(argument.short_argument, argv[index])){
                    setArgValue(argument, index);
                }
            }
        }
    }

}

void ArgParser::setArgValue(arg& argument, int index)
{
    switch (argument.t) {
    case int_arg:{
        if(index + 1 < argc){
            auto* value = reinterpret_cast<int*>(argument.value);
            char* idx;
            *value = std::strtol(argv[index + 1], &idx, 10);
            if(*idx != '\0'){
                std::string err;
                err += "Unable to interpet input ";
                err += argv[index + 1];
                err += " as integer input to ";
                err += argument.argument;
                error_status.push_back(err);
            }
        }
        break;
    }

    case float_arg:{
        if(index + 1 < argc){
            auto* value = reinterpret_cast<float*>(argument.value);
            char* idx;
            *value = std::strtof(argv[index + 1], &idx);
            if(*idx != '\0'){
                std::string err;
                err += "Unable to interpet input ";
                err += argv[index + 1];
                err += " as float input to ";
                err += argument.argument;
                error_status.push_back(err);
            }
        }
        break;
    }

    case string_arg:{
        if(index + 1 < argc){
            auto* value = reinterpret_cast<const char*>(argument.value);
            size_t* idx;
            value = argv[index + 1];
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

arg_parser_t create_arg_parser()
{
    return new ArgParser();
}

void add_argument(arg_parser_t parser, arg* input_arg)
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    my_parser->addArgument(*input_arg);
}

void parse_args(arg_parser_t parser, int argc, char* argv[])
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    my_parser->parseArguments(argc, argv);
}

void delete_parser(arg_parser_t parser)
{
    auto* my_parser = static_cast<ArgParser*>(parser);
    delete my_parser;
}
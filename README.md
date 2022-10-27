# argparse

An opinionated command line input parsing tool.

Partially an example for myself on how to call C++ code in C. Partially a way to parse cmd line inputs the way I like to pass in command line inputs.

## Supported arguments

### GNU-style multi-letter arguments

`
my_app --command
`

### Single letter arguments

`
my_app -i
`

#### Chained single letter arguments

This

`
my_app -i -c -u
`

is equivalent to this

`
my_app -icu
`

and this

`
my_app -a -b 5 -c 5
`

is equivalent to this

`
my_app -abc 5
`

### Default arguments

`my_app command`

## Help command
`--help` will print a list of all known commands with description text.

## How to use

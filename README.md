# argparse

An opinionated command line input parsing tool.

Partially an example for myself on variadic templates and how to call C++ code in C. Partially a way to parse cmd line inputs the way I like to pass in command line inputs.

## Supported arguments

### GNU-style multi-letter arguments

`my_app --command`

`my_app --command 1`

`my_app --command 1.5`

`my_app --command 'something'`

### Single letter arguments

`my_app -i`

`my_app -i 2`

`my_app -i 2.3`

`my_app -i 'something else'`

#### Chained single letter arguments

`my_app -i -c -u` is equivalent to `my_app -icu`

`my_app -a -b 5 -c 5` is equivalent to `my_app -abc 5`

This last behavior might be a bit contentious, as there is some sort of implicit sharing of input arguments (both `b` and `c` are accepting the input 5) while arguments that don't accept arguments will ignore this (like `a` above).

### Default arguments

`my_app command`

## Help command
`--help` will print a list of all known commands with description text.

## Building

```
cmake -B build .
cmake --build build
```

If you don't want the example apps, change `set(EXAMPLES TRUE)` to `set(EXAMPLES FALSE)` in CMakeLists.txt.

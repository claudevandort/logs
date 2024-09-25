# Logging Library Documentation

## Overview

This logging library provides a flexible and easy-to-use interface for adding logging capabilities to C programs. It supports multiple output destinations, customizable formatting options, and different log levels.

## Features

- Multiple log levels
- Output to stdout and/or file
- Customizable log format
- Color-coded console output

## API Reference

### Initialization

```c
void logs_init(int output_flags, const char* log_file_path);
```

#### Parameters

- `output_flags`: This parameter is a bitwise OR of the following flags:
  - `LOG_OUTPUT_STDOUT`: Logs to standard output (stdout).
  - `LOG_OUTPUT_FILE`: Logs to a file specified by `log_file_path`.
  - `LOG_FORMAT_LEVEL`: Logs the log level (`DEBUG`, `INFO`, `WARN`, `ERROR`).
  - `LOG_FORMAT_TIMESTAMP`: Logs the timestamp.
  - `LOG_FORMAT_LOCATION`: Logs the file location.
- `log_file_path`: The path to the file where logs will be written if the `LOG_OUTPUT_FILE` flag is set, if not just set to `0`.

#### Example

A full example can be found in the [src/example.c](src/example.c) file.
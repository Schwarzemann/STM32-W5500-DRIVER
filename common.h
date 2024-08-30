// Define a prefix for the log messages, making it easy to change the prefix in the future.
#define LOG_PREFIX KBUILD_MODNAME ": "

// Define a generic logging format function that takes a format string as input and prepends the log prefix.
#define LOG_FORMAT(fmt) LOG_PREFIX fmt

// Example usage of the LOG_FORMAT macro
#define pr_fmt(fmt) LOG_FORMAT(fmt)

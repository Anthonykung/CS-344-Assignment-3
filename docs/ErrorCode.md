# Error Code Reference

| Error Code Number | Error Description                                      | Common Causes                      |
| ----------------- | ------------------------------------------------------ | ---------------------------------- |
| 0                 | No Error - Success                                     | None                               |
| 1                 | General Error OR Operation not permitted               | Unspecified                        |
| 2                 | Misuse of shell built-ins OR No such file or directory | Missing keyword or command         |
| 3                 | No such process                                        | User input not valid               |
| 4                 | Interrupted system call                                | Control-C                          |
| 5                 | I/O error                                              |                                    |
| 6                 | No such device or address                              |                                    |
| 7                 | Argument list too long                                 |                                    |
| 8                 | Exec format error                                      |                                    |
| 9                 | Bad file number                                        |                                    |
| 10                | No child processes                                     |                                    |
| 11                | Try again                                              |                                    |
| 12                | Out of memory                                          |                                    |
| 13                | Permission denied                                      |                                    |
| 124               | Invalid User Input                                     | User input not valid               |
| 125               | Ignore                                                 | Commented operations               |
| ################# | ###################################################### | ################################## |
| 126               | Command invoked cannot execute                         | Permision issues or not executable |
| 127               | Command not found                                      | Invalid path or command typo       |
| 128               | Invalid exit argument                                  | Exit code not an integer           |
| 128 + n           | System signal 'n'                                      | System signal 'n' called           |
| 129               | System signal 1 - SIGHUP                               | SIGHUP called                      |
| 130               | System signal 2 - SIGINT                               | SIGINT called - Control-C          |
| 131               | System signal 3 - SIGQUIT                              | SIGQUIT called - Control-\         |
| 132               | System signal 4 - SIGILL                               | SIGILL called                      |
| 137               | System signal 9 - SIGKILL                              | SIGKILL called                     |
| 148               | System signal 20 - SIGTSTP                             | SIGTSTP called - Control-Z         |
| 255               | Exit code out of range                                 | Exit code exceed 0 - 255           |

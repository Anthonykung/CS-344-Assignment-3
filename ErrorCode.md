# Error Code Reference

| Error Code Number | Error Description                  | Common Causes                      |
| ----------------- | ---------------------------------- | ---------------------------------- |
| 0                 | No Error - Success                 | None                               |
| 1                 | General Error                      | Unspecified                        |
| 2                 | Misuse of shell built-ins          | Missing keyword or command         |
| 3                 | Invalid Input                      | User input not valid               |
| 125               | Ignore                             | Commented operations               |
| 126               | Command invoked cannot execute     | Permision issues or not executable |
| 127               | Command not found                  | Invalid path or command typo       |
| 128               | Invalid exit argument              | Exit code not an integer           |
| 128 + n           | System signal 'n'                  | System signal 'n' called           |
| 129               | System signal 1 - SIGHUP           | SIGHUP called                      |
| 130               | System signal 2 - SIGINT           | SIGINT called - Control-C          |
| 131               | System signal 3 - SIGQUIT          | SIGQUIT called                     |
| 131               | System signal 4 - SIGILL           | SIGILL called                      |
| 255               | Exit code out of range             | Exit code exceed 0 - 255           |

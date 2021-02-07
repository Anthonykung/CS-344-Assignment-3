# Error Code Reference

| Error Code Number | Error Description              | Common Causes                      |
| ----------------- | ------------------------------ | ---------------------------------- |
| 0                 | No Error - Success             | None                               |
| 1                 | General Error                  | Unspecified                        |
| 2                 | Misuse of shell built-ins      | Missing keyword or command         |
| 3                 | Invalid Input                  | User input not valid               |
| 125               | Ignore                         | Commented operations               |
| 126               | Command invoked cannot execute | Permision issues or not executable |
| 127               | Command not found              | Invalid path or command typo       |
| 128               | Invalid exit argument          | Exit code not an integer           |
| 128 + n           | System signal 'n'              | System signal 'n' called           |
| 130               | System signal 2 - Control-C    | System signal 2 called - Control-C |
| 255               | Exit code out of range         | Exit code exceed 0 - 255           |

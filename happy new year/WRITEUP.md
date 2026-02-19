# Happy New Year Batch Puzzle – Write-Up

## File Information

- **Filename**: `hny.bat`  
- **Type**: Windows Batch Script  
- **Category**: Obfuscation puzzle (not malware, not a classic crackme)

## Challenge Goals

The puzzle asks for two things only:

1. The value of the string  
   `!n!!e!!w! a!n!ch!o!v!y!`
2. How many real batch statements the file contains, and what kinds they are  
   (`set`, `if`, `for`, `goto`, etc.)

---

## Initial Observations

Opening the file in a text editor shows a heavily obfuscated batch script containing:

- Symbolic noise (`! [] {} @$# ★`)
- Long Base64-looking strings
- Output redirection to strange filenames
- A `setlocal EnableDelayedExpansion` statement

At first glance, the script appears complex and suggests hidden logic or decoding steps.

---

## Understanding the Obfuscation

### Delayed Expansion as Misdirection

The script contains:

```bat
setlocal EnableDelayedExpansion
```

This makes expressions like `!var!` look like delayed variable expansion.

However, searching the entire file shows that **no variables named**  
`n`, `e`, `w`, `a`, `ch`, `o`, `v`, or `y` are ever defined using `set`.

In Windows batch scripting:

- `!var!` expands only if the variable exists
- If a variable is undefined, it expands to **nothing**

Despite this, the script visibly prints characters surrounded by `!`, which means these expressions are **not being evaluated**, only **displayed**.

This confirms that the delayed expansion is present only as **psychological misdirection**.

---

## Decoding the Target String

The challenge string is:

```
!n!!e!!w! a!n!ch!o!v!y!
```

Because:
- The variables do not exist
- The line is printed, not computed

The `!` characters serve no functional purpose.

Removing the symbolic noise reveals:

```
new anchovy
```

### Final decoded value

```
new anchovy
```

---

## Statement Analysis

The second part of the challenge is to identify the actual batch statements used.

### Statements present

- `setlocal` (used once)
- Output-only lines (effectively `echo` behavior)

### Statements not present

- No variable assignments (`set`)
- No conditionals (`if`)
- No loops (`for`)
- No jumps (`goto`)
- No subroutine calls (`call`)
- No control flow or logic

The Base64-looking data and output redirections are never referenced again and exist only as false trails.

---

## Conclusion

This puzzle is not about decoding data, extracting payloads, or executing logic.

It tests the ability to:

- Recognize fake complexity
- Understand batch file semantics
- Distinguish between syntax that executes and syntax that is merely printed
- Avoid over-analysis and unnecessary tooling

The correct solution comes from identifying what the script **does not do**, rather than assuming it must do something hidden.

---

## Final Answers

- **Decoded string**:  
  ```
  new anchovy
  ```

- **Script behavior**:
  - Prints obfuscated text only
  - Contains no variables, no logic, and no control flow
  - Safe and non-destructive

---

## Notes

This challenge rewards restraint and understanding over brute-force analysis.  
The obfuscation is the puzzle, not a layer hiding real computation (as per my understanding). 

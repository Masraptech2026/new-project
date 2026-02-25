# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a minimal Python repository. Currently it contains a single file, `task.py`, which is a raw Python IDLE shell session transcript. The meaningful code within it is a `show_system_info()` function that prints platform and datetime information using the standard library modules `platform` and `datetime`.

## Running the code

The actual working function in `task.py` is:

```python
import platform
import datetime

def show_system_info():
    print(f"System: {platform.system()}")
    print(f"Node Name: {platform.node()}")
    print(f"Release: {platform.release()}")
    print(f"Processor: {platform.processor()}")
    print(f"Current Time: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

if __name__ == "__main__":
    show_system_info()
```

To run it as a standalone script, extract and save the clean code above, then:

```bash
python task.py
```

## Notes

- `task.py` is not a valid Python script as-is — it contains raw IDLE shell output including `>>>` prompts and `SyntaxError` lines. It cannot be executed directly with `python task.py`.
- No dependencies beyond the Python standard library are needed.
- No build system, test framework, or package configuration exists in this repo yet.

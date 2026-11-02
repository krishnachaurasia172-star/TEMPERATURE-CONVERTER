# Thermo / Temperature Converter

A small temperature converter with a browser interface and a matching C command-line program. Both support Celsius, Fahrenheit, and Kelvin, and reject temperatures below absolute zero.

## Browser version

Open `index.html` in a browser. The browser runs the interactive converter with JavaScript; browsers do not execute a native C program directly.

## C command-line version

Compile with GCC:

```sh
gcc -std=c11 -Wall -Wextra -Werror temperature.c -o temperature
```

Convert a value by giving the number, source unit, and target unit:

```sh
./temperature 21 C F
```

On Windows, run the compiled program as `temperature.exe 21 C F`.
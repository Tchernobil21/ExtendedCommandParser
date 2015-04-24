# ExtendedCommandParser

This project is yet another substitute to the classical argument parsers. There are currently many parsers that for me are either too complicated, too simple, or too hard to custom. This one aims to be a trade-off between all those problems.

# Features

- Parse arguments from a command.
- Set constraints on the arguments.
- Handle dependences between arguments.
- Auto-generate help and errors.
- Create your own parsers and constraints.

# Syntax

A lot of programs use nearly the same syntax to set there arguments but there are no actual standard. I wanted to use a syntax which would have the best of them all and I've come up with an "extended standard" which suits me for many cases.

Example : `program +abcde -v -n 16 --long-option --float-number 13.5 file.txt`

Here you can see all the types of argument that we can use.

## Minus Argument

It's the kind of argument that we are mostly used to. It can take two forms :

- `-n` : a minus argument with the shortcut 'n'.
- `--float-number` : a minus argument with the fullname 'float-number'.

Make no mistake, `-v` and `--long-option` are actually plus arguments (see further). Indeed, a minus argument must take a parameter to be valid.

## Plus Argument

It's a way to allow concatenation of arguments. Plus arguments take no parameters and can take two forms :

- `-v` : yes, it is a plus argument (it does not take any parameter).
- `+v` : this notation is also correct.
- `+abcde` : this is interpreted as `-a -b -c -d -e`.
- `--long-option` : also a plus argument (takes no parameter).

You may wonder why `-v` and `--long-option` are plus arguments. The answer is simple : to be compatible with what we are used to. A plus arguments takes no parameters and must have a shortcut of one letter only. If we could only use the '+' notation, a help argument would be called `+h` which is not the standard `-h` or `--help` notation. On the other hand, it's really nice to be able to concatenate arguments like in `ls -lah` but the distinction between them is not clear.

Now we can do both and the distinction is clear.

## Target Argument

A target argument is always at the end of the arguments list. It has a name that will not appear in the command and no shortcut. In the syntax example, file.txt is a target. You can have as many targets as you want but the order must be the same every time.

# Validators

They handle the cast of the parameters and add constraints to it if you want.

- IntegerValidator : cast a parameter to int and can have a value in ranges like `0:10,100:`.
- FloatValidator : cast a parameter to float and can have a value in ranges like `0.0:10.0,100.0:`.
- DoubleValidator : cast a parameter to double and can have a value in ranges like `0.0:10.0,100.0:`.
- StringValidator : cast a parameter to string and can have a specific values like `str1,str2`.
- BooleanValidator : cast a parameter to bool, the parameter must be `yes`, `no`, `y`, `n`, `true` or `false`.

# Dependences

It's really anoying to check if an argument is set or if it must be set because of another argument. For instance, if you make a program that takes two integers n1 and n2 and return their sum, you know that if n1 is set, n2 must be set too, and you also know that your program cannot run if this arguments aren't set.

I hope that was clear but here is what the dependences could look like `program -> n1 & n2`. This mean "if program is set (which is always true), then n1 and n2 must be set too".

# Example

See example.cpp, you can use make to compile it, then try to execute commands like this to see what happens :

```
bubble
bubble -h
bubble +h
bubble --help
bubble -R
bubble -R -n 513
bubble -R -n 10 -rmax 10
bubble -r -n 10 -rmax 10
bubble -rv -n 10
bubble +rv -n 10
bubble -r -v -n 10
bubble --random --verbose --number 10
```

# Go further

You can also extend Validator to create your own, a good advice would be to look the code of Validator, BooleanValidator (which is quite simple), and BasicValidator. By extending BasicValidator you can set your own constraints, and parse directly into a specific object.

# TODO

- C++ 11 version.

# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A word for Maximum length

## According to its man page, what does `getrusage` do?

get the resource usage of a process

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

`before`and `after` are pointers to an object of type struct rusage in which the returned information is stored

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

c equals the next character from a file;If c is alphabetical characters or apostrophes, appends character to word. If words are alphabetical strings longer than LENGTH or with numbers, ignore them, else terminate and save current word.
Check the word's spelling, print word if misspelled. Finally, prepare for next word.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

It's difficult to deal with words that are alphabetical strings longer than LENGTH or with numbers.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

In this way, functions can take a large parameter, a data structure without copying it. Also, it says to the caller, functions won't change the contents of that parameter.
Passing a const reference also allows the compiler to make certain performance decisions.

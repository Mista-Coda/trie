# Trie (prefix tree)

This is a basic implementation of a Trie data structure (also known as 'Prefix Tree' or 'digital tree'), this data structure is commonly used for autocompletions.

This program simply indexes all files inside the current folder (or folder passed in through the first arg) and allows you to enter a term and returns completions for all files that exist starting with those characters.

## Building

Running the following commands:

```console
$ cc ./nob.c -o nob
$ ./nob
```

Builds the output `trie` executable.

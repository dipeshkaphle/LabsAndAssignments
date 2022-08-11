---
title: Compilers Lab 4 Report
author: 106119029 Dipesh Kafle, 106119073 Marmik Upadhyay, 106119117 Sobhagya Singh Dewal
bibliography: "bibliography.bib"
link-citations: true
geometry: margin=1cm
toc: true
urlcolor: blue
---

## Project Link

[Project Link](https://github.com/dipeshkaphle/Enma)

## Description

- We are using Recursive Descent Parser for the project.
- The expression parsing is done through Pratt Parser(A Recursive Operator Precedence Parser).

### Operator Precedence

- lhs > rhs means right associative.
- rhs > lhs means left associative.

![](./op_precedence.png)

### Parser Class

- Recursive Descent based parser

![](./parser_class.png)


## Output

### Error Handling

![](./continue_break.png)

![](./semantic_error.png)

### Parsing a full program

- Program 

![](./program.png)

- After Parsing

![](./parsed_program.png)

 

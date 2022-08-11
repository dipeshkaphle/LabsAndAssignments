---
title: Compilers Assignment 6
author: 106119029 Dipesh Kafle, 106119073 Marmik Upadhyay, 106119117 Sobhagya Singh Dewal
bibliography: "bibliography.bib"
link-citations: true
geometry: margin=2cm
toc-depth: 2
header-includes: |
  \usepackage{fancyhdr}
  \pagestyle{fancy}
  \usepackage{graphicx}
  \usepackage{amsfonts} 
  \usepackage{amssymb}
  \usepackage{amsmath}
  \usepackage[colorlinks = true,
              linkcolor = blue,
              urlcolor  = blue]{hyperref}
  \usepackage[australian]{babel}
urlcolor: blue
---

## \centering Features Implemented

- While Loop
- Conditional Statements
- Functions
- Five data types : string, int, double, bool, char
- Arithmetic Operations
- String Concat operation
- Logical Comparisions
- Type Checking
- Basic Type inference
- Undefined symbols static analysis


## \centering Code

[Link](https://github.com/dipeshkaphle/Enma)

## \centering Error Discovery Capabilities

### \centering Parsing Errors


| Break Outside of Loop is Error |
| :-------------------- |
| ![](./pics/breakOutsieLoop.png) |

| Continue Outside of Loop is Error |
| :-------------------- |
| ![](./pics/continueError.png) |


| Missing condition in while loop |
| :-------------------- |
| ![](./pics/invalidWhile.png) |


| Missing right hand side in let statement |
| :-------------------- |
| ![](./pics/missingInitialization.png) |

| Missing Type after : in let statement |
| :-------------------- |
| ![](./pics/forgotType.png) |


### \centering Semantic Errors with static analysis

[Semantic Analysis done in this file](https://github.com/dipeshkaphle/Enma/blob/main/frontend/SemanticCheck.cpp)

| Type Mismatch |
| :-------------------- |
| ![](./pics/type_mismatch.png) |

| Invalid Operands |
| :-------------------- |
| ![](./pics/bad_operands.png) |

| Undeclared Symbol |
| :-------------------- |
| ![](./pics/undeclared_sym.png) |

## \centering Intermediate Code Gen in Stack Based architecture


| Codegen for continue and break |
| :-------------------- |
| ![](./pics/continue_and_break.png) |


| Valid Program [Here in first and third line , type is inferred automatically with type inference] |
| :------------ |
| ![](./pics/prog.png) |

| CodeGen for above program|
| :------------ |
| ![](./pics/codegen1.png) |
| ![](./pics/codegen2.png) |


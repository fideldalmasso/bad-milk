# Table of contents
[Note](#note)
[What is Bad Milk](#what is bad milk)
[Screenshots](#screenshots)
[Games included](#games included)
[Installation](#installation)
[Licence](#licence)


# Note 
The primary language of this project is Spanish. Hispanohablantes [click aquí](README-es).

# What is Bad Milk
Bad Milk is a project that brings together simple games about numbers, guessing and memory. Some of them are related to basics topics in the programming world.

In addition to the games themselves, different features are included, such as: a user management system, a ranking system and a simple XOR encryption for sensitive files. 

The project was exclusively written in C++ using mainly [Zinjai](http://zinjai.sourceforge.net/), a free C++ IDE.

# Screenshots

# Games included
|Name   | Description| 
|---|---|
|Frical |Guess the secret number.|
|PiPaTi|Simple rock, paper, scissors.|
|Generala|Similar to poker dice. [More info](https://en.wikipedia.org/wiki/Generala)|
|Ahorcado|Hangman game.|
|ParEs|Memory game.|
|Batalla Naval|Naval Battle.|


# Installation
### Windows
Just download the installer from [here](win_installer/installer.exe) and follow the instructions. 

### Linux: building from source
Make sure you have git and build-essential package installed
First, clone this repository in your computer:
```
git clone https://github.com/fideldalmasso/Bad-Milk.git
```
Then run:
```
cd bad-milk
make
```
Finally, run the program by:
```
./bad-milk
```
If this last step doesn't work, first run the following and try it again:
```
chmod +x bad-milk
```

# Licence
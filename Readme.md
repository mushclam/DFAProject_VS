# DFA Minimalizing Program

This is DFA Minimal Program Project for `EC3216 Automata Theory` class.

I call this program as `DFAminimal` in below.

`DFAminimal` read json file that have DFA format and print out json file that minimized.

* DFA Format

```
{
  "state" : [""],           // List of states
  "symbol" : [""],          // List of symbol
  "transition" : [["","",""]],  // List of transition that have ["q1", "a", "q2"] format
  "startState": "",         // One start state
  "finalState": [""]        // List of final state
}
```

## Getting Started

`DFAminimal` can be used in `Windows` and `Linux` environment.

You can enter json file name have DFA format.

If you don't enter file name you want minimize, program is executed by default file name `dfa.json`

input file must be json file have DFA format

* Windows

Execute `DFAProject.exe` in `Release/` like below.

```
./DFAProject.exe DFAfileName[dfa.json]
```

* Linux

1. Build program by using `makefile` at `DFAProject/`

```
make
```

2. Run `DFAminimal`

```
./DFAminimal DFAfileName[dfa.json]
```

## Examples

* Input DFA file
```
{
  "state": [ "0", "1", "2", "3", "4", "5" ],
  "symbol": [ "a", "b" ],
  "transition": [
    [ "0", "a", "1" ],
    [ "0", "b", "3" ],
    [ "1", "a", "0" ],
    [ "1", "b", "3" ],
    [ "2", "a", "1" ],
    [ "2", "b", "4" ],
    [ "3", "a", "5" ],
    [ "3", "b", "5" ],
    [ "4", "a", "3" ],
    [ "4", "b", "3" ],
    [ "5", "a", "5" ],
    [ "5", "b", "5" ]
  ],
  "startState": "0",
  "finalState": [ "3", "5" ]
}
```

* Output DFA file
```
{
	"finalState" : [ "35" ],
	"startState" : "01",
	"state" : [ "01", "35" ],
	"symbol" : [ "a", "b" ],
	"transition" : 
	[
		[ "01", "a", "01" ],
		[ "01", "b", "01" ],
		[ "35", "a", "35" ],
		[ "35", "b", "35" ]
	]
}
```
**Key of output file is sorted by alphabetical order it because jsoncpp sort all contents in value**

## Authors

* **Jinwook Park**
* **Soohyun Choi**
* **Songmi Oh**

## Acknowledgments

* It used `Jsoncpp` library
* Thanks for professor `Changwook Ahn`!

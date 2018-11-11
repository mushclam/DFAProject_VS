# DFA Minimalizing Program

This is DFA Minimal Program Project for `EC3216 Automata Theory` class.

I call this program as `DFAminimal` in below.

`DFAminimal` reads a JSON file that has a definition of a DFA in `DFA Format` as below and prints out minimized DFA written in a output JSON file `result.json`.

* DFA Format

```
{
  "state" : [""],               // List of states
  "symbol" : [""],              // List of symbols
  "transition" : [["","",""]],  // List of transitions in ["q1", "a", "q2"] format
  "startState": "",             // Single initial state
  "finalState": [""]            // List of final states
}
```

## Getting Started

`DFAminimal` can be executed in `Windows` and `Linux` environment.

You can enter a name of JSON file which is in `DFA Format`.

If you don't enter the file name you want to minimize, program is executed by default file `dfa.json`

Input file must be a JSON file in `DFA Format`.

Output file is saved as `result.json` with minimized DFA described in your input file.

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

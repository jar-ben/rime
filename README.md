# RIME

RIME is a tool for enumeration of Maximal Satisfiable Subsets (MSSes), or alternatively, Minimal Correction Subsets (MCSes), of a given Boolean formula. 
**This is an experimental version which still needs some clean up. If you with to use the tool and encounter any problems with installing or running the tool, please, contact me at xbendik=at=gmail.com.**


## Installation
We use miniSAT [4], glucose [2], and CaDiCaL [3] as SAT solvers. The code of miniSAT and glucose is packed with the tool, however, you still need to install the library zlib which is used by miniSAT. You can install zlib with:
```
sudo apt install zlib1g-dev
```

You also need to install CaDiCaL. Please, follow the instructions at https://github.com/arminbiere/cadical

Once you have installed zlib and CaDiCaL, you should be able to build our tool.
In the main directory (the one where is this README.md file), run:
```
make
```

## Running our tool
```
timeout <seconds> ./rime <input_cnf_file>
```

So for example, "timeout 10 ./rime ./examples/bf1355-228.cnf"
To see all the available parameters, run:
```
./rime -h
```

## Other Third-Party Tools
Besides mniSAT, glucose, and CaDiCaL, we also use two single MUS extraction tools: muser2 [5] and mcsmus [8]. Muser2 is presented in our repo in a binary form, and mcsmus is compiled with our code. Moreover, provide an interface for using two MSS/MCS extraction tools: mcsls and cmp, and a MaxSAT solver UWrMaxSat. These tools are not packed with our tool; either due to restrictive license or we have just not fully integrated them yet. 

## Related Tools
The tool MUST originates from our MUS numeration tool called MUST (https://github.com/jar-ben/mustool). MUST is a contemporary MUS enumeration tool. Moreover, besides the SAT domain, it also supports MUS enumeration in the SMT and LTL domains. If you are interested in MUS enumeration, then you should give MUST a try. 

## References
* [1] The algorithm RIME is currently under a conference review process. We will add a reference once it will be accepted. 
* [2] https://www.labri.fr/perso/lsimon/glucose/
* [3] http://fmv.jku.at/cadical/
* [4] http://minisat.se/
* [5] https://bitbucket.org/anton_belov/muser2
* [8] https://bitbucket.org/gkatsi/mcsmus

## Contact
In case of any troubles, do not hesitate to contact me, Jaroslav Bendik, the developer of the tool, at xbendik=at=fi.muni.cz.




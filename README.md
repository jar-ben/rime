# RIME

RIME [1] is a tool for enumeration of Maximal Satisfiable Subsets (MSSes), or alternatively, Minimal Correction Subsets (MCSes), of a given Boolean formula. 
**This is an experimental version which still needs some clean up. If you wish to use the tool and encounter any problems during installing or running the tool, please, contact me at xbendik=at=gmail.com.**


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
To see all the available options, run:
```
./rime -h
```

## Other Third-Party Tools
Besides miniSAT, glucose, and CaDiCaL, we also use two single MUS extraction tools: muser2 [5] and mcsmus [8]. Muser2 is presented in our repository in a binary form whereas mcsmus is packed as a source code and compiled with our code; you do not have to install these tools separately.  
Moreover, we provide an interface for using two MSS/MCS extraction tools: mcsls [6] and cmp [7], and a MaxSAT solver UWrMaxSat [9]. These tools are not packed with our tool; either due to restrictive license or we have just not fully integrated them yet. You do not need to install these tools to be able to run RIME. However, you can if you want. The usage of these tools is documented in the help message (./rime -h).

## Related Tools
RIME originates from our MUS (minimal unsatisfiable subsets) enumeration tool called MUST (https://github.com/jar-ben/mustool). If you are interested in MUS enumeration, you should give MUST a try. 

## References
* [1] Jaroslav Bendik and Ivana Cerna. Rotation Based MSS/MCS Enumeration. LPAR 2020 (accepted).
* [2] https://www.labri.fr/perso/lsimon/glucose/
* [3] http://fmv.jku.at/cadical/
* [4] http://minisat.se/
* [5] https://bitbucket.org/anton_belov/muser2
* [6] Joao Marques-Silva, Federico Heras, Mikolás Janota, Alessandro Previti, and Anton Belov. On computing minimal correction subsets. IJCAI 2013.
* [7] Éric Grégoire, Jean-Marie Lagniez, Bertrand Mazure. An experimentally efficient method for (MSS, coMSS) partitioning. AAAI 2014.
* [8] https://bitbucket.org/gkatsi/mcsmus

## Citing
If you use our tool (RIME) in your research, please cite our paper that presented RIME:
```
@inproceedings{LPAR23:Rotation_Based_MSS_MCS_Enumeration,
  author    = {Jaroslav Bend{\'{\i}}k and Ivana Cern{\'{a}}},
  title     = {Rotation Based MSS/MCS Enumeration},
  booktitle = {LPAR23. LPAR-23: 23rd International Conference on Logic for Programming, Artificial Intelligence and Reasoning},
  editor    = {Elvira Albert and Laura Kovacs},
  series    = {EPiC Series in Computing},
  volume    = {73},
  pages     = {120--137},
  year      = {2020},
  publisher = {EasyChair},
  bibsource = {EasyChair, https://easychair.org},
  issn      = {2398-7340},
  url       = {https://easychair.org/publications/paper/rXZL},
  doi       = {10.29007/8btb}}
  ```

## Contact
In case of any troubles, do not hesitate to contact me, Jaroslav Bendik, at xbendik=at=gmail.com.




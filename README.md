# RIME

RIME is a tool for enumeration of Maximal Satisfiable Subsets (MSSes), or alternatively, Minimal Correction Subsets (MCSes), of a given Boolean formula. 
**This is an experimental version**. **If you wish to use the tool, please, contact me at xbendik=at=gmail.com.**

Most of the code originate from our MUS enumeration tool called MUST which is available at https://github.com/jar-ben/mustool (if you are interested also in MUS enumeration, give MUST a try, it is a state-of-the art MUS enumerator). MUST support MUS enumeration not just in the SAT domain, but also in the SMT and LTL domains. However, RIME is designed (and can be used) only for MSS enumeration in the SAT domain. Consequently, there is currently a lot of code that is useless (and unreachable). Eventually we will clean up the code in this repo and keep only the things that are related to RIME; however, it can take a while. 

Nevertheless, you can try to build the code and if you succeed, you should be able to run RIME. The build process is done via a make file, i.e., it is done by typing "make" in the root directory of the repo. Yet, you will probably need to first install several additional third party tools. Please, follow the installation instructions for MUST at https://github.com/jar-ben/mustool since everything that is required by RIME is also required by MUST. If you succeed with the build, you can run the tool via: 

timeout <seconds> ./rime <input_cnf_file>
  
So for example, "timeout 10 ./rime ./examples/bf1355-228.cnf"



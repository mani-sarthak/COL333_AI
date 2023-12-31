## Notes after 1st reading 
1. the network is given in `alarm.bif` but the probabilities are not given (-1 is marked in all CPT's). However a parser for reading `alarm.bif` is given to get the understanding of the graph. So we have to learn the parameters from one of the many algorithms.


2. Now in the data file each line will be a patient record. `All features will be listed in exactly the same order as in the .bif network` and will be comma-separated. If a feature value is unknown we will use the special symbol `“?”` for it. `There will be no more than 1 unknown value per row.`

3. Since data is also incomplete we have to use `expectation maximisation !`.

4. Around `10,000` patients records in data file.



#### What to output ?
learnt CPT with upto `4 decimal places` or simply output the completed version of `alarm.bif`


#### What's provided ?
1. code to parse `alarm.bif` and storing relevant information about graph in a data structure.
2. some basic helper functions.

3. `records.dat`
4. `startup_code.cpp`
5. `format_checker.cpp` : uses `alarm.bif`, `solved_alarm.bif` and `gold_alrm.bif`.


### Constraints:
1. completion in `2mins` !! with about `10,000` patient records.



#### Running Instructions:
0. `git pull origin main`
1. run `make all`. Assuming the data is in `records.dat`.
2. `enjoy :)`.




## Draft completed on OCT'22
#### Only optimisations and review left

#### Scope of Improvement
1. ~~`dataUpdater()`: I think that the probabilities using inference can be made even better (with using childs into account too; ie. considering the whole `markov blanket`).~~
2. ~~`CPTUpdater()`: What is implemeted is based on input from ChatGPT and we have to apply the learning algorithms learnt in class (`weighted average`).~~
3. `readDataFile()`: Since i dont know much of `ifstream` in c++, input from ChatGPT have been taken in consideration. If you know better one please implement.
4. `readNetwork()`: Since i don
t know much of `ifstream` & `ofstream` in c++, input from ChatGPT have been taken in consideration. If you know better one please implement.
5. ~~`Note`: `Timing effects` are to be checked else gandi bt ho sakti hai !!~~
6. ~~`smoothing` in `CPTUpdater()` needs to be implemeted.~~
7. ~~Analysis of `smoothingFactor`~~. This remains 0;
8. ~~Till now it is working on `HARD` have to shift that to `SOFT`~~.



#### Time Analysis (it canges with each implemetation, cant comment on it !!)
1. reading neywork and dataalong with initialising CPT and intermediateData `70ms - 75 ms` -> `150ms`. 
2. Each iteration in learning and inferencing takes abt `255ms to 275ms` -> `800ms` now. Out of them learnign takes most of the time `240ms - 250ms` and the time by inferencing is around `20ms to 25ms`.
3. writing to solved_alarm.bif happens in less than `2ms`.




#### Rivision and further implementation !
1. ~~since enough time, generalising the code for any graph/CPT should work!~~
2. ~~check for writing in `solved_alarm.bif` that the sum is 1.0000 and not more !!~~


#### Discussions on 29th Oct
1. ~~Update the writting method (`setprecision fix`)~~.
2. ~~Update the codes in `startup_code.cpp`~~.
3. Look for `likelihood estimate` for the optimal solution. Probably wont be using !!

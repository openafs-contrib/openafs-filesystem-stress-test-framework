# Open AFS Stress Testing Framework

## Capabilities
**Stress Testing**

Currently the tester runs the operations defined inside of *fileoperations.h* over *n* number of files and directories in a 
random order and sequence. Users can edit *config.cfg* to alter the frequency of certain file operations occurring and the length of the test
alongside other features. 

**Metrics**

Throughout the test certain metrics will be recorded and dumped into corresponding *.txt* files in the metrics directory.

[Throughput: Sequential and Random Access] *might deal with caching*

[IO Operations: Time to Append]

[Metadata Operations: Time to Rename, Write, Delete]

## Initialization

###Edit *config.cfg* before setup
The formatting of *config.cfg* is of a key value pair with "=" as the delimiter

###Setting up test directories and files
Run ```make init``` to establish the test files and test directories. Directories will be in the format of **testFiles-#**
inside of the **TestDirectory** directory

## Run
Run ```make run``` to run the tester.

## Reset
Run ```make clean``` to remove the test directories, files, and any files generated by the test suite

Run ```make reset``` to clean, setup, and run the test suite again

## Experimental
**Configurability** remains experimental and is not fully tested

**AFS Metrics** will be implemented in the future

Script to parse the data and visual will be implemented soon

##Running on OpenAFS
**Bash Script to scp this package and run on multiple machines will be implemented soon**
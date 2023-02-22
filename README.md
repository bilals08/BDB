# BDB: B Tree and B+ Tree based database system
BDB is a simple database system that stores data in multiple files and uses B tree and B+ tree to index the data stored in files. The system is developed in C++.

## Data stored in DSDB system
The data stored in DSDB is related to the leading causes of deaths in different states of USA. Each tuple (or entry) in data comprises of the following fields:

* ID (This field is unique for every row/record/tuple within data)
* Year
* Cause name
* State
* Deaths
* Age-adjusted death rate
* Any one of the above fields can be used for creating the index. The data is stored in 10 different files.

## Indexing
BDB supports both B and B+ tree based indexing on the data. For both B and B+ trees, the root node will always reside in the heap (i.e., RAM). However, all other nodes will be stored on the file system in separate files. Each index has a separate directory to store the files related to a B or B+ tree index.

## Indexing with duplicates
Indexing on data fields other than “ID” may result in duplicates, i.e., same key may point to multiple tuples (or entries) in the data. The duplicates are handled in the following manner:
* There must be only one entry for each key in both B and B+ trees (even if the key is pointing to multiple tuples in the data).
* Each key maintains the information about the file names and line numbers of all relevant entries (i.e., entries with the same key).
* When the node is loaded in the heap (i.e., RAM), a linked list (associated with each key) is created to store the file names and line numbers of duplicate entries.
* When the node is stored in the file, the file names and line numbers of duplicate entries are stored as a list in textual form.

## Operations supported by DSDB
* Create index: The user can create a B tree index or B+ tree index (at the same time multiple indices can reside), specify the order of B tree or B+ tree (i.e., value of m) and on which data field to perform indexing.
* Point search: The user can specify the key and DSDB system should be able to display the corresponding tuple(s) from the data.
* Range search: The user can specify a range of key values and DSDB system should be able to display all the relevant tuples.
* Update key, field, old value, new value: The user can specify the key, name of the field to be modified along with its old value and new value. The DSDB system should be able to find the tuple with the given key and change the value of the field to new value. If multiple tuples exist with the same key, the old value is used to break the ties.

## Contributing
Contributions to this project are welcome. Please feel free to create an issue or a pull request if you have any suggestions or improvements.


# Introduction
This is a program written in C++, which simualtes social networking, where people can add/remove/find friends. 

# Run
    cd Social_Network/
    make 
    ./run

# Functionalities:
`insert [name]` insert an person into the network. 
`printAll` print every person in the network, including their names, ages, and all their friends.
`range [name1] [name2]` print every person in the network between name1 and name2, including their names, ages, and all their friends.
`printTree:` print the current B+ tree.
`printNodes` print all leaves in the current B+ tree.
`printFriends [name]` print all friends' information of a person.
`addFriend [name1] [name2]` make these two people become friends.
`printHashTable` print current hashtable.

# Specification
It contains:
- a profile data on disk, which has a name, age, and occupation for each user.
- a B+ tree (in memory) on the name attribute of the profile file. It supports insert and range search queries.
- a friendship graph (in memory) where each graph node comprises of the name of the
user, edges to all his/her friends as well as a pointer to his/her record in the profile data. The graph supports insert and search for friends queries.
- a hash function, which takes the name of a user and maps it to the corresponding
node in the friendship graph, thus allowing access to the friends of the given user.

# Author
Shunji Zhan


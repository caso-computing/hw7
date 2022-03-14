# Design Doc for homework 7: Hash tables, I/O and strings

**Connor Lynch, CS13
  March 7, 2022

# introduction

This homework implements a customer lookup database using hash tables.  I'm also implementing 
the **hardmode** version of the program to include inserting each customer record into a BST structure.

I will also be using "regular expressions" to parse the customer database table.

I've also added command line parsing to change bucket size, input file, output file, and a synopsis of usage.   see below for flags and synopsis.

**Code Acknowledgements**
  Dr. Long
  I'm using code from Derrel Long's class to execute the compile regex expression to parse the DB.  I'm also 
  using code that generates a **SPECK** hash key for my hash table.  It is a very good hash code that 

  generates a good distribution of hash keys to help minimize collissions in the hash table.
  Eugene
    Eugene (TA) supplied the template using for command line parsing.

**Extra Features in code

  o  ./business does command line parsing.  These are the flags you can pass:  
     -i  inputfile_name -o outputfilename -b bucket_size -h synopsis
     without specifying these values, they default as follows:  input='customers.tsv', 
     output='customer_out.tsv' **note: different than hw instruction output**, bucketsize=10
  o  Program implements **HARD** mode.  This means list_sorted is implemented and a binary tree is kept.  **note:**  when you issues the list_sorted command, you just get a list of sorted keys, not the complete record for each key.  This was done for output clarity.  Use 'lookup' or 'list' for complete DB record display.
  o  The HashTable data structure also keeps the following follows:  bucketsize, bst root ptr, total records entered, and longest link created in a bucket.  Though these value can be kept with the HashTable, I didn't implement the record keeping for the stats.  Only root pointer and bucketsize was implemented.
  o  Added a **hidden command** to the input routine called **hash_key** that returns the for ANY value inputed on the 'input email address' line.  This is a helpful debugging tool to make sure the keys are being distributed evenly and correctly across the hash buckets.
  
  **Note on the BST**:  Since the binary search table only makes sense with the DB's HashTable, I put the pointer to the root of the BST in the structure for the hashtable.  This made more sense than tracking the BST as a seperate structure.  The other reason was that when an entry was deleted from the hash
      table, it also had to be deleted from the BST.  Otherwise, you could have pointers floating around to nodes that had alread been 'free()'.
      
      Correction:  I made an update to the above.  It was simpler to create a BST node with right and left pointers and a pointer to the customer record stored in the HT node in the hash table.  It made the
          addition and deletion in the BST table a lot simpler.  Before this, when I deleted a record, I
          would also replace the key in a ht node with the successors key.  This had a nasty side affect of
          leaving the successors key in the wrong bucket on the hash table.  The delinking of these two
          structures made the code much easier to implement.

##Input Commands##
  notes:  List will print out all records in the HT along with the customer rec.  list_ordered will print out only the bst keys.  It also provides a helpful 'left, right' pointer output so one can visulize the structure of the tree itself.  The form for each key is...
            key:  keyname (email address)
                left->node->keyname, right->node->keyname
        There is also one hidden command, hey_hash that prints out the hash number for any data inputed on the next line.  It also prints the bucket number generated from that hash key.

**Limitations**
  o  There is no checking to ensure any of the data base fields make sense.  eg, I don't' check 
     for legitament email addresses
  o  The database has to be formatted as lines of records with 4 fields, each field seperated by a tab
     character.  (thus, a tsv file).  The fields are:  email, name, shoe size (read as an integer), 
     favorite food.
  o  The root node of the BST is created using the 1st record read from the customer DB.  There is no logic to try and "balance" the tree.  This means that if the 1st record of the DB contains an ascii value that is very low (eg, APPLE) or high (eg, zebra), you will end up with a very unbalance tree of O(n).
  o  The input command **Listed_ordered** returns the value of emails sorted in ASCII order.  That means all capitalize letters will be sorted BEFORE lower case letters.  This could be changed by changing the node key in the BST routine to insert and remove by converting uppercase letters to lowercase during insertion and removing (but not changing the node record value of uppercase letters).  


## Data Structures
  
  ###Customer Record - stores both the 4 fields from db record + the BST right and left links to LLNodes
        struct cus_rec {
            char *email;
            char *name;
            int shoe_size;
            char *fav_food;
            LLNode *left;           // Not used.  Updated with seperate BST Node structure
            LLNode *right;          // Not used.  Updated with seperate BST Node sturcutre (below)
        };

   ### Hash Table LL Nodes -  This structure is used in the hash table linked list of nodes to cus recs
        struct LLNode {
            cus_rec record;
            LLNode *next;           //  Linked list from the hash table bucket
        };
        
    ### BST Nodes           -  Added this during the debug cycle.  Turns out my bright idea of adding
                               the tree pointers in the customer records was not that bright.  Creating
                               the structure this way mean I didn't have to change any code for inserting
                               and deleting from the hashtable.  Just change variables in the BST.c code
                               Note:  I'm just droping the a HT linked node into a BST node.
        struct BSTnode {
            Cus_Rec *cusPtr;    //Makes it easy to copy data from LLnode to a BSTnode.  More importantly,
                                //there's no need to duplicate space for the customer record in both the
                                //BST structure and Hash Table structure.  This is a big benefit if the 
                                //DB becomes really large.
            BSTnode *left;
            BSTnode *right;
        };
        
}

###Hash Table
        struct HashTable{
            LLNode *root;           // ptr to BST root
            uint64_t salt[2];       // salt for SPECK hash code
            uint64_t size;          // bucket size for hash table
            uint64_t num_records;   // stat for total number of records stored.  Not implemented
            uint64_t long_link;     // stat for longest linked list in hashtable.  Not implementd
            uint64_t num_entries;   // stat to compute empty buckets, ie efficiencey of hash.  Not implemted
            LLNode **llink;         // **array of pointers to a linked list of Nodes
};
            
  All structures are created dynamically using calloc and malloc.  
  
  The hash table itself carries the size
  of the hash table as suggested.  The links to the linked list would be addressed as HashTable[x] (where 
  x<size).  To get to a specific email, you would do this:  HashTable[x]->Customer->email for example.        
}


No other complex data structure was introduced for this problem.

## Pseudo Code for functions to implement

0)  Parse the command line to sse if any default vales need to be changed
1) **Open customer Data Base
2) Create Hash Table and store in *ht

3) While (Read Record from Customer DB){
  3a) **Parse Customer Data Base for 4 fields:  email, name, shoe size, favorite food

  3b) **Compute the key=hash_key(record.email)%sizee
  3c) Insert customer Record LL into hash table[key]
  3d)  If (hardmode) insert customer record into BST
}

While (Reading for Termnal and INPUT <> quit){
  if (input=add) add_customer record;
  if (input=delete) delete_customer record;
  if (input = lookup) display_customer.email record;
  if (input = list) list_hash table and BST (if in hard mode)
  if (input = list_sorted) list_BST in post order transversal (ie sorted alphabetically)
  if (input = save) write_hashtable to customerDB
  if (input = quit) break
}

Clean up dynamic Memory

exit program

###functions
add_customer_rec(ht, customer_rec) {
  temp_ptr = ht-llink[key]
  ht-llink[key]=customer_rec
  if temp (!null) then customer_rec->llink=null
  }
  
 bstInsert (root node, node to insert)
   insert node into bst in a postorder insertion
   }

bstDelete(root node, node to delete){
  recursively search down bst tree to locate node to delete
  then search for the min successor to replace node to delete
  change parent pointer to point to successsor node
  set successor's left and right pointers
  (you actually replaced the contents of the deleted BST node with the successor's data)
    therefore you need to reclaim the memmory of the successors node since it is tucked in the 'deleted' node
}
  
display_customer(ht, customer_rec.email){
    key = hash(customer_rec.email)%ht->size
    if ht->llist[key] = null then return 'customer doesn't exist'
    else if (ht-llist[key]->llnode.email == customer_rec.email) print customer rec
    else see if there are anymore nodes linked to this entry, if not return customer not foud
    else goto next linked entry and repeat check till you either find the customer _rec to print or return
      not found.

delete customer(ht, customer_rec){
   Does customer exits in ht;  if yes, remove hash entry
                               if no, return customer doesn't exits
}

list_hash table(ht){
  for each entry in the hash table do{
    if ht[entry]!=Null print all entries at this hash table index by following the linked list
  }
}

list_sorted(ht){
  retrieve root value for bst from HT
  do a postorder transversal of BST
  display the keyindex (email) at the end nodes of the BST  (done for 'display' simplicity)
}

write_hash table to db{
    for each entry in the hash table do{
    if ht[entry]!=Null write all entries at this hash table index to the DB in tab seperated values
  }
}

  
   


## Cleaning up memory

My strategy for eliminating memory leaks is to make sure any dynamically allocated memory from either malloc,
calloc, ralloc, strdup, or regexp are 'free' when they are no longer needed.

There are four data structures that are being dynamically created in this program:
  1)  The hash table.
  2)  The array of pointers in the hash table that point to a linked list of customer recs, 
      'customer rec **hash table**
  3)  The strdup arrays stored in the customer record fields: email, name, favorite food
  4)  Compiled regular expressions used to parse the DB.

Each of the above structures need to be released before the program exits.

The  character string arrays pointed to in customer rec are released when we eliminate a customer record.
We then set these pointers to NULL.  

After freeing up the customer rec pointers, we free up the memory of the linked list and then finally the 
hash table itself when it is time to exit the program.  

Finally, we have to free up the memory used by the hash table array before exiting the program.



# Design Doc for homework 7: Hash tables, I/O and strings

**Connor Lynch, CS13
  March 7, 2022

# introduction

This homework is to implement a quick customer lookup database using hash tables.  I'm also implementing 
the **hardmode** version of the program to include inserting each customer record into a BST structure.

I will also be using "regular expressions" to parse the customer database table. 

**Code Credits**
  I'm using code from Derrel Long's class to execute the compile regex expression to parse the DB.  I'm also 
  using code that generates a **SPECK** hash key for my hash table.  It is a very good hash code that 
  generates a good distribution of hash keys to help minimize collissions in the hash table.


## New Data Structures

  ###Customer Record
        Struct Custmer_Rec{
            char *email
            char *name
            int shoe size
            char *favorite food
            Custmer_rec *right      // to be used for hard mode insertion in BST
            Custmer_rec *left       //to be used for hard mode insertion in BST
}

  ###Hash Link
        Struct LLhash{
            Custmer *ptr
            LLhash *LLhash
            }

###Hash Table
        Struct Hash_Table{
            uint64_t    size
            uint64_t   salt[2]
            LLhash **LLink
            }
            
  All structures are created dynamically using calloc and malloc.  
  
  The hash table itself carries the size
  of the hash table as suggested.  The links to the linked list would be addressed as HashTable[x] (where 
  x<size).  To get to a specific email, you would do this:  HashTable[x]->Customer->email for example.        
}


No other complex data structure was introduced for this problem.

## Pseudo Code for functions to implement

1) **Open customer Data Base
2) Create Hash Table and store in *ht

3) While (Read Record from Customer DB){
  3a) **Parse Customer Data Base for 5 fields:  email, name, shoe size, favorite food

  3b) **Compute the key=hash_key(record.email)%sizee
  3c) Insert customer Record LL into hash table[key]
  3d)  If (hardmode) insert customer record into BST
}

While (Reading for Termnal and INPUT <> quit){
  if (input=add) add_customer record;
  if (input=delete) delete_customer record;
  if (input = lookup) display_customer.email record;
  if (input = list) list_hash table and BST (if in hard mode)
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
    if ht[entry]!=Null print all entries at this hash table index
  }
}

write_hash table to db{
    for each entry in the hash table do{
    if ht[entry]!=Null write all entries at this hash table index to the DB in tab seperated values
  }
}

  
   


## Cleaning up memory

My strategy for eliminating memory leaks is to make sure any dynamically allocated memory from either malloc,
calloc, ralloc, or strdup are 'free' when they are no longer needed.

There are three data structures that are being dynamically created in this program:
  1)  The hash table.
  2)  The array of pointers in the hash table that point to a linked list of customer recs, 
      'customer rec **hash table**
  3)  The strdup arrays stored in the customer record fields: email, name, favorite food

Each of the above structures need to be released before the program exits.

solver.c was already coded to release the char *guess each time through the do loop to guess a new word.

The  character string arrays pointed to in customer rec are released when we eliminate a customer record.
We then set these pointers to NULL.  

After freeing up the customer rec pointers, we free up the memory of the linked list and then finally the 
hash table itself when it is time to exit the program.  

Finally, we have to free up the memory used by the hash table array before exiting the program.



//
//  main.c
//  hw7
//
//  Created by Connor Lynch on 3/2/22.
//  This is the code to read a customer data base and
//  then set the mode to 'input' to await a valid user command from the
//  terminal.
//  Once the command quit is given, the code exits from input mode and then cleans
//  up any memory allocated on the stack and closes all open files.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "parser.h"
#include "salts.h"
#include "speck.h"
#include "input.h"
#include "ht.h"
#include "bst.h"

#define OPTIONS "b:i:o:h"

int main(int argc,  char * argv[]) {
    char *field;
    FILE *bdb;
    regex_t db_parse;
    int buckets=10;
    char *inputfile="customers.tsv";
    char *outputfile="customers_out.tsv";
   
//  Code to parse the command line
    
    //  template for parsing code using getopt thanks to Eugene
    //  getopt will parse the command line passed.
    //  if no arguments, it will print out the help file else
    //  -b: Specfies the hash size, ie, buckets to create in the hash table, default = 10.
    //  -i: specifies in the customer data base file in tsv, default = customers.tsv
    //  -o: output tsv customer data base file, default = customer_out.tsv
    //  -h displays program synopsis and usage
    //
    

     char *help_str = "SYNOPSIS\n"
     "Simiple data base commands to read and store records from a\n"
     "customer data base composed of 4 fields, each field is seperated\n"
     "by a tab deliminated value.\n"
     "\n"
     "USAGE\n"
     "./businessdb [-i inputfile] [-o outputfile] [-b sizze] [-h]\n"
     "\n"
     "OPTIONS\n"
     "-b         specifies the hash table bucket size.  DEFAULT=10\n"
     "-i         specifies the input file name.  DEFAULT = customers.tsv\n"
     "-o         specifies the output file name for 'save'.  DEFAULT = customers_out.tsv\n"
     "-h         Program usage and help.\n";
     
     int opterr;            //supress printing an error message for badly form args
     int opt = 0;
     
     //  Set up command line processing variable below
     //
     opterr = 0;

     //
     //  Command line parsing is below.  Keep track of which switches and arguments
     //  where passed.
     //
     
     while ((opt = getopt (argc, argv, OPTIONS)) != -1)
     {
     switch (opt)
     {
     case 'b':
     buckets = atoi (optarg);
     break;
     case 'i':
     inputfile = optarg;
     break;
     case 'o':
     outputfile = optarg;
     break;
     case 'h':
     printf ("%s\n", help_str);
     exit (1);
     
     default:
     printf ("%s\n", help_str);
     exit (1);
     }
     }

 
    if (!(bdb=fopen(inputfile, "r"))){
        printf("File %s not found.  Exiting program\n",inputfile);
        exit(-1);
    }
    
    HashTable *ht = ht_create(buckets);

    //"[\\w]?[^\\t\\n\\r]+" is the regular expression to parse the customer db
    //  the regex says:  match any printable character up to either a tab OR carriage return OR new line
    if (regcomp(&db_parse, "[\\w]?[^\t\n\r]+", REG_EXTENDED)){
        fprintf(stderr, "Failed to compile regex.\n)");
        return 1;
    }
    
 

    //  This while loop reads the customer database.  It assumes the database is correct, ie, for each
    //  record in the database, there are 4 fields (email, name, shoe size, favorite food).
    //  No error checking is done on the fields either.  For example, no check is made to see if we
    //  have a valid email address.  The database file is searched for fields using
    //  "[\\w]?[^\t\n\r]+" as the regex.  ie, fields in a record are seached for printable ascii chars
    //  delineated by 'tabs', 'newlines', or 'carriage returns.'
    //
    while (true){
        LLNode *node=LLnode_create();
        
        if (!(field=next_word(bdb, &db_parse))){
            free(node);                                     // we don't need our last node.
            node=NULL;
            break;                                          // Reached end of Customer DB
        }
        node->record.email=strdup(field);
        node->record.name=strdup(next_word(bdb, &db_parse));
        node->record.shoe_size=atoi(next_word(bdb, &db_parse));
        node->record.fav_food=strdup(next_word(bdb, &db_parse));
        node->record.left=NULL;
        node->record.right=NULL;
        ht_insert(ht, node);
        if (ht->root==NULL){
            ht->root=node;
        }
        bst_insert(ht,ht->root,node);
    }
    printf("*** Done creating hash table & BST from DB file.\n\n");
    regfree(&db_parse);
    fclose(bdb);              // Done reading from DB, so close it.
    
//  Main i/o input of program
    input(ht,outputfile);                // go process termional input commands
    
//  Now clean up all allocated pointers.  We can trace all dynaic pointers via the hash table ptr.
    ht_delete(ht);
    ht=NULL;

}

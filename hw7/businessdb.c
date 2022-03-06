//
//  main.c
//  hw7
//
//  Created by Connor Lynch on 3/2/22.
//

#include <stdio.h>

#include "parser.h"

int main(int argc, const char * argv[]) {
    char *field;
    FILE *bdb;
    regex_t db_parse;
    // insert code here...
    //"[\\w]?[^\\t\\n\\r]+" is the regular expression to parse the customer db
    //  the regex says:  match any printable character up to either a tab OR carriage return OR new line
    if (regcomp(&db_parse, "[\\w]?[^\t\n\r]+", REG_EXTENDED)){
        fprintf(stderr, "Failed to compile regex.\n)");
        return 1;
    }
    bdb=fopen("customers.tsv", "r");

    for (int i=0;i<20;i++){
        field=next_word(bdb, &db_parse);
        printf("DB Field is: %s\n",field);
    }
    

    printf("Hello, World!\n");
    return 0;
}

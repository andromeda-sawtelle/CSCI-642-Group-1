char* identGlobal = NULL;
char* poisonedIdents[1024];
int poisonedIndex = 0;
char prevUnaryStar = 0;

...

char toPoison = 0;
if(identGlobal != NULL && strcmp(identGlobal, "free") == 0) {
  toPoison = 1;
}

// DONE: support __func__
char* ident = IdentTable + s;
if(toPoison) {
  poisonedIdents[poisonedIndex] = ident;
  poisonedIndex++;
}

if(prevUnaryStar) {
  for(int i = 0; i < poisonedIndex; i++) {
    if(strcmp(ident, poisonedIdents[i]) == 0) {
      error("ident: %s is poisoned\n", ident);
    }
  }
}

identGlobal = ident;
char* identGlobal = NULL;
char* poisonedIdents[32][1024];
int poisonedIndex[32];
char prevUnaryStar = 0;

...

char toPoison = 0;
if(identGlobal != NULL && strcmp(identGlobal, "free") == 0) {
  toPoison = 1;
}
// DONE: support __func__
char* ident = IdentTable + s;
if(toPoison) {
  poisonedIdents[ParseLevel][poisonedIndex[ParseLevel]] = ident;
  poisonedIndex[ParseLevel]++;
}
if(prevUnaryStar) {
  for(int j = ParseLevel; j >= 0; j--) {
    for(int i = 0; i < poisonedIndex[ParseLevel]; i++) {
      if(strcmp(ident, poisonedIdents[ParseLevel][i]) == 0) {
        error("ident: %s is poisoned\n", ident);
      }
    }
  }
}
identGlobal = ident;

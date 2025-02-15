#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define HASHSIZE				(101)

struct nlist {					/* table entry: */
	struct nlist* next;			/* next entry in chain */
	char *name;					/* defined name */
	char* defn;					/* replacement text */
};

static struct nlist* hashtab[HASHSIZE];			/* pointer table */

/* salloc: make a duplicate of s */
char* salloc(char* s)
{
	char* p;

	p = (char*)malloc(strlen(s) + 1);	/* +1 fpr '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* hash: form hash value for string */
unsigned hash(char* s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist* lookup(char* s)
{
	struct nlist* np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;		/* found */
	return NULL;			/* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist* install(char* name, char* defn)
{
	struct nlist* np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = (struct nlist*)malloc(sizeof(*np));
		if (np == NULL || (np->name = salloc(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else			/* already there */
		free((void*)np->defn);			/* free previous defn */
	if ((np->defn = salloc(defn)) == NULL)
		return NULL;
	return np;
}

main()
{
	struct nlist* np1 = install("ursula", "123");
	struct nlist* np2 = install("george", "43242");
	struct nlist* np3 = install("samuel", "342342");

	return 0;
}

#!/bin/bash

#./bib.sh ds.bib
#mv ds_cleaned.bib ds.bib
./BibParser ds.bib
mv ds.bib.trim ds.bib

#!/bin/bash

TARGET=$1
OUTFILE="${TARGET%.bib}_cleaned.bib"
EXTENSION='.bak'
PREFIX="' = {'"
SUFFIX='},'
#Fields to remove
DELETIONS=(
    'file'
    'abstract'
    'language'
    'read'
    'rating'
    'date-added'
    'date-modified'
    'local-url'
    'annote'
    'month'
    'uri'
)
#Replacements ('original.new')
REPLACEMENTS=(
    'affiliation.collaboration'
)

echo -e "INPUT FILE:\n\t$TARGET"
echo -e "OUTPUT FILE:\n\t$OUTFILE"

#Perform deletions
echo "DELETIONS:"

# Clear the file
> $OUTFILE
SKIP=0
FIRSTENTRY=1
while read -r line; do
    PRINT=$line
    #echo $PRINT
    # Check if this line is commented
    COMMENT=`echo $line | grep "^%"`
    if [ -n "$COMMENT" ]; then
	# Print to output file
	if [ -n "$PRINT" ]; then
	    echo "$PRINT" >> $OUTFILE
	fi
	continue
    fi
	
    # Check if this line is the start of a new entry
    if [ "${line:0:1}" == "@" ]; then
	SKIP=0
	if [ "$FIRSTENTRY" -eq "0" ]; then
	    echo -e "}\n" >> $OUTFILE
	fi
	FIRSTENTRY=0
	# Print to output file
    #echo -e "\t${line:1:-1}}"
    echo -e "\t$line"
	if [ -n "$PRINT" ]; then
	    echo "$PRINT" >> $OUTFILE
	fi
	continue
    fi

    # Check if this matches any of the keys you want to delete
    for key in "${DELETIONS[@]}"; do
	MATCH=`echo $line | grep "^$key = {.*"`    
	if [ "$SKIP" -eq "1" ] || [ -n "$MATCH" ]; then 
	    # Look for the end of this key's field
	    CLOSES=`echo $line | grep "},$"`
	    if [ -n "$CLOSES" ]; then
		SKIP=0
	    else
		SKIP=1
	    fi
	    PRINT=""
	    break
	fi
    done 

    # Special case author lists: if the author list starts with {Collaboration Name}
    #   only include the collaboration name
    if [ -n "`echo $PRINT | grep "author = {{"`" ]; then
	PRINT=`echo $PRINT | sed 's/} and.*$/}},/g'`
    fi
    #echo $PRINT
    # Print to output file
    if [ -n "$PRINT" ]; then
	echo "$PRINT" >> $OUTFILE
    fi
done <$TARGET
echo -e "}\n" >> $OUTFILE

#Perform replacements
echo "REPLACEMENTS:"
TMPFILE="tmp.bib"
for i in "${REPLACEMENTS[@]}"; do
    IFS='.' read -a PAIR <<< "$i"
    ORIGINAL=${PAIR[0]}
    NEW=${PAIR[1]}
    echo -e "replacing $ORIGINAL with $NEW with command:\n\tsed 's/^'$ORIGINAL'/'$NEW'/g' $OUTFILE > ${OUTFILE%.bib}_2.bib"
    sed 's/^'$ORIGINAL'/'$NEW'/g' $OUTFILE > $TMPFILE
done

echo "Moving $TMPFILE to $OUTFILE"
mv $TMPFILE $OUTFILE

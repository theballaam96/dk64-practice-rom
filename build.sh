V=1
SRC="./src"
DEST="./src"
file = "./test.txt"
cat > $file
echo "running copy" > $file

#The last path we saw -- make it garbage, but not blank.  (Or it will break the '[' test command
LPATH="/////" 
#Let us find the files we want
find $SRC -iname "*.c" -print0 | while read -d $'\0' i
  do
  echo "We found the file name... $i" > $file;

  #Now, we rip off the off just the file name.
  FNAME=$(basename "$i" .doc)
  echo "And the basename is $FNAME" > $file;
  #Now we get the last chunk of the directory
  ZPATH=$(dirname "$i"  | awk -F'/' '{ print $NF}' )
  echo "And the last chunk of the path is... $ZPATH" > $file
  echo "" > $file

  # If we are down a new path, then reset our counter.
  if [ $LPATH == $ZPATH ]; then
    V=1
  fi;
  LPATH=$ZPATH
  echo $ZPATH

  # Eat the error message
  mkdir $DEST/$ZPATH 2> /dev/null 
  echo cp \"$i\" \"$DEST/${FNAME}\"
  cp "$i" "$DEST/${ZPATH}_${FNAME}"
done
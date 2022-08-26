V=1
SRC="./src"
DEST="./src"
log_file="./build.log"
rm ${log_file}
echo "Installing Python" >> ${log_file}
sudo apt install python3
echo "Building" >> ${log_file}

#The last path we saw -- make it garbage, but not blank.  (Or it will break the '[' test command
LPATH="/////" 
#Let us find the files we want
find $SRC -iname "*.c" -print0 | while read -d $'\0' i
  do

  #Now, we rip off the off just the file name.
  FNAME=$(basename "$i" .doc)
  #Now we get the last chunk of the directory
  ZPATH=$(dirname "$i"  | awk -F'/' '{ print $NF}' )
  echo "Moving file $i to ${DEST}/${ZPATH}_${FNAME}" >> ${log_file};

  # If we are down a new path, then reset our counter.
  if [ $LPATH == $ZPATH ]; then
    V=1
  fi;
  LPATH=$ZPATH

  # Eat the error message
  mkdir $DEST/$ZPATH 2> /dev/null 
  cp "$i" "$DEST/${ZPATH}_${FNAME}"
done
python3 scripts/amend_include.py
echo "Building initial files" >> ${log_file}
make clean
make all
echo "Wiping temporary C files" >> ${log_file}
rm ./src/*.c
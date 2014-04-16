x=$(find . -name "*\.[h|c]pp" | awk '{gsub(/ /,"\\ ")}8' ) 

for y in $x 
do
    echo "\"$y\""
done

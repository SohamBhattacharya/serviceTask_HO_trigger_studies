#/bin/bash

sourcePrefix="/dpm/indiacms.res.in/home/cms/store"

jobID="@1@"
sourceDir="user/sobhatta/@2@/crab_@2@"
outDir="sourceFiles/@2@"
outFile="@2@_custom"

filePrefix="root://se01.indiacms.res.in//store"


mkdir -p "$outDir"


sourceDir_temp="$sourcePrefix"/"$sourceDir"/"$jobID"
outFile_temp="$outDir"/"$outFile".txt

tempFile="$outDir"/temp.txt

echo "Source: $sourceDir_temp"
echo "Output file: $outFile_temp"
echo "Temporary file: $tempFile"

rfdir "$sourceDir_temp" > "$tempFile"

declare -a pathList=($(awk '{print $9}' "$tempFile"))

rm -f "$tempFile"
touch "$tempFile"

rm -f "$outFile_temp"
touch "$outFile_temp"

echo ""

for path in "${pathList[@]}"; do
    
    if [ "$path" = "failed" ] && [ "$path" = "log" ]; then
        
        continue
        
    fi
    
    path_temp="$sourceDir_temp"/"$path"
    prefix_temp="$filePrefix"/"$sourceDir"/"$jobID"/"$path"
    
    echo "Source: $path_temp"
    echo "Source (xrootd): $prefix_temp"
    
    rfdir "$path_temp" > "$tempFile"
    
    temp="$(awk '{print $9}' "$tempFile")"
    echo "$temp" > "$tempFile"
    
    # Remove failed and log directories
    sed -i -e "/failed/d" "$tempFile"
    sed -i -e "/log/d" "$tempFile"
    
    # Add prefix to each line
    sed -i -e "s%^%$prefix_temp/%g" "$tempFile"
    
    cat "$tempFile" >> "$outFile_temp"
    
    echo ""
    
done

# Sort
cat "$outFile_temp" | sort -V > "$tempFile"
cat "$tempFile" > "$outFile_temp"

rm -f "$tempFile"

echo ""



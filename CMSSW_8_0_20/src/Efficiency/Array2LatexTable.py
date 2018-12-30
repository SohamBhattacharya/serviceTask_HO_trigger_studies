def array2LatexTable(arr, isColumnTitled = False, table_caption = "", table_label = "", table_width = 1) :
    
    nRow = len(arr)
    nCol = len(arr[0])
    
    line_break = " \\\\"
    vertical_spacing =  "&"*(nCol-1) + line_break + "\n"
    horizontal_line = "\\hline" + "\n"
    
    latexTable = ""
    
    #latexTable += "\\begin{table}[!ht]" + "\n" + \
    #    "\\begin{center}" + "\n" + \
    #    "\\begin{tabular}"
    
    latexTable += "\\begin{adjustbox}{width=" + str(table_width) + "\\textwidth}" + "\n" + \
        "\\begin{tabular}"
    
    temp = "{|" + (" c |"*nCol) + "}" + "\n"
    latexTable += temp
    
    latexTable += horizontal_line
    latexTable += vertical_spacing
    
    for iRow in range(0, nRow) :
        
        row = " & \n".join(arr[iRow]) + line_break + "\n\n"
        
        if (iRow == 0 and isColumnTitled) :
            
            #latexTable += vertical_spacing
            latexTable += row
            latexTable += vertical_spacing
            
            latexTable += horizontal_line
            latexTable += vertical_spacing
        
        else :
            
            latexTable += row
    
    latexTable += vertical_spacing
    latexTable += horizontal_line
    
    #latexTable += "\\end{tabular}" + "\n" + \
    #    "\\end{center}" + "\n" + \
    #    "\\caption{" + table_caption + "}" + "\n" + \
    #    "\\label{" + table_label + "}" + "\n" + \
    #    "\\end{table}" + "\n"
    
    latexTable += "\\end{tabular}" + "\n" + \
        "\\end{adjustbox}" + "\n"
    
    return latexTable

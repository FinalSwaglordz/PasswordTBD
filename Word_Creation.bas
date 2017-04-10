Attribute VB_Name = "Module32"
Sub Cracker()
Attribute Cracker.VB_Description = "Create all words"
Attribute Cracker.VB_ProcData.VB_Invoke_Func = " \n14"
'
' Cracker Macro
' Create all words
'
    
    'a b c d
    Cells(1, 1) = "a"
    Cells(2, 1) = "b"
    Cells(3, 1) = "c"
    Cells(4, 1) = "d"
    Cells(5, 1) = "e"
    'Cells(6, 1) = "f"
    'Cells(7, 1) = "g"
    'Cells(8, 1) = "h"
    'Cells(9, 1) = "i"
    'Cells(10, 1) = "j"
    'Cells(11, 1) = "k"
    'Cells(12, 1) = "l"
    'Cells(13, 1) = "m"
    'Cells(14, 1) = "n"
    'Cells(15, 1) = "o"
    'Cells(16, 1) = "p"
    
    temp = Cells(1, 1).Value
    lrow = Cells(Rows.count, 1).End(xlUp).row
    Set lRange = Range(Cells(1, 1), Cells(lrow, 1))
    'Set xRange = Range(Cells(1, 2), Cells(4, 2))
    
    Set currentRange = lRange
    
    For t = 2 To 5 Step 1
        i = 0
        For Each xCell In lRange
            
            For Each yCell In currentRange
                i = i + 1
                Cells(i, t).Select
                Cells(i, t).FormulaR1C1 = xCell & yCell
            Next
            
        Next
        lastrow = Cells(Rows.count, t).End(xlUp).row
        Set currentRange = Range(Cells(1, t), Cells(lastrow, t))
    Next
    
    Cells(1, 1).Select
'
End Sub
